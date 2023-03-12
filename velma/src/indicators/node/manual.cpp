#include <ros/ros.h>

#include <std_msgs/String.h>
#include <pathing/gpiowrite.h>
#include <std_msgs/Int8MultiArray.h>

class ManualLEDs {
private:
  ros::NodeHandle n;
  
  ros::Subscriber joy;
  ros::Subscriber key;
  
  ros::Publisher p0;
  ros::Publisher p1;
  ros::Publisher p2;
  ros::Publisher p3;
  
  ros::Publisher log;
  
  ros::publisher c0;
  ros::publisher c1;
  
  ros::publisher brake_lights;
  
  std::string active_controller;
  
  int joy_button_idx;
  int key_button_idx;
  int web_button_idx;
  int forward_button_idx;
  int backward_button_idx;
  int left_button_idx;
  int right_button_idx;
  int brake_button_idx;
  int random_walk_button_idx;
  int guard_button_idx;
  int wall_follow_button_idx;
  int gap_follow_button_idx;
  int log_button_idx;
  int recall_button_idx;
  int return_button_idx;
  int navigate_button_idx;
  int explore_button_idx;
  int search_button_idx;
    
  std::string joy_key_char;
  std::string keyboard_key_char;
  std::string web_key_char;
  std::string brake_key_char;
  std::string forward_key_char;
  std::string backward_key_char;
  std::string left_key_char;
  std::string right_key_char;
  std::string random_walk_key_char;
  std::string guard_key_char;
  std::string wall_follow_key_char;
  std::string gap_follow_key_char;
  std::string log_key_char;
  std::string recall_key_char;
  std::string return_key_char;
  std::string navigate_key_char;
  std::string explore_key_char;
  std::string search_key_char;
    
  std::string joy_web_char;
  std::string keyboard_web_char;
  std::string web_web_char;
  std::string brake_web_char;
  std::string forward_web_char;
  std::string backward_web_char;
  std::string left_web_char;
  std::string right_web_char;
  std::string random_walk_web_char;
  std::string guard_web_char;
  std::string wall_follow_web_char;
  std::string gap_follow_web_char;
  std::string log_web_char;
  std::string recall_web_char;
  std::string return_web_char;
  std::string navigate_web_char;
  std::string explore_web_char;
  std::string search_web_char;
  
public:
  LEDInterface () {
    n = ros::NodeHandle("~");
    
    std::string p0_topic, p1_topic, p2_topic, p3_topic;
    std::string log_topic;
    std::string c0_topic, c1_topic;
    std::string brake_lights_topic;
    n.getParam("w0_pathing_topic", p0_topic);
    n.getParam("w1_pathing_topic", p1_topic);
    n.getParam("w2_pathing_topic", p2_topic);
    n.getParam("w3_pathing_topic", p3_topic);
    n.getParam("w0_logging_topic", log_topic);
    n.getParam("w0_controller_topic", c0_topic);
    n.getParam("w1_controller_topic", c1_topic);
    n.getParam("brake_lights_topic", brake_lights_topic);
    
    p0 = n.advertise<pathing::gpiowrite>(p0_topic, 100);
    p1 = n.advertise<pathing::gpiowrite>(p1_topic, 100);
    p2 = n.advertise<pathing::gpiowrite>(p2_topic, 100);
    p3 = n.advertise<pathing::gpiowrite>(p3_topic, 100);
    log = n.advertise<pathing::gpiowrite>(log_topic, 100);
    c0 = n.advertise<pathing::gpiowrite>(c0_topic, 100);
    c1 = n.advertise<pathing::gpiowrite>(c1_topic, 100);
    
    brake_lights = n.advertise<pathing::gpiowrite>(brake_lights_topic, 100);
    
    std::string joy_topic, key_topic;
    n.getParam("joy_topic", joy_topic);
    n.getParam("key_topic", key_topic);
    
    joy = n.subscribe(joy_topic, 10, &LEDInterface::joy_callback, this);
    key = n.subscribe(key_topic, 10, &LEDInterface::key_callback, this);
    
    active_controller = "";
  }
  
