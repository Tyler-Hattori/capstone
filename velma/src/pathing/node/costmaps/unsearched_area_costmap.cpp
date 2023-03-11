#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include "math.h"

class UnsearchedAreaCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher unsearched_area_cm;
  ros::Subscriber laser;
  ros::Subscriber odom;
  ros::Subscriber map;
 
  nav_msgs::OccupancyGrid unsearched_area_costmap;
   
public:
  UnsearchedAreaCostmap() {
    n = ros::NodeHandle("~");
    unsearched_area_cm = n.advertise<nav_msgs::OccupancyGrid>("/algorithms/navigation_algoritms/unsearched_area_costmap", 1000);
    laser = n.subscribe("/scan", 1000, &UnsearchedAreaCostmap::laser_callback, this);
    odom = n.subscribe("/odom", 1000, &UnsearchedAreaCostmap::odom_callback, this);
    map = n.subscribe("/map", 1000, &UnsearchedAreaCostmap::map_callback, this);
  }
  
  void populate_costmap() {
    nav_msgs::OccupancyGrid costmap;
    
    //  TODO: populate the values of costmap according to how long its been since certain points have been seen. 
    
    unsearched_area_cm.publish(costmap);
  }
  
  void map_callback(const nav_msgs::OccupancyGrid & cm) {
    
  }
  void laser_callback(const sensor_msgs::LaserScan & cm) {
    
  }
  void odom_callback(const nav_msgs::Odometry & cm) {
    
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "unsearched_area_costmapper");
    UnsearchedAreaCostmap area;
    ros::spin();
    return 0;
}
