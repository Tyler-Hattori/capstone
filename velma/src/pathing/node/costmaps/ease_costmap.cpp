#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>

#include "math.h"

struct Obstacle {
  double min_angle;
  double max_angle;
  double distance;
};

class EaseCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher ease_cm;
  ros::Subscriber map;
  
   double min_ease_dist;
   double max_ease_dist;
   double berth;
   double max_ease_ideal_dist;
   double non_ideal_attenuator;
   double attentiveness;
   double ideal_berth;
   double berth_limit_weight_ratio;
  
  double local_search_radius;
    
public:
  EaseCostmap() {
    n = ros::NodeHandle("~");
      
    std::string costmap_topic;
    n.getParam("ease_costmap_topic", costmap_topic);
    n.getParam("min_ease_dist", min_ease_dist);
    n.getParam("max_ease_dist", max_ease_dist);
      
    ease_cm = n.advertise<nav_msgs::OccupancyGrid>(costmap_topic, 10);
    map = n.subscribe("/map", 1000, &EaseCostmap::map_callback, this);
      
    n.getParam("max_ease_ideal_dist", max_ease_ideal_dist);
    n.getParam("ease_berth", berth);
      berth = berth * 3.141593 / 180.0;
    n.getParam("ease_ideal_berth", ideal_berth);
      ideal_berth = ideal_berth * 3.141593 / 180.0;
    n.getParam("ease_weight_ratio_at_berth_limit", berth_limit_weight_ratio);
    n.getParam("ease_non_ideal_attenuator", non_ideal_attenuator);
    n.getParam("attentiveness", attentiveness);
    attentiveness = int(100/attentiveness);
    
    n.getParam("local_search_radius", local_search_radius);
  }
    
  signed char weight(double dist, double ang) {
      double weight = 0;
     
      if (dist <= min_ease_dist) return 0;
      else if (dist >= max_ease_dist) return 0;
      else if (dist <= min_ease_dist + max_ease_ideal_dist) weight = 100;
      else weight = int((1/(dist-max_ease_ideal_dist))*100);
      
      if (std::abs(ang) >= berth) weight = weight/non_ideal_attenuator;
      else if (std::abs(ang) >= ideal_berth) {
          double diff = (std::abs(ang) - ideal_berth) / (berth - ideal_berth);
          double attenuator = 1.0 - ((1.0 - berth_limit_weight_ratio) * diff);
          weight *= attenuator;
      }
      
      int weight_rounded = int(weight);
      return (signed char)weight_rounded;
  }
  
  bool local(const int cell) {
    
  }
    
  /*bool behind_obstacle(std::vector<Obstacle> obstacles, double angle, double distance) {
     for (int i = 0; i < int(obstacles.size()); i++) {
        if (angle <= obstacles[i].min_angle && angle >= obstacles[i].max_angle && distance > obstacles[i].distance) return true;
     }
     return false;
  }*/
  
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
      nav_msgs::OccupancyGrid costmap;
      costmap.header = cm.header;
      costmap.info = cm.info;
      
      std::vector<signed char, std::allocator<signed char>> weights;
      std::vector<Obstacle> obstacles;
      
      tf::TransformListener listener;
      tf::StampedTransform cam_to_map;
      ros::Time t = ros::Time(0);
      listener.waitForTransform("map", "base_footprint", t, ros::Duration(30));
      listener.lookupTransform("map", "base_footprint", t, cam_to_map);
      double th = tf::getYaw(cam_to_map.getRotation());
      double car_x = cam_to_map.getOrigin().getX();// + cm.info.origin.position.x; //- 0.4318*cos(th);
      double car_y = cam_to_map.getOrigin().getY();// + cm.info.origin.position.y; //- 0.4318*sin(th);
      //ROS_INFO_STREAM("th: " << th << " car_x: " << car_x << " car_y: " << car_y);
      
      for (int i = 0; i < int(cm.data.size()); i = i + attentiveness) {
          double cell_x = (cm.info.resolution * ((i+1) % cm.info.width)) + cm.info.origin.position.x;
          double cell_y = (cm.info.resolution * (1 + int(i/cm.info.width))) + cm.info.origin.position.y;
          double y = cell_y - car_y; //cell_x*sin(th) + cell_y*cos(th) + car_y;
          double x = cell_x - car_x; //cell_x*cos(th) - cell_y*sin(th) + car_x;
          double distance_from_car = sqrt(pow(x,2) + pow(y,2));
        if (distance_from_car <= local_search_radius) {
          double angle_from_car = atan(y / x) - th;
          if (y < 0 && x < 0) angle_from_car -= 3.141593;
          else if (y > 0 && x < 0) angle_from_car += 3.141593;
          
          if (cm.data[i] == 100) {
               weights.push_back(0);
               /*double min_angle = 0.0;
               double max_angle = 0.0;
               if (y < 0) {
                  min_angle = atan((y + cm.info.resolution/2)/(x + cm.info.resolution/2));// - th;
                  max_angle = atan((y - cm.info.resolution/2)/(x - cm.info.resolution/2));// - th;
               }
               else {
                  min_angle = atan((y + cm.info.resolution/2)/(x - cm.info.resolution/2));// - th;
                  max_angle = atan((y - cm.info.resolution/2)/(x + cm.info.resolution/2));// - th;
               }

               obstacles.push_back({min_angle, max_angle, distance_from_car});*/
          }
          else {
              signed char val = weight(distance_from_car, angle_from_car);
              weights.push_back(val);
          }
        }
        else weights.push_back(0);
          
          for (int j = 0; j < attentiveness - 1; j++) weights.push_back(0);
      }
      
      int discrepancy = int(cm.data.size()) - int(weights.size());
      if (discrepancy > 0) {
         for (int i = 0; i < discrepancy; i++) {
            weights.push_back(0);
         }
      }
      else if (discrepancy < 0) {
         for (int i = 0; i < -discrepancy; i++) {
            weights.pop_back();
         }
      }
      
      /*for (int i = 0; i < int(weights.size()); i++) {
          double cell_x = (cm.info.resolution * ((i+1) % cm.info.width)) + cm.info.origin.position.x;
          double cell_y = (cm.info.resolution * (1 + int(i/cm.info.width))) + cm.info.origin.position.y;
          double y = cell_y - car_y; //cell_x*sin(th) + cell_y*cos(th) + car_y;
          double x = cell_x - car_x; //cell_x*cos(th) - cell_y*sin(th) + car_x;
          double distance_from_car = sqrt(pow(x,2) + pow(y,2));
          double angle_from_car = atan(y / x) - th;
          if (y < 0 && x < 0) angle_from_car -= 3.141593;
          else if (y > 0 && x < 0) angle_from_car += 3.141593;
          if (behind_obstacle(obstacles,angle_from_car,distance_from_car)) weights[i] = 0;
      }*/
      
      costmap.data = weights;
      ease_cm.publish(costmap);
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "ease_costmapper");
    EaseCostmap easer;
    ros::spin();
    return 0;
}
