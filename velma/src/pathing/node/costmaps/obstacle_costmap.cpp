#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>

#include "math.h"

class ObstacleCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher obstacle_cm;
  ros::Subscriber map;
 
  nav_msgs::OccupancyGrid obstacle_costmap;
   
public:
  ObstacleCostmap() {
    n = ros::NodeHandle("~");
      
    std::string costmap_topic;
    n.getParam("obstacle_costmap_topic", costmap_topic);
      
    obstacle_cm = n.advertise<nav_msgs::OccupancyGrid>(costmap_topic, 1000);
    map = n.subscribe("/map", 1000, &ObstacleCostmap::map_callback, this);
  }
  
  void populate_costmap() {
    nav_msgs::OccupancyGrid costmap;
    
    //  TODO: populate the values of costmap according to how long its been since certain points have been seen. 
    
    obstacle_cm.publish(costmap);
  }
  
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
    
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "obstacle_costmapper");
    ObstacleCostmap detective;
    ros::spin();
    return 0;
}
