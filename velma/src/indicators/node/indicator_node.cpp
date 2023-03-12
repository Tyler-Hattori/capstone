#include <ros/ros.h>

#include <std_msgs/String.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <std_msgs/Int8MultiArray.h>
#include <sensor_msgs/LaserScan.h>

class IndicatorNode {
  
private:
  ros::NodeHandle n;
  ros::Subscriber drive_sub;
  ros::Subscriber laser_sub;
  ros::Publisher indicator;
  ros::Publisher proximity;
  
public:
  IndicatorNode () {
    n = ros::NodeHandle("~");
    
    std::string indicator_topic, drive_topic, laser_topic, proximity_topic;
    n.getParam("indicator_topic", indicator_topic);
    n.getParam("proximity_topic", proximity_topic);
    n.getParam("drive_topic", drive_topic);
    n.getParam("scan_topic", laser_topic);
    
    indicator = n.advertise<std_msgs::String>(indicator_topic, 100);
    proximity = n.advertise<std_msgs::String>(proximity_topic, 100);
    drive_sub = n.subscribe(drive_topic, 10, &IndicatorNode::drive_callback, this);
    laser_sub = n.subscribe(laser_topic, 10, &IndicatorNode::laser_callback, this);
  }
  
  void publish_indicator(const std_msgs::String & msg) {
    indicator.publish(msg);
  }
  void publish_proximity(const std_msgs::String & msg) {
    proximity.publish(msg);
  }
  
  void check_for_close_obstacles(const sensor_msgs::LaserScan & scan) {
    
  }
  
  void drive_callback(const ackermann_msgs::AckermannDriveStamped & msg) {
    if (msg.drive.speed < 0) publish("reverse");
    else if (msg.drive.speed == 0) publish("brake");
    else if (msg.drive.steering_angle > .1) publish("left_blinker");
    else if (msg.drive.steering_angle < -0.1) publish("right_blinker");
  }
  void laser_callback(const sensor_msgs::LaserScan & msg) {
    check_for_close_obstacles(msg);
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "indicator_node");
    IndicatorNode indicator;
    ros::spin();
    return 0;
}
