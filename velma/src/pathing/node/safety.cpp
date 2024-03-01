#include <ros/ros.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <led_control/gpiowrite.h>

struct State {
  double velocity;
  double angular_velocity;
  double x;
  double y;
};

class Safety {
  private:
  ros::NodeHandle n;
  ros::Subscriber laser;
  ros::Subscriber drive_sub;
  ros::Subscriber odom;
  ros::Publisher drive_pub;
  ros::Publisher front_safety_led;
  ros::Publisher back_safety_led;
  
  State state;
  
  bool danger_front;
  bool danger_back;
  
  double back_safety_berth;
  double back_safety_margin;
  double front_safety_berth;
  double front_safety_margin;
  
  public:
  Safety() {
    n = ros::NodeHandle("~");
    
    std::string drive_topic, front_safety_topic, back_safety_topic;
    n.getParam("drive_topic", drive_topic);
    n.getParam("front_safety_topic", front_safety_topic);
    n.getParam("back_safety_topic", back_safety_topic);
    
    drive_pub = n.advertise<ackermann_msgs::AckermannDriveStamped>(drive_topic, 10);
    front_safety_led = n.advertise<led_control::gpiowrite>(front_safety_topic, 10);
    back_safety_led = n.advertise<led_control::gpiowrite>(back_safety_topic, 10);
    drive_sub = n.subscribe("/drive", 10, &Safety::drive_callback, this);
    laser = n.subscribe("/backwards_scan", 100, &Safety::laser_callback, this);
    odom = n.subscribe("/odom", 10, &Safety::odom_callback, this);
    
    danger_front = false;
    danger_back = false;
    state = {.velocity=0.0, .angular_velocity=0.0, .x=0.0, .y=0.0};
    
    n.getParam("back_safety_berth", back_safety_berth);
    n.getParam("back_safety_margin", back_safety_margin);
    n.getParam("front_safety_berth", front_safety_berth);
    n.getParam("front_safety_margin", front_safety_margin);
    back_safety_berth = back_safety_berth*3.141593/180.0;
    front_safety_berth = front_safety_berth*3.141593/180.0;
  }
  
  void drive_callback(const ackermann_msgs::AckermannDriveStamped& msg) {
    if ((danger_front && msg.drive.speed > 0) || (danger_back && msg.drive.speed < 0)) {
      if (danger_front) ROS_INFO("There's something in front of you! Safety brake engaged.");
      else ROS_INFO("There's something behind you! Safety brake engaged.");
      ackermann_msgs::AckermannDriveStamped drive_msg;
      drive_msg.header = msg.header;
      drive_msg.drive.speed = 0;
      drive_msg.drive.steering_angle = msg.drive.steering_angle;
    }
    else
      drive_pub.publish(msg);
  }
  
  bool check_danger(sensor_msgs::LaserScan msg, std::string type) {
    led_control::gpiowrite led;
    led.state = true;
    
    if (state.velocity != 0) {
      if (type == "front") {
        double min_front_ang = front_safety_berth/2.0;
        double max_front_ang = (2.0*3.141593) - (front_safety_berth/2.0);
        for (int i = 0; i < int(msg.ranges.size()); i++) {
            double angle = msg.angle_min + i * msg.angle_increment;
            if ((angle < min_front_ang || angle > max_front_ang) && double(msg.ranges[i]) <= front_safety_margin) {
              front_safety_led.publish(led);
              return true;
            }
        }
      }
      else if (type == "back") {
        double min_back_ang = 3.141593 - (back_safety_berth/2);
        double max_back_ang = 3.141593 + (back_safety_berth/2);
        for (int i = 0; i < int(msg.ranges.size()); i++) {
            double angle = msg.angle_min + i * msg.angle_increment;
            if (angle >= min_back_ang && angle <= max_back_ang && double(msg.ranges[i]) <= back_safety_margin) {
              back_safety_led.publish(led);
              return true;
            }
        }
      }
    }
    led.state = false;
    front_safety_led.publish(led);
    back_safety_led.publish(led);
    return false; 
  }
  
  void odom_callback(const nav_msgs::Odometry & msg) {
      // Keep track of state to be used elsewhere
      state.velocity = msg.twist.twist.linear.x;
      state.angular_velocity = msg.twist.twist.angular.z;
      state.x = msg.pose.pose.position.x;
      state.y = msg.pose.pose.position.y;
  }
  
  void laser_callback(const sensor_msgs::LaserScan& msg) {
    danger_front = check_danger(msg, "front");
    danger_back = check_danger(msg, "back");
  }
  
};

int main(int argc, char ** argv) {
    ros::init(argc, argv, "safety_sensor");
    Safety s;
    ros::spin();
    return 0;
}
