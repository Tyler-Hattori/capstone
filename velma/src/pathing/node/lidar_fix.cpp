#include <ros/ros.h>

#include <sensor_msgs/LaserScan.h>

#include "math.h"

class LaserFix {
    
private:
  ros::NodeHandle n;
  ros::Publisher scan_pub;
  ros::Subscriber scan_sub;
    
public:
    LaserFix() {
      n = ros::NodeHandle("~");
      
      scan_pub = n.advertise<sensor_msgs::LaserScan>("/scan",10);
      scan_sub = n.subscribe("/backwards_scan", 1000, &LaserFix::laser_callback, this);
    }
  
    void laser_callback(const sensor_msgs::LaserScan& msg) {
      sensor_msgs::LaserScan fixed_scan;
      fixed_scan.angle_min = msg.angle_min;
      fixed_scan.angle_max = msg.angle_max;
      fixed_scan.angle_increment = msg.angle_increment;
      fixed_scan.time_increment = msg.time_increment;
      fixed_scan.scan_time = msg.scan_time;
      fixed_scan.range_min = msg.range_min;
      fixed_scan.range_max = msg.range_max;
      fixed_scan.ranges = msg.ranges;
      fixed_scan.intensities = msg.intensities;
      fixed_scan.header = msg.header;
      fixed_scan.header.frame_id = "laser";
      scan_pub.publish(fixed_scan);
    }
}; 

int main(int argc, char** argv) {
    ros::init(argc, argv, "lidar_fixer");
    LaserFix flipper;
    ros::spin();
    return 0;
}
