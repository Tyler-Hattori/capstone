#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <sensor_msgs/LaserScan.h>

#include "math.h"

class FrontierCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher frontier_cm;
  ros::Subscriber laser;
  ros::Subscriber map;
 
  nav_msgs::OccupancyGrid frontier_costmap;
   
public:
  FrontierCostmap() {
    n = ros::NodeHandle("~");
      
    std::string costmap_topic;
    n.getParam("frontier_costmap_topic", costmap_topic);
      
    ease_cm = n.advertise<nav_msgs::OccupancyGrid>(costmap_topic, 1000);
    laser = n.subscribe("/scan", 1000, &FrontierCostmap::laser_callback, this);
    map = n.subscribe("/map", 1000, &FrontierCostmap::map_callback, this);
  }
  
  void populate_costmap() {
    nav_msgs::OccupancyGrid costmap;
    
    //  TODO: populate the values of costmap according to how long its been since certain points have been seen. 
    
    frontier_cm.publish(costmap);
  }
  
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
    
  }
  void laser_callback(const sensor_msgs::LaserScan & cm) {
    
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "frontier_costmapper");
    FrontierCostmap explorer;
    ros::spin();
    return 0;
}
