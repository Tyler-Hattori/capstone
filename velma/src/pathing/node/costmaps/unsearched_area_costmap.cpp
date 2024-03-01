#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <pathing/seenPoints.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include "math.h"

struct Memory {
    //int idx;
    int x;
    int y;
    int weight;
};

class UnsearchedAreaCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher ua_cm_pub;
  ros::Publisher ua_temp_cm_pub;
  ros::Subscriber map;
  ros::Subscriber view;
  ros::Publisher status;
    
  //ros::Timer timer;
 
  nav_msgs::OccupancyGrid ua_cm;
  nav_msgs::OccupancyGrid binary_cm;
  nav_msgs::OccupancyGrid temp_cm;
  std::vector<Memory> history;
  
  double kernel_size;
  double attentiveness;
  
  double highest_weight;
    
  bool single;
  int origin_x;
  int origin_y;
  int width;
  double res;
  double ox;
  double oy;
    
  double free_cells;
  
  double local_search_radius;
   
public:
  UnsearchedAreaCostmap() {
    n = ros::NodeHandle("~");
      
    std::string costmap_topic, global_costmap_topic, seen_points_topic;
    n.getParam("unsearched_area_costmap_topic", costmap_topic);
    //n.getParam("global_costmap_topic", global_costmap_topic);
    n.getParam("seen_points_topic", seen_points_topic);
      
    ua_cm_pub = n.advertise<nav_msgs::OccupancyGrid>(costmap_topic, 10);
    ua_temp_cm_pub = n.advertise<nav_msgs::OccupancyGrid>("ua_temp_cm", 10);
    status = n.advertise<std_msgs::Float64>("/search_status", 10);
    map = n.subscribe("/map", 1000, &UnsearchedAreaCostmap::map_callback, this);
    view = n.subscribe(seen_points_topic, 1000, &UnsearchedAreaCostmap::view_callback, this);
      
    //timer = n.createTimer(ros::Duration(3), &UnsearchedAreaCostmap::timer_callback, this);
      
    n.getParam("ua_kernel_size", kernel_size);
    n.getParam("attentiveness", attentiveness);
    attentiveness = int(100/attentiveness);
      
    std::vector<signed char, std::allocator<signed char>> weights;
    weights.reserve(1);
    binary_cm.data = weights;
    highest_weight = 0.0;
    single = false;
    origin_x = 0;
    origin_y = 0;
    width = 0;
    res = 0;
    free_cells = 0;
    ox = 0;
    oy = 0;
    
    n.getParam("local_search_radius", local_search_radius);
  }
  
  double calculate_priority(int idx, nav_msgs::OccupancyGrid temp_cm) {
      double weight = 0.0;
      int width = temp_cm.info.width;
      int height = temp_cm.info.height;
      int kernel_size_in_cells = int(kernel_size/temp_cm.info.resolution);
      // int max_temp_weight = kernel_size_in_cells * kernel_size_in_cells * 100 / attentiveness;
      
      for (int row = int(idx/width) - int(kernel_size_in_cells/2); row <= int(idx/width) + int(std::ceil(kernel_size_in_cells/2)); row++) {
          for (int col = int(idx % width) - int(kernel_size_in_cells/2); col <= int(idx % width) + int(std::ceil(kernel_size_in_cells/2)); col++) {
              if (row >= 0 && row < height && col >= 0 && col < width) weight += (int)temp_cm.data[row*width + col]; 
          }
      }
      if (weight < 0) weight = 0;
      if (weight > highest_weight) highest_weight = weight;
      
      return weight;
  }
    
  std::vector<double> cell2world(int index) {
      int width = ua_cm.info.width;
      int x = int(index/width);
      int y = index % width;
      std::vector<double> coor = {x * ua_cm.info.resolution, y * ua_cm.info.resolution};
      return coor;
  }
  
  int world2cell(double x, double y) {
      int width = ua_cm.info.width;
      int u  = int(x / ua_cm.info.resolution);
      int v  = int(y / ua_cm.info.resolution);
      return u*width + v; 
  }
    
  int history_index_of(int cell) {
      for (int i = 0; i < int(history.size()); i++) {
          //if (history[i].idx == cell) return i;
          if (world2cell(history[i].x, history[i].y) == cell) return i;
      }
      return -1;
  }
    
  bool not_stored(std::vector<double> coor) {
      int berth = binary_cm.info.resolution*1.5;
      for (int i = 0; i < int(history.size()); i++) {
          if (std::abs(history[i].x - coor[0]) <= berth && std::abs(history[i].y - coor[1]) <= berth) {
              return false;
          }
      }
      return true;
  }
    
  /*void timer_callback(const ros::TimerEvent&) {
      double percent = 100.0*seen_free_cells/free_cells;
      ROS_INFO_STREAM("free cells: " << free_cells << ". mapped: " << seen_free_cells << ". " << percent << " % searched");
  }*/
   
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
      binary_cm.header = cm.header;
      binary_cm.info = cm.info;
      ua_cm.header = cm.header;
      ua_cm.info = cm.info;
      temp_cm.header = cm.header;
      temp_cm.info = cm.info;
      width = binary_cm.info.width;
      ox = cm.info.origin.position.x;
      oy = cm.info.origin.position.y;
      
      res = cm.info.resolution;
      origin_x = -int(cm.info.origin.position.x/res);
      origin_y = -int(cm.info.origin.position.y/res);
      
      std::vector<signed char, std::allocator<signed char>> weights;
      
      free_cells = 0;
      for (int i = 0; i < int(cm.data.size()); i = i + attentiveness) {
          if (cm.data[i] == 0) {
              free_cells++;
              weights.push_back(100);
          }
          else weights.push_back(-100);
          for (int j = 0; j < attentiveness - 1; j++) { weights.push_back(0); }
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
      
      binary_cm.data = weights;
  }
    
  void view_callback(const pathing::seenPoints & seen_points) {
    if (int(binary_cm.data.size()) > 0) {
      std::vector<signed char, std::allocator<signed char>> weights;
      weights = binary_cm.data;
      
      //ROS_INFO_STREAM("origin: " << origin_x << ", " << origin_y);
      for (int i = 0; i < int(seen_points.confidences.size()); i++) {
        int weight = 100 - int(seen_points.confidences[i]);
        //std::vector<double> coor = cell_to_world(int(seen_points.indices[i]));
        int x = origin_x + int(seen_points.xs[i]);
        int y = origin_y + int(seen_points.ys[i]);
        int cell = y*width + x;
        if (weights[cell] == 100) {
            std::vector<double> cell_coor = {x*res,y*res};
            if (not_stored(cell_coor)) {
                Memory new_memory = {int(seen_points.xs[i]), int(seen_points.ys[i]), weight}; //{cell, weight}; 
                history.push_back(new_memory);
            }
        }
      }
      
      /*if (!single) {
          std::vector<double> coor = cell2world(2341);
          int cell = world2cell(coor[0], coor[1]);
          ROS_INFO_STREAM("cell: 2341 --> cell: " << cell << ". ");
          single = true;
      }*/
        
      //ROS_INFO_STREAM("number of seen points: " << int(history.size()));
      for (int i = int(history.size()) - 1; i >= 0; i--) {
        int x = origin_x + history[i].x;
        int y = origin_y + history[i].y;
        int cell = y*width + x;
        // int cell =  world2cell(history[i].x, history[i].y); // history[i].idx; 
        //if (weights[cell] == 100) { 
            weights[cell] = history[i].weight;
            weights[cell+1] = 0;
            weights[cell-1] = 0;
            weights[cell+width] = 0;
            weights[cell+width-1] = 0;
            weights[cell+width+1] = 0;
            weights[cell-width] = 0;
            weights[cell-width-1] = 0;
            weights[cell-width+1] = 0;
        //}
        /*else {
            if (weights[cell] <= history[i].weight) history.erase(history.begin() + i);
            else {
                weights[cell] = history[i].weight;
                seen_free_cells++;
                history.erase(history.begin() + history_index_of(cell));
            }
        }*/
      }
      
      double unseen_free_cells = 0;
      for (int i = 0; i < int(weights.size()); i++) {
          if (weights[i] == 100) unseen_free_cells++;
      }
      
      temp_cm.data = weights;
      ua_temp_cm_pub.publish(temp_cm);
      double percent = 100 - (100.0*unseen_free_cells/free_cells);
      std_msgs::Float64 msg;
      msg.data = percent;
      status.publish(msg);
      
      std::vector<double> priorities;
        
      tf::TransformListener listener;
      tf::StampedTransform car_to_map;
      ros::Time t = ros::Time(0);
      listener.waitForTransform("map", "base_footprint", t, ros::Duration(30));
      listener.lookupTransform("map", "base_footprint", t, car_to_map);
      double car_x = car_to_map.getOrigin().getX();
      double car_y = car_to_map.getOrigin().getY();
      
      for (int i = 0; i < int(temp_cm.data.size()); i = i + attentiveness) {
          double cell_x = (res * ((i+1) % width)) + ox;
          double cell_y = (res * (1 + int(i/width))) + oy;
          double y = cell_y - car_y; 
          double x = cell_x - car_x; 
          double distance_from_car = sqrt(pow(x,2) + pow(y,2));
          if (distance_from_car <= local_search_radius) priorities.push_back(calculate_priority(i,temp_cm));
          else priorities.push_back(0);
          
          for (int j = 0; j < attentiveness - 1; j++) { priorities.push_back(0); }
      }
      
      int discrepancy = int(temp_cm.data.size()) - int(priorities.size());
      if (discrepancy > 0) {
         for (int i = 0; i < discrepancy; i++) {
            priorities.push_back(0);
         }
      }
      else if (discrepancy < 0) {
         for (int i = 0; i < -discrepancy; i++) {
            priorities.pop_back();
         }
      }
      
      std::vector<signed char, std::allocator<signed char>> normalized_weights;
      for (int i = 0; i < int(priorities.size()); i++) {
          int normalized_weight = int(100.0*priorities[i]/highest_weight);
          normalized_weights.push_back(normalized_weight);
      }
        
      ua_cm.data = normalized_weights;
      ua_cm_pub.publish(ua_cm);
    }
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "unsearched_area_costmapper");
    UnsearchedAreaCostmap area;
    ros::spin();
    return 0;
}
