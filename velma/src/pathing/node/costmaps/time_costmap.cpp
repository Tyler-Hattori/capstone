#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>

#include "math.h"

class TimeCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher time_cm;
  ros::Subscriber odom;
  ros::Subscriber map;
 
  nav_msgs::OccupancyGrid time_costmap;
   
public:
  TimeCostmap() {
    n = ros::NodeHandle("~");
    time_cm = n.advertise<nav_msgs::OccupancyGrid>("/algorithms/navigation_algoritms/time_costmap", 1000);
    odom = n.subscribe("/odom", 1000, &TimeCostmap::odom_callback, this);
    map = n.subscribe("/map", 1000, &TimeCostmap::map_callback, this);
  }
  
  void populate_costmap() {
    nav_msgs::OccupancyGrid costmap;
    
    //  TODO: populate the values of costmap according to how long its been since certain points have been seen. 
    
    time_cm.publish(costmap);
  }
  
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
    
  }
  void odom_callback(const nav_msgs::Odometry & cm) {
    
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "time_costmapper");
    TimeCostmap timer;
    ros::spin();
    return 0;
}
