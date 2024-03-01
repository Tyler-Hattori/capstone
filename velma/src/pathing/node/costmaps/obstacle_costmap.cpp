#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <pathing/PixyData.h>
#include <pathing/PixyResolution.h>
#include <tf/transform_listener.h>

#include "math.h"
#include <cmath>

class ObstacleCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher obstacle_cm;
  ros::Subscriber map;
  //ros::Subscriber bucket;
  // ros::Subscriber pixy_resolution;
    
  //bool detected;
  //int target_cell;  
    
  // double image_width;
  // double image_height;
  //double a;
  //double b;
  //double c;
  //double object_width;
  
    /*int map_width;
    int map_height;
    double map_resolution;
    double map_origin_y;
    double map_origin_x;
    double obstacle_buffer;
    double attentiveness;*/
   
public:
  ObstacleCostmap() {
    n = ros::NodeHandle("~");
      
    std::string costmap_topic;
    n.getParam("obstacle_costmap_topic", costmap_topic);
      
    obstacle_cm = n.advertise<nav_msgs::OccupancyGrid>(costmap_topic, 10);
    //bucket = n.subscribe("/bucket_visual", 10, &ObjectCostmap::bucket_callback, this);
    // pixy_resolution = n.subscribe("/pixy_resolution", 10, &ObjectCostmap::pixy_resolution_callback, this);
    map = n.subscribe("/map", 1000, &ObstacleCostmap::map_callback, this);
      
    //n.getParam("pixy_dist_coef", a);
    //n.getParam("pixy_dist_exp", b);
    //n.getParam("pixy_angle_coef", c);
    //n.getParam("object_width", object_width);
    //n.getParam("obstacle_buffer", obstacle_buffer);
    //n.getParam("obstacle_attentiveness", attentiveness);
    
    //attentiveness = int(100/attentiveness);
    //detected = false;
  }
    
  /*void tranform_and_publish(int height, int width, int x_offset, int y_offset) {
      double block_area = height*width;
      double pixy_distance = a*pow(block_area, b);
      double pixy_angle = (-x_offset+159)*(c*M_PI/180);
      
      //double pixy_x = (pixy_distance*cos(pixy_angle))/100;
      //double pixy_y = (pixy_distance*sin(pixy_angle))/100;
      //ROS_INFO_STREAM("dist: " << pixy_distance << ". ang: " << pixy_angle);
      //ROS_INFO_STREAM("pixy_x: " << pixy_x << ". pixy_y: " << pixy_y);
      tf::TransformListener listener;
      tf::StampedTransform pixy_to_map;
      ros::Time t = ros::Time(0);
      listener.waitForTransform("map", "base_footprint", t, ros::Duration(30));
      listener.lookupTransform("map", "base_footprint", t, pixy_to_map);
      double th = 1*(tf::getYaw(pixy_to_map.getRotation()));
      double car_x = 1*pixy_to_map.getOrigin().getX(); // - 2*0.4318*cos(th);
      double car_y = 1*pixy_to_map.getOrigin().getY(); // - 2*0.4318*sin(th);
      //ROS_INFO_STREAM("car_x: " << car_x << ". car_y: " << car_y);
      
      //ROS_INFO_STREAM("car_x: " << car_x << ". car_x: " << car_y);
      
      double cell_x = car_x + ((pixy_distance+0.43)/100)*(cos(th + pixy_angle)) - map_origin_x;
      double cell_y = car_y + ((pixy_distance+0.43)/100)*(sin(th + pixy_angle)) - map_origin_y;
      target_cell = int( (int(cell_y/map_resolution)-1)*map_width + int(cell_x/map_resolution) - 1);
      //ROS_INFO_STREAM("cell_x: " << cell_x << ". cell_y: " << cell_y);

  }
    
  void bucket_callback(const pathing::PixyData & msg) {
      if (!msg.blocks.empty() && int(msg.blocks[0].roi.height*msg.blocks[0].roi.width) != 0) {
          detected = true;
          tranform_and_publish((int)msg.blocks[0].roi.height, (int)msg.blocks[0].roi.width, (int)msg.blocks[0].roi.x_offset, (int)msg.blocks[0].roi.y_offset);
      }
      else detected = false;
  }*/
  /*void pixy_resolution_callback(const pathing::PixyResolution & res) {
      image_width = res.width;
      image_height = res.height;
  }*/
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
      /*map_width = cm.info.width;
      map_height = cm.info.height;
      map_resolution = cm.info.resolution;
      map_origin_x = cm.info.origin.position.x;
      map_origin_y = cm.info.origin.position.y;*/
      //ROS_INFO_STREAM("origin x: " << map_origin_x << ". origin y: " << map_origin_y);
      
      nav_msgs::OccupancyGrid costmap;
      costmap.header = cm.header;
      costmap.info = cm.info;
      //costmap.data.resize(int(cm.data.size()));
      std::vector<signed char, std::allocator<signed char>> weights;
      //weights.resize(int(cm.data.size()));
      
      //int wall_buffer_in_cells = int(obstacle_buffer/map_resolution);
      for (int i = 0; i < int(cm.data.size()); i++) {
          if (cm.data[i] == 0) weights.push_back(1);
          else weights.push_back(0);
          /*if (cm.data[i] > 0) {
            for (int row = int(i/map_width) - int(wall_buffer_in_cells/2); row <= int(i/map_width) + int(wall_buffer_in_cells/2); row++) {
              for (int col = int(i % map_width) - int(wall_buffer_in_cells/2); col <= int(i % map_width) + int(wall_buffer_in_cells/2); col++) {
                  if (row >= 0 && row < map_height && col >= 0 && col < map_width) {
                      int idx = row*map_width + col;
                      weights[idx] = 0;
                  }
              }
            }
          }
          else weights[i] = (10);*/
      }
      
      /*if (detected) {
          double object_width_in_cells = int(object_width/costmap.info.resolution);
          for (int row = int(target_cell/map_width) - int(object_width_in_cells/2); row <= int(target_cell/map_width) + int(object_width_in_cells/2); row++) {
            for (int col = int(target_cell%map_width) - int(object_width_in_cells/2); col <= int(target_cell%map_width) + int(object_width_in_cells/2); col++) {
              int i = row*map_width + col;
              if (row >= 0 && row < map_height && col >= 0 && col < map_width) weights[i] = 100;
            }
          }
      }*/
      
      costmap.data = weights;
      obstacle_cm.publish(costmap);
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "obstacle_costmapper");
    ObstacleCostmap obstacler;
    ros::spin();
    return 0;
}
