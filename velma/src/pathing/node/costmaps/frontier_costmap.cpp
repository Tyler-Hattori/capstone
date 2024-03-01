#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float64.h>

#include "math.h"

class FrontierCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher cm_pub;
  ros::Subscriber map;
  ros::Publisher status;
  //ros::Timer timer;
 
  nav_msgs::OccupancyGrid frontier_cm;
    
    double min_frontier_length;
    double min_frontier_ratio;
    int attentiveness;
    double frontiers;
   
public:
  FrontierCostmap() {
    n = ros::NodeHandle("~");
      
    std::string costmap_topic;
    n.getParam("frontier_costmap_topic", costmap_topic);
      
    cm_pub = n.advertise<nav_msgs::OccupancyGrid>(costmap_topic, 10);
    status = n.advertise<std_msgs::Float64>("/frontier_status", 10);
    map = n.subscribe("/map", 1000, &FrontierCostmap::map_callback, this);
    //timer = n.createTimer(ros::Duration(2), &FrontierCostmap::timer_callback, this);
      
    n.getParam("min_frontier_length", min_frontier_length);
    n.getParam("min_frontier_ratio", min_frontier_ratio);
    n.getParam("attentiveness", attentiveness);
    attentiveness = int(100/attentiveness);
    frontiers = 0;
  }
    
  bool is_frontier(nav_msgs::OccupancyGrid cm, int idx) {
      int width = cm.info.width;
      int height = cm.info.height;
      double res = cm.info.resolution;
      int min_frontier_width_in_cells = int(min_frontier_length / res);
      int unmapped_cells_nearby = 0;
      int free_mapped_cells_nearby = 0;
      
      for (int row = int(idx/width) - int(min_frontier_width_in_cells/2); row <= int(idx/width) + int(min_frontier_width_in_cells/2); row++) {
          for (int col = int(idx % width) - int(min_frontier_width_in_cells/2); col <= int(idx % width) + int(min_frontier_width_in_cells/2); col++) {
              if (row >= 0 && row < height && col >= 0 && col < width) {
                  int i = row*width + col;
                  if (cm.data[i] > 0) return false;
                  if (cm.data[i] < 0) unmapped_cells_nearby += 1;
                  else free_mapped_cells_nearby += 1;
              }
          }
      }
      
      double ratio = double(unmapped_cells_nearby) / (unmapped_cells_nearby + free_mapped_cells_nearby);
      if (unmapped_cells_nearby == 0 || ratio < min_frontier_ratio) return false;
      return true;
  }
    
  /*void timer_callback(const ros::TimerEvent&) {
      ROS_INFO_STREAM("frontiers: " << frontiers);
  }*/
    
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
    /*std::vector<int> map_weights;
    for (int i = 0; i < int(cm.data.size()); i++) { 
        map_weights.push_back(int(cm.data[i])); 
        //ROS_INFO_STREAM("cell: " << int(cm.data[i]));
    }*/
    nav_msgs::OccupancyGrid temp;
    temp.header = cm.header;
    temp.data = cm.data;
    temp.info = cm.info;
      
    frontier_cm.header = cm.header;
    frontier_cm.info = cm.info;
      
    std::vector<signed char, std::allocator<signed char>> weights;
    frontiers = 0;
      
    for (int i = 0; i < int(cm.data.size()); i = i + attentiveness) {
        if (cm.data[i] == 0 && is_frontier(temp, i)) {
            frontiers++;
            weights.push_back(100);
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
    
    frontier_cm.data = weights;
    cm_pub.publish(frontier_cm);
    std_msgs::Float64 msg;
    msg.data = frontiers;
    status.publish(msg);
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "frontier_costmapper");
    FrontierCostmap explorer;
    ros::spin();
    return 0;
}
