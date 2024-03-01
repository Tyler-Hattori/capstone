#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <pathing/seenPoints.h>
#include <geometry_msgs/PoseStamped.h>
   
#include <tf/transform_listener.h>

#include "math.h"

struct Obstacle {
  double min_angle;
  double max_angle;
  double distance;
};

class View {
    
private:
  ros::NodeHandle n;
  ros::Publisher view_cm;
  ros::Publisher seen_points;
  ros::Subscriber map;
 
  double berth; // degrees
  double range; // meters
  double attentiveness;
   
  int origin_x;
  int origin_y;
    
public:
  View() {
    n = ros::NodeHandle("~");
      
    std::string costmap_topic, seen_points_topic;
    n.getParam("view_costmap_topic", costmap_topic);
    n.getParam("seen_points_topic", seen_points_topic);
      
    view_cm = n.advertise<nav_msgs::OccupancyGrid>(costmap_topic, 10);
    seen_points = n.advertise<pathing::seenPoints>(seen_points_topic, 10);
    map = n.subscribe("/map", 1000, &View::map_callback, this);
     
    n.getParam("pixy_berth", berth);
    n.getParam("pixy_range", range);
    n.getParam("attentiveness", attentiveness);
    attentiveness = int(100/attentiveness);
     
    origin_x = 0;
    origin_y = 0;
  }
    
  signed char weight(double rho, double theta) {
      signed char confidence = 0;
      confidence = 90;
      return confidence;
  }
   
  bool behind_obstacle(std::vector<Obstacle> obstacles, double angle, double distance) {
     for (int i = 0; i < int(obstacles.size()); i++) {
        if (angle <= obstacles[i].min_angle && angle >= obstacles[i].max_angle && distance > obstacles[i].distance) return true;
     }
     return false;
  }
  
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
      pathing::seenPoints view;
      nav_msgs::OccupancyGrid costmap;
      costmap.header = cm.header;
      costmap.info = cm.info;
      int width = cm.info.width;
     
      double res = cm.info.resolution;
      origin_x = -int(cm.info.origin.position.x/res);
      origin_y = -int(cm.info.origin.position.y/res);
      //ROS_INFO_STREAM("origin view: " << origin_x << ", " << origin_y);
     
      std::vector<signed char, std::allocator<signed char>> weights;
      std::vector<double> exes;
      std::vector<double> whys;
      std::vector<double> confidences;
     
      std::vector<Obstacle> obstacles;
      
      tf::TransformListener listener;
      tf::StampedTransform cam_to_map;
      ros::Time t = ros::Time(0);
      listener.waitForTransform("map", "base_footprint", t, ros::Duration(30));
      listener.lookupTransform("map", "base_footprint", t, cam_to_map);
      double th = tf::getYaw(cam_to_map.getRotation());
      double car_x = cam_to_map.getOrigin().getX(); //- 2*0.4318*cos(th);
      double car_y = cam_to_map.getOrigin().getY(); //- 2*0.4318*sin(th);
    
      for (int i = 0; i < int(cm.data.size()); i = i + attentiveness) {
          double cell_x = cm.info.origin.position.x + (cm.info.resolution * ((i+1) % cm.info.width));
          double cell_y = cm.info.origin.position.y + (cm.info.resolution * (1 + int(i/cm.info.width)));
          double y = cell_y - car_y; //cell_x*sin(th) + cell_y*cos(th) + car_y;
          double x = cell_x - car_x; //cell_x*cos(th) - cell_y*sin(th) + car_x;
          double distance_from_car = sqrt(pow(x,2) + pow(y,2));
          double angle_from_car = atan(y / x) - th;
          if (y < 0 && x < 0) angle_from_car -= 3.141593;
          else if (y > 0 && x < 0) angle_from_car += 3.141593;
         
          if (std::abs(angle_from_car) >= berth || distance_from_car > range) weights.push_back(0);
          else if (int(cm.data[i]) == 100) {
               weights.push_back(0);
               double min_angle = 0.0;
               double max_angle = 0.0;
               if (y < 0) {
                  min_angle = atan((y + cm.info.resolution/2)/(x + cm.info.resolution/2));// - th;
                  max_angle = atan((y - cm.info.resolution/2)/(x - cm.info.resolution/2));// - th;
               }
               else {
                  min_angle = atan((y + cm.info.resolution/2)/(x - cm.info.resolution/2));// - th;
                  max_angle = atan((y - cm.info.resolution/2)/(x + cm.info.resolution/2));// - th;
               }
             
               obstacles.push_back({min_angle, max_angle, distance_from_car});
          }
          else {
               signed char confidence = weight(distance_from_car, angle_from_car);
               weights.push_back(confidence);
               exes.push_back(i%width - origin_x);
               whys.push_back(int(i/width) - origin_y);
               //ROS_INFO_STREAM("i: " << i << " (int)(signed char)i: " << (int)(signed char)i);
               confidences.push_back(confidence);
          }
         
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
      
      for (int i = 0; i < int(weights.size()); i++) {
         if (int(weights[i]) != 0) {
            double cell_x = cm.info.origin.position.x + (cm.info.resolution * ((i+1) % cm.info.width));
            double cell_y = cm.info.origin.position.y + (cm.info.resolution * int((i)/cm.info.width));
            double y = cell_x*sin(th) + cell_y*cos(th) + car_y;
            double x = cell_x*cos(th) - cell_y*sin(th) + car_x;
            //ROS_INFO_STREAM("x: " << x << ". y: " << y);
            double distance_from_car = sqrt(pow(x,2) + pow(y,2));
            double angle_from_car = atan(y / x);// - th;
            if (y < 0 && x < 0) angle_from_car -= 3.141593;
            else if (y > 0 && x < 0) angle_from_car += 3.141593;
            
            if (behind_obstacle(obstacles,angle_from_car,distance_from_car)) weights[i] = 0;
         }
      }
      
      view.xs = exes;
      view.ys = whys;
      view.confidences = confidences;
      costmap.data = weights;
      view_cm.publish(costmap);
      seen_points.publish(view);
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "define_currently_searched_area");
    View searcher;
    ros::spin();
    return 0;
}
