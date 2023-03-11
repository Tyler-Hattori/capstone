#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>

#include "math.h"

class EaseCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher ease_cm;
  ros::Subscriber odom;
  ros::Subscriber map;
 
  nav_msgs::OccupancyGrid ease_costmap;
   
public:
  EaseCostmap() {
    n = ros::NodeHandle("~");
      
    std::string costmap_topic;
    n.getParam("ease_costmap_topic", costmap_topic);
      
    ease_cm = n.advertise<nav_msgs::OccupancyGrid>(costmap_topic, 1000);
    odom = n.subscribe("/odom", 1000, &EaseCostmap::odom_callback, this);
    map = n.subscribe("/map", 1000, &EaseCostmap::map_callback, this);
  }
  
  void populate_costmap() {
    nav_msgs::OccupancyGrid costmap;
    
    //  TODO: populate the values of costmap according to how long its been since certain points have been seen. 
    
    ease_cm.publish(costmap);
  }
  
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
    
  }
  void odom_callback(const nav_msgs::Odometry & cm) {
    
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "ease_costmapper");
    EaseCostmap easer;
    ros::spin();
    return 0;
}
