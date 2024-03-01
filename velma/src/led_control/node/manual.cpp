#include <ros/ros.h>

#include <std_msgs/String.h>
#include <led_control/gpiowrite.h>
#include <sensor_msgs/Joy.h>

class ManualLEDs {
private:
  ros::NodeHandle n;
  
  ros::Subscriber joy;
  ros::Subscriber key;
  
  ros::Publisher p0;
  ros::Publisher p1;
  ros::Publisher p2;
  ros::Publisher p3;
  
  ros::Publisher l0;
  
  ros::Publisher c0;
  ros::Publisher c1;
  
  ros::Publisher forward;
  ros::Publisher backward;
  ros::Publisher left;
  ros::Publisher right;
  
  ros::Publisher brake_lights;
  
  std::string active_controller;
    
  std::string keyboard_key_char;
  std::string web_key_char;
  std::string brake_key_char;
  std::string forward_key_char;
  std::string backward_key_char;
  std::string left_key_char;
  std::string right_key_char;
  std::string random_walk_key_char;
  std::string wall_follow_key_char;
  std::string gap_follow_key_char;
  std::string log_key_char;
  std::string recall_key_char;
  std::string return_key_char;
  std::string navigate_key_char;
  std::string explore_key_char;
  std::string search_key_char;
  
  bool brake;
  bool manual;
  bool manual_interrupt;
  
public:
  ManualLEDs () {
    n = ros::NodeHandle("~");
    
    std::string p0_topic, p1_topic, p2_topic, p3_topic;
    std::string l0_topic;
    std::string c0_topic, c1_topic;
    std::string brake_lights_topic;
    std::string forward_topic, backward_topic, left_topic, right_topic;
    n.getParam("w0_pathing_topic", p0_topic);
    n.getParam("w1_pathing_topic", p1_topic);
    n.getParam("w2_pathing_topic", p2_topic);
    n.getParam("w3_pathing_topic", p3_topic);
    n.getParam("w0_logging_topic", l0_topic);
    n.getParam("w0_controller_topic", c0_topic);
    n.getParam("w1_controller_topic", c1_topic);
    n.getParam("brake_lights_topic", brake_lights_topic);
    n.getParam("forward_topic", forward_topic);
    n.getParam("backward_topic", backward_topic);
    n.getParam("left_topic", left_topic);
    n.getParam("right_topic", right_topic);

    // Get key indices
    n.getParam("keyboard_key_char", keyboard_key_char);
    n.getParam("web_key_char", web_key_char);
    n.getParam("brake_key_char", brake_key_char);
    n.getParam("random_walk_key_char", random_walk_key_char);
    n.getParam("wall_follow_key_char", wall_follow_key_char);
    n.getParam("gap_follow_key_char", gap_follow_key_char);
    n.getParam("log_key_char", log_key_char);
    n.getParam("recall_key_char", recall_key_char);
    n.getParam("return_key_char", return_key_char);
    n.getParam("navigate_key_char", navigate_key_char);
    n.getParam("explore_key_char", explore_key_char);
    n.getParam("search_key_char", search_key_char);
    
    p0 = n.advertise<led_control::gpiowrite>(p0_topic, 100);
    p1 = n.advertise<led_control::gpiowrite>(p1_topic, 100);
    p2 = n.advertise<led_control::gpiowrite>(p2_topic, 100);
    p3 = n.advertise<led_control::gpiowrite>(p3_topic, 100);
    l0 = n.advertise<led_control::gpiowrite>(l0_topic, 100);
    c0 = n.advertise<led_control::gpiowrite>(c0_topic, 100);
    c1 = n.advertise<led_control::gpiowrite>(c1_topic, 100);
    
    led_control::gpiowrite init;
    init.state = false;
    c0.publish(init);
    init.state = true;
    c1.publish(init);
               
    forward = n.advertise<led_control::gpiowrite>(forward_topic, 100);
    backward = n.advertise<led_control::gpiowrite>(backward_topic, 100);
    left = n.advertise<led_control::gpiowrite>(left_topic, 100);
    right = n.advertise<led_control::gpiowrite>(right_topic, 100);
    
    brake_lights = n.advertise<led_control::gpiowrite>(brake_lights_topic, 100);
    
    std::string key_topic;
    n.getParam("key_topic", key_topic);
    
    key = n.subscribe(key_topic, 10, &ManualLEDs::key_callback, this);
    
    active_controller = "";
               
    brake = false;
    manual = false;
    manual_interrupt = false;
  }
  
  void key_callback(const std_msgs::String & msg) {
    led_control::gpiowrite on;
    led_control::gpiowrite off;
    on.state = true;
    off.state = false;
    brake = false;
    manual = false;
    manual_interrupt = false;
    
    if (msg.data == keyboard_key_char) { 
      active_controller = "key";
      c0.publish(on);
      c1.publish(off);
      manual = true;
    }
    else if (msg.data == web_key_char) { 
      active_controller = "web";
      c0.publish(off);
      c1.publish(on);
      manual = true;
    }
    else if (active_controller == "key") {
      if (msg.data == "up") { 
        forward.publish(on);
        backward.publish(off);
        manual_interrupt = true;
      }
      else if (msg.data == "down") {
        backward.publish(on);
        forward.publish(off);
        manual_interrupt = true;
      }
      if (msg.data == "left") { 
        left.publish(on);
        right.publish(off);
        manual_interrupt = true;
      }
      else if (msg.data == "right") { 
        right.publish(on);
        left.publish(off);
        manual_interrupt = true;
      }
      if (msg.data == brake_key_char) {
        brake = true;
      }
      else if (msg.data == random_walk_key_char) { 
        p0.publish(off);
        p1.publish(off);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.data == wall_follow_key_char) { 
        p0.publish(off);
        p1.publish(on);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.data == gap_follow_key_char) { 
        p0.publish(on);
        p1.publish(on);
        p2.publish(off);
        p3.publish(off);
      }
      else if (msg.data == log_key_char) { 
        l0.publish(on);
      }
      else if (msg.data == navigate_key_char) {
        p0.publish(off);
        p1.publish(off);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.data == return_key_char) {
        p0.publish(on);
        p1.publish(off);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.data == recall_key_char) {
        p0.publish(off);
        p1.publish(on);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.data == explore_key_char) {
        p0.publish(on);
        p1.publish(on);
        p2.publish(on);
        p3.publish(off);
      }
      else if (msg.data == search_key_char) {
        p0.publish(off);
        p1.publish(off);
        p2.publish(off);
        p3.publish(on);
      }
    }
    
    if (brake) brake_lights.publish(on);
    else brake_lights.publish(off);
    
    if (!manual_interrupt) {
      forward.publish(off);
      backward.publish(off);
      left.publish(off);
      right.publish(off);
    }
    
    if (manual) {
      p0.publish(on);
      p1.publish(on);
      p2.publish(on);
      p3.publish(on);
    }
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "led_interface");
    ManualLEDs teenager;
    ros::spin();
    return 0;
}
