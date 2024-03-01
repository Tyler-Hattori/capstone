#include <ros/ros.h>

#include <ackermann_msgs/AckermannDriveStamped.h>
#include <ackermann_msgs/AckermannDrive.h>
#include <geometry_msgs/PoseStamped.h>

#include "math.h"

class Rotate {
    
private:
  ros::NodeHandle n;
  ros::Publisher drive_pub;
  ros::Subscriber drive_sub;
  ros::Subscriber goal_point;
  
  bool nav_on;
  geometry_msgs::PoseStamped goal;
  
  double max_steering_angle;
  double uturn_speed;
  double idle_speed;
  
  bool on_its_way;
  ackermann_msgs::AckermannDrive prev_drive;
    
  double start;
  double linger_time;
    
  double dir;
  bool reversing;
  double begin_timer;
  double fix_toggle_time;
    
public:
    Rotate() {
      n = ros::NodeHandle("~");
        
      std::string navigate_drive_topic, nav_goal_topic;
      n.getParam("navigate_drive_topic", navigate_drive_topic);
      n.getParam("nav_goal_topic", nav_goal_topic);
        
      n.getParam("max_steering_angle", max_steering_angle);
      n.getParam("uturn_speed", uturn_speed);
      
      drive_pub = n.advertise<ackermann_msgs::AckermannDriveStamped>(navigate_drive_topic,10);
      drive_sub = n.subscribe("/pathing/navigate_drive_raw", 1000, &Rotate::drive_callback, this);
      goal_point = n.subscribe(nav_goal_topic, 1000, &Rotate::goal_callback, this);
      
      n.getParam("idle_speed", idle_speed);
      n.getParam("linger_time", linger_time);
      n.getParam("fix_toggle_time", fix_toggle_time);
        
      nav_on = false;
      on_its_way = false;
        
      prev_drive.speed = 0.0;
      prev_drive.steering_angle = 0.0;
      start = 0.0;
      dir = 1;
      reversing = false;
      begin_timer = 0;
    }

    void drive_callback(const ackermann_msgs::AckermannDriveStamped& msg) {
      ackermann_msgs::AckermannDriveStamped drive_msg;
      drive_msg.header = msg.header;
        
      bool idle = false;
      if (msg.drive.speed < idle_speed && !idle) idle = true;
      
      double now = ros::Time::now().toSec();
      double stall = now - start;
      
      if (idle && !on_its_way) {
          if (!reversing) {
              reversing = true;
              begin_timer = now;
          }
          if ((now - begin_timer) > fix_toggle_time) {
              dir = dir * -1;
              begin_timer = now;
          }
          
          if (dir * uturn_speed > 0) drive_msg.drive.speed = 0.7;
          else drive_msg.drive.speed = dir * uturn_speed;
          
          drive_msg.drive.steering_angle = dir * max_steering_angle * (-goal.pose.position.y / std::abs(goal.pose.position.y));
          start = now;
      }
      else if (stall < linger_time) {
          if (dir * uturn_speed > 0) drive_msg.drive.speed = 0.7;
          else drive_msg.drive.speed = dir * uturn_speed;
          drive_msg.drive.steering_angle = dir * max_steering_angle * (-goal.pose.position.y / std::abs(goal.pose.position.y));
      }
      /*else if (idle && on_its_way) {
          drive_msg.drive = prev_drive;
      }*/
      else {
          drive_msg.drive = msg.drive;
          drive_msg.drive.speed = drive_msg.drive.speed * 2.0;
          reversing = false;
          prev_drive = drive_msg.drive;
          on_its_way = true;
          dir = 1;
      }
      drive_pub.publish(drive_msg);
    }
  
    void goal_callback(const geometry_msgs::PoseStamped& msg) {
      goal = msg;
      on_its_way = false;
    }
}; 

int main(int argc, char** argv) {
    ros::init(argc, argv, "nav_turner");
    Rotate rotator;
    ros::spin();
    return 0;
}