  void joy_callback(const sensor_msgs::Joy & msg) {
    pathing::gpiowrite on;
    pathing::gpiowrite off;
    on.state = true;
    off.state = false;
    
    if (msg.buttons[joy_button_idx]) { 
      active_controller = "joy";
      c0.publish(off);
      c1.publish(off);
    }
    else if (msg.buttons[key_button_idx]) { 
      active_controller = "key";
      c0.publish(on);
      c1.publish(off);
    }
    else if (msg.buttons[web_button_idx]) { 
      active_controller = "web";
      c0.publish(off);
      c1.publish(on);
    }
    else if (active_controller == "joy") {
      if (msg.buttons[forward_button_idx]) { 
        p0.publish(off);
        p1.publish(off);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.buttons[backward_button_idx]) {
        p0.publish(on);
        p1.publish(off);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.buttons[left_button_idx]) { 
        p0.publish(off);
        p1.publish(on);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.buttons[right_button_idx]) { 
        p0.publish(on);
        p1.publish(on);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.buttons[brake_button_idx]) {
        brake_lights.publish(on);
      }
      else if (msg.buttons[random_walk_button_idx]) { 
        p0.publish(off);
        p1.publish(off);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.buttons[guard_button_idx]) { 
        p0.publish(on);
        p1.publish(off);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.buttons[wall_follow_button_idx]) { 
        p0.publish(off);
        p1.publish(on);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.buttons[gap_follow_button_idx]) { 
        p0.publish(on);
        p1.publish(on);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.buttons[log_button_idx]) { 
        log.publish(on);
      }
      else if (msg.buttons[navigate_button_idx]) {
        p0.publish(off);
        p1.publish(off);
        p2.publish(off);
        p3.publish(on);
      }
      else if (msg.buttons[return_button_idx]) {
        p0.publish(on);
        p1.publish(off);
        p2.publish(off);
        p3.publish(on);
      }
      else if (msg.buttons[recall_button_idx]) {
        p0.publish(off);
        p1.publish(on);
        p2.publish(off);
        p3.publish(on);
      }
      else if (msg.buttons[explore_button_idx]) {
        p0.publish(on);
        p1.publish(on);
        p2.publish(off);
        p3.publish(on);
      }
      else if (msg.buttons[search_button_idx]) {
        p0.publish(off);
        p1.publish(off);
        p2.publish(on);
        p3.publish(on);
      }
    }
  }
  void key_callback(const std_msgs::String & msg) {
    pathing::gpiowrite on;
    pathing::gpiowrite off;
    on.state = true;
    off.state = false;
    
    if (msg.data == joy_key_char) { 
      active_controller = "joy";
      c0.publish(off);
      c1.publish(off);
    }
    else if (msg.data == keyboard_key_char) { 
      active_controller = "key";
      c0.publish(on);
      c1.publish(off);
    }
    else if (msg.data == web_key_char) { 
      active_controller = "web";
      c0.publish(off);
      c1.publish(on);
    }
    else if (active_controller == "key") {
      if (msg.data == forward_key_char) { 
        p0.publish(off);
        p1.publish(off);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.data == backward_key_char) {
        p0.publish(on);
        p1.publish(off);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.data == left_key_char) { 
        p0.publish(off);
        p1.publish(on);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.data == right_key_char) { 
        p0.publish(on);
        p1.publish(on);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.data == brake_key_char) {
        brake_lights.publish(on);
      }
      else if (msg.data == random_walk_key_char) { 
        p0.publish(off);
        p1.publish(off);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.data == guard_key_char) { 
        p0.publish(on);
        p1.publish(off);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.data == wall_follow_key_char) { 
        p0.publish(off);
        p1.publish(on);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.data == gap_follow_key_char) { 
        p0.publish(on);
        p1.publish(on);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.buttons[log_button_idx]) { 
        log.publish(on);
      }
      else if (msg.data == navigate_key_char) {
        p0.publish(off);
        p1.publish(off);
        p2.publish(off);
        p3.publish(on);
      }
      else if (msg.data == return_key_char) {
        p0.publish(on);
        p1.publish(off);
        p2.publish(off);
        p3.publish(on);
      }
      else if (msg.data == recall_key_char) {
        p0.publish(off);
        p1.publish(on);
        p2.publish(off);
        p3.publish(on);
      }
      else if (msg.data == explore_key_char) {
        p0.publish(on);
        p1.publish(on);
        p2.publish(off);
        p3.publish(on);
      }
      else if (msg.data == search_key_char) {
        p0.publish(off);
        p1.publish(off);
        p2.publish(on);
        p3.publish(on);
      }
    }
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "led_interface");
    ManualLEDs teenager;
    ros::spin();
    return 0;
}
