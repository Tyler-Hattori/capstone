#include <ros/ros.h>

#include <std_msgs/String.h>
#include <pathing/gpiowrite.h>
#include <std_msgs/Int8MultiArray.h>

class LEDInterface {
private:
  ros::NodeHandle n;
  
  ros::Subscriber joy;
  ros::Subscriber key;
  ros::Subscriber indicator;
  ros::Subscriber proximity;
  
  ros::Publisher w0;
  ros::Publisher w1;
  ros::Publisher w2;
  ros::Publisher w3;
  ros::Publisher w4;
  
  std::vector<bool> input;
  
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
    
    std::string w0_topic, w1_topic, w2_topic, w3_topic, w4_topic;
    n.getParam("w0_topic", w0_topic);
    n.getParam("w1_topic", w1_topic);
    n.getParam("w2_topic", w2_topic);
    n.getParam("w3_topic", w3_topic);
    n.getParam("w4_topic", w4_topic);
    
    w0 = n.advertise<pathing::gpiowrite>(w0_topic, 100);
    w1 = n.advertise<pathing::gpiowrite>(w1_topic, 100);
    w2 = n.advertise<pathing::gpiowrite>(w2_topic, 100);
    w3 = n.advertise<pathing::gpiowrite>(w3_topic, 100);
    w4 = n.advertise<pathing::gpiowrite>(w4_topic, 100);
    
    intput.reserve(5);
    for (int i = 0; i < 5; i++) {
      input[i] = false;
    }
    
    std::string joy_topic, key_topic, indicator_topic, proximity_topic;
    n.getParam("joy_topic", joy_topic);
    n.getParam("key_topic", key_topic);
    n.getParam("indicator_topic", indicator_topic);
    n.getParam("proximity_topic", proximity_topic);
    
    joy = n.subscribe(joy_topic, 10, &LEDInterface::joy_callback, this);
    key = n.subscribe(key_topic, 10, &LEDInterface::key_callback, this);
    indicator = n.subscribe(indicator_topic, 10, &LEDInterface::indicator_callback, this);
    proximity = n.subscribe(proximity_topic, 10, &LEDInterface::proximity_callback, this);
  }
  
  void publish() {
    pathing::gpiowrite w0_msg;
    pathing::gpiowrite w1_msg;
    pathing::gpiowrite w2_msg;
    pathing::gpiowrite w3_msg;
    pathing::gpiowrite w4_msg;
    
    w0_msg.state = input[0];
    w1_msg.state = input[1];
    w2_msg.state = input[2];
    w3_msg.state = input[3];
    w4_msg.state = input[4];
    
    w0.publish(w0_msg);
    w1.publish(w1_msg);
    w2.publish(w2_msg);
    w3.publish(w3_msg);
    w4.publish(w4_msg);
  }
  
  void joy_callback(const sensor_msgs::Joy & msg) {
    if (msg.buttons[joy_button_idx]) { 
        input = {false, false, false, false, false};
        publish();
    }
    else if (msg.buttons[web_button_idx]) { 
        input = {true, false, false, false, false};
        publish();
    }
    else if (msg.buttons[key_button_idx]) { 
        input = {false, true, false, false, false};
        publish();
    }
    else if (msg.buttons[forward_button_idx]) { 
        input = {true, true, false, false, false};
        publish();
    }
    else if (msg.buttons[backward_button_idx]) { 
        input = {false, false, true, false, false};
        publish();
    }
    else if (msg.buttons[left_button_idx]) { 
        input = {true, false, true, false, false};
        publish();
    }
    else if (msg.buttons[right_button_idx]) { 
        input = {false, true, true, false, false};
        publish();
    }
    else if (msg.buttons[brake_button_idx]) { 
        input = {true, true, true, false, false};
        publish();
    }
    else if (msg.buttons[random_walk_button_idx]) { 
        input = {false, false, false, true, false};
        publish();
    }
    else if (msg.buttons[guard_button_idx]) { 
        input = {true, false, false, true, false};
        publish();
    }
    else if (msg.buttons[wall_follow_button_idx]) { 
        input = {false, true, false, true, false};
        publish();
    }
    else if (msg.buttons[gap_follow_button_idx]) { 
        input = {true, true, false, true, false};
        publish();
    }
    else if (msg.buttons[log_button_idx]) { 
        input = {false, false, true, true, false};
        publish();
    }
    else if (msg.buttons[navigate_button_idx]) {
        input = {true, false, true, true, false};
        publish();
    }
    else if (msg.buttons[return_button_idx]) {
        input = {false, true, true, true, false};
        publish();
    }
    else if (msg.buttons[recall_button_idx]) {
        input = {true, true, true, true, false};
        publish();
    }
    else if (msg.buttons[explore_button_idx]) {
        input = {false, false, false, false, true};
        publish();
    }
    else if (msg.buttons[search_button_idx]) {
        input = {true, false, false, false, true};
        publish();
    }
  }
  void key_callback(const std_msgs::String & msg) { //UNFINISHED
    if (msg.data == joy_key_char]) { 
        input = {false, false, false, false, false};
        publish();
    }
    else if (msg.data == web_key_char) { 
        input = {true, false, false, false, false};
        publish();
    }
    else if (msg.data == keyboard_key_char) { 
        input = {false, true, false, false, false};
        publish();
    }
    else if (msg.data == brake_key_char) { 
        input = {true, true, false, false, false};
        publish();
    }
    else if (msg.data == random_walk_key_char) { 
        input = {false, false, true, false, false};
        publish();
    }
    else if (msg.data == guard_key_char) { 
        input = {true, false, true, false, false};
        publish();
    }
    else if (msg.data == wall_follow_key_char) { 
        input = {false, true, true, false, false};
        publish();
    }
    else if (msg.data == gap_follow_key_char) { 
        input = {true, true, true, false, false};
        publish();
    }
    else if (msg.buttons[random_walk_button_idx]) { 
        input = {false, false, false, true, false};
        publish();
    }
    else if (msg.buttons[guard_button_idx]) { 
        input = {true, false, false, true, false};
        publish();
    }
    else if (msg.buttons[wall_follow_button_idx]) { 
        input = {false, true, false, true, false};
        publish();
    }
    else if (msg.buttons[gap_follow_button_idx]) { 
        input = {true, true, false, true, false};
        publish();
    }
    else if (msg.buttons[log_button_idx]) { 
        input = {false, false, true, true, false};
        publish();
    }
    else if (msg.buttons[navigate_button_idx]) {
        input = {true, false, true, true, false};
        publish();
    }
    else if (msg.buttons[return_button_idx]) {
        input = {false, true, true, true, false};
        publish();
    }
    else if (msg.buttons[recall_button_idx]) {
        input = {true, true, true, true, false};
        publish();
    }
    else if (msg.buttons[explore_button_idx]) {
        input = {false, false, false, false, true};
        publish();
    }
    else if (msg.buttons[search_button_idx]) {
        input = {true, false, false, false, true};
        publish();
    }
  }
  void indicator_callback(const std_msgs::String & msg) { //UNFINISHED
    if (msg.data == brake){
      output = {false, true, false, false, false};
    }
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "led_interface");
    LEDInterface teenager;
    ros::spin();
    return 0;
}
