#include <ros/ros.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Point.h>
#include <pathing/waypoints.h>
#include <nav_msgs/Odometry.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>

#include "math.h"

struct Point {
    float x;
    float y;
};

class Log {
    
private:
  ros::NodeHandle n;
  ros::Publisher waypoints_pub;
  ros::Subscriber log_command_sub;
  ros::Subscriber odom_sub;
  
  Point last_logged_point;
  Point pos;
  std::string log_command;
  bool log;
  
  double distance_between_waypoints;
  
  std::vector<Point> waypoints;
    
public:
  Log() {
    std::string odom_topic, waypoints_topic;  
    n.getParam("odom_topic", odom_topic);
    n.getParam("waypoints_topic", waypoints_topic);
    
    n.getParam("distance_between_waypoints", distance_between_waypoints);
    
    waypoints_pub = n.advertise<pathing::waypoints>("logged_points", 1000);
    log_command_sub = n.subscribe("/pathing/log_command", 1, &Log::log_command_callback, this);
    odom_sub = n.subscribe(odom_topic, 1, &Log::odom_callback, this);
    
    last_logged_point.x = 0.0; last_logged_point.y = 0.0; 
    pos.x = 0.0; pos.y = 0.0; 
    
    log_command = "";
    log = false;
    
    waypoints.reserve(0);
  }
  
  void odom_callback(const nav_msgs::Odometry & msg) {
    if (log) {
      pos.x = msg.pose.pose.position.x;
      pos.y = msg.pose.pose.position.y;
      double dist = sqrt( pow(pos.x-last_logged_point.x,2) + pow(pos.y-last_logged_point.y,2) );
        
      if (dist >= distance_between_waypoints) {
        waypoints.push_back(pos);
        last_logged_point = pos;
        ROS_INFO("Waypoint logged");
      }
    }
  }

  void log_command_callback(const std_msgs::String& msg) {
    log_command = msg.data;
    if (log_command == "start") {
      waypoints.clear();
      last_logged_point = pos;
      log = true;
    }
    else if (log_command == "publish") {
      publish_waypoints();
      log = false;
    }
    else if (log_command == "store") {
      log = false;
    }
  }
  
  void publish_waypoints() {
    pathing::waypoints msg;
      
    for (int i = 0; i < int(waypoints.size()); i++) {
      geometry_msgs::PoseWithCovarianceStamped waypoint;
      waypoint.pose.pose.position.x = waypoints[i].x;
      waypoint.pose.pose.position.y = waypoints[i].y;
      msg.waypoints[i] = waypoint;
    }
    waypoints_pub.publish(msg);
  }

};

int main(int argc, char** argv) {
    ros::init(argc, argv, "waypoint_logger");
    Log logger;
    ros::spin();
    return 0;
}
