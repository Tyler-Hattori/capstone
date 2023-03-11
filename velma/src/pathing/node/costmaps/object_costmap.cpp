#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <pixy2_msgs/PixyData.h>
#include <pixy2_msgs/PixyResolution.h>

#include "math.h"

class ObjectCostmap {
    
private:
  ros::NodeHandle n;
  ros::Publisher object_cm;
  ros::Subscriber odom;
  ros::Subscriber bucket;
  ros::Subscriber pixy_resolution;
    
 
  nav_msgs::OccupancyGrid object_costmap;
   
public:
  ObjectCostmap() {
    n = ros::NodeHandle("~");
    object_cm = n.advertise<nav_msgs::OccupancyGrid>("/algorithms/navigation_algoritms/object_costmap", 1000);
    odom = n.subscribe("/odom", 1000, &ObjectCostmap::odom_callback, this);
    bucket = n.subscribe("/bucket_visual", 1000, &ObjectCostmap::bucket_callback, this);
    pixy_resolution = n.subscribe("/pixy_resolution", 1000, &ObjectCostmap::pixy_resolution_callback, this);
  }
  
  void populate_costmap() {
    nav_msgs::OccupancyGrid costmap;
    
    //  TODO: populate the values of costmap according to how long its been since certain points have been seen. 
    
    object_cm.publish(costmap);
  }
    
  void odom_callback(const nav_msgs::Odometry & cm) {
    
  }
  void bucket_callback(const pixy2_msgs::PixyData & cm) {
    
  }
  void pixy_resolution_callback(const pixy2_msgs::PixyResolution & cm) {
    
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "object_costmapper");
    ObjectCostmap objecter;
    ros::spin();
    return 0;
}
