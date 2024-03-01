#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <pathing/waypoints.h>
#include <nav_msgs/OccupancyGrid.h>
#include <tf/transform_listener.h>
#include <std_msgs/String.h>

#include "math.h"

struct Point {
    double x;
    double y;
};

class Log {
    
private:
  ros::NodeHandle n;
  ros::Publisher waypoints_pub;
  ros::Subscriber log_command_sub;
  ros::Subscriber map;
    
  ros::Timer timer;
  
  std::vector<Point> waypoints;
  bool log;
    
public:
  Log() {
    std::string waypoints_topic; 
    n.getParam("waypoints_topic", waypoints_topic);
    
    waypoints_pub = n.advertise<pathing::waypoints>("/algorithms/logged_points", 1000);
    log_command_sub = n.subscribe("/pathing/log_command", 10, &Log::log_command_callback, this);
    map = n.subscribe("/map", 10, &Log::map_callback, this);
    
    double log_time;
    n.getParam("logging_rate", log_time);
    timer = n.createTimer(ros::Duration(log_time), &Log::timer_callback, this);
    
    log = false;
  }
    
  void timer_callback(const ros::TimerEvent&) {
      if (log) {
          tf::TransformListener listener;
          tf::StampedTransform car_to_map;
          ros::Time t = ros::Time(0);
          listener.waitForTransform("map", "base_footprint", t, ros::Duration(30));
          listener.lookupTransform("map", "base_footprint", t, car_to_map);
          double car_x = car_to_map.getOrigin().getX();
          double car_y = car_to_map.getOrigin().getY();
          Point new_waypoint = {car_x, car_y};
          if (car_x != 0.0 && car_y != 0.0) waypoints.push_back(new_waypoint);
          ROS_INFO_STREAM("Waypoint logged at x: " << car_x << " y: " << car_y);
      }
  }

  void log_command_callback(const std_msgs::String& msg) {
    std::string log_command = msg.data;
    if (log_command == "start") {
      waypoints.clear();
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
    
  void map_callback(const nav_msgs::OccupancyGrid& cm) {
      int width = cm.info.width;
      double res = cm.info.resolution;
      int origin_x = -int(cm.info.origin.position.x/res);
      int origin_y = -int(cm.info.origin.position.y/res);
      
  }
  
  void publish_waypoints() {
    pathing::waypoints msg;
    std::vector<double> exes;
    std::vector<double> whys;
      
    for (int i = 0; i < int(waypoints.size()); i++) {
      exes.push_back(waypoints[i].x);
      whys.push_back(waypoints[i].y);
    }
    
    msg.xs = exes;
    msg.ys = whys;
    waypoints_pub.publish(msg);
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "waypoint_logger");
    Log logger;
    ros::spin();
    return 0;
}
