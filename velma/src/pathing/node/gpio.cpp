#include <ros/ros.h>

#include <std_msgs/String.h>
#include <pathing/gpio.h>

class WebInterface {
private:
  ros::NodeHandle n;
  ros::Publisher output;
  ros::Subscriber joy_sub;
  ros::Subscriber key_sub;
  ros::Subscriber web_sub;
  ros::Subscriber forward_sub;
  ros::Subscriber backward_sub;
  ros::Subscriber left_sub;
  ros::Subscriber right_sub;
  ros::Subscriber brake_sub;
  ros::Subscriber wander_sub;
  ros::Subscriber guard_sub;
  ros::Subscriber patrol_sub;
  ros::Subscriber advance_sub;
  ros::Subscriber log_sub;
  ros::Subscriber return_sub;
  ros::Subscriber recall_sub;
  ros::Subscriber explore_sub;
  ros::Subscriber search_sub;
  
  bool prev_joy;
  bool prev_key;
  bool prev_web;
  bool prev_forward;
  bool prev_backward;
  bool prev_left;
  bool prev_right;
  bool prev_brake;
  bool prev_wander;
  bool prev_guard;
  bool prev_patrol;
  bool prev_advance;
  bool prev_log;
  bool prev_return;
  bool prev_recall;
  bool prev_explore;
  bool prev_search;
  
public:
  WebInterface () {
    n = ros::NodeHandle("~");
    
    std::string output_topic, joy_topic, key_topic, web_topic, forward_topic, backward_topic, left_topic, right_topic, brake_topic, wander_topic, guard_topic, patrol_topic, advance_topic, return_topic, log_topic, recall_topic, explore_topic, search_topic;
    n.getParam("web_topic", output_topic);
    n.getParam("joy_web_topic", joy_topic);
    n.getParam("key_web_topic", key_topic);
    n.getParam("web_web_topic", web_topic);
    n.getParam("forward_web_topic", forward_topic);
    n.getParam("backward_web_topic", backward_topic);
    n.getParam("left_web_topic", left_topic);
    n.getParam("right_web_topic", right_topic);
    n.getParam("brake_web_topic", brake_topic);
    n.getParam("wander_web_topic", wander_topic);
    n.getParam("guard_web_topic", guard_topic);
    n.getParam("patrol_web_topic", patrol_topic);
    n.getParam("advance_web_topic", advance_topic);
    n.getParam("return_web_topic", return_topic);
    n.getParam("log_web_topic", log_topic);
    n.getParam("recall_web_topic", recall_topic);
    n.getParam("explore_web_topic", explore_topic);
    n.getParam("search_web_topic", search_topic);
    
    output = n.advertise<std_msgs::String>(output_topic, 100);
    joy_sub = n.subscribe(joy_topic, 10, &WebInterface::joy_callback, this);
    key_sub = n.subscribe(key_topic, 10, &WebInterface::key_callback, this);
    web_sub = n.subscribe(web_topic, 10, &WebInterface::web_callback, this);
    forward_sub = n.subscribe(forward_topic, 10, &WebInterface::forward_callback, this);
    backward_sub = n.subscribe(backward_topic, 10, &WebInterface::backward_callback, this);
    left_sub = n.subscribe(left_topic, 10, &WebInterface::left_callback, this);
    right_sub = n.subscribe(right_topic, 10, &WebInterface::right_callback, this);
    brake_sub = n.subscribe(brake_topic, 10, &WebInterface::brake_callback, this);
    wander_sub = n.subscribe(wander_topic, 10, &WebInterface::wander_callback, this);
    guard_sub = n.subscribe(guard_topic, 10, &WebInterface::guard_callback, this);
    patrol_sub = n.subscribe(patrol_topic, 10, &WebInterface::patrol_callback, this);
    advance_sub = n.subscribe(advance_topic, 10, &WebInterface::advance_callback, this);
    return_sub = n.subscribe(return_topic, 10, &WebInterface::return_callback, this);
    log_sub = n.subscribe(log_topic, 10, &WebInterface::log_callback, this);
    recall_sub = n.subscribe(recall_topic, 10, &WebInterface::recall_callback, this);
    explore_sub = n.subscribe(explore_topic, 10, &WebInterface::explore_callback, this);
    search_sub = n.subscribe(search_topic, 10, &WebInterface::search_callback, this);
    
    prev_joy = false;
    prev_key = false;
    prev_web = false;
    prev_forward = false;
    prev_backward = false;
    prev_left = false;
    prev_right = false;
    prev_brake = false;
    prev_wander = false;
    prev_guard = false;
    prev_patrol = false;
    prev_advance = true;
    prev_log = false;
    prev_return = false;
    prev_recall = false;
    prev_explore = true;
    prev_search = false;
  }
  
  void publish(const std_msgs::String msg) {
    output.publish(msg);
  }
  
  void joy_callback(const pathing::gpio & msg) {
    if (msg.state != prev_joy){
      prev_joy = msg.state;
      std_msgs::String output;
      output.data = "joystick";
      publish(output);
    }
  }
  void key_callback(const pathing::gpio & msg) {
    if (msg.state != prev_key){
      prev_key = msg.state;
      std_msgs::String output;
      output.data = "keyboard";
      publish(output);
    }
  }
  void web_callback(const pathing::gpio & msg) {
    if (msg.state != prev_web){
      prev_web = msg.state;
      std_msgs::String output;
      output.data = "web";
      publish(output);
    }
  }
  void forward_callback(const pathing::gpio & msg) {
    if (msg.state != prev_forward){
      prev_forward = msg.state;
      std_msgs::String output;
      output.data = "forward";
      publish(output);
    }
  }
  void backward_callback(const pathing::gpio & msg) {
    if (msg.state != prev_backward){
      prev_backward = msg.state;
      std_msgs::String output;
      output.data = "backward";
      publish(output);
    }
  }
  void left_callback(const pathing::gpio & msg) {
    if (msg.state != prev_left){
      prev_left = msg.state;
      std_msgs::String output;
      output.data = "left";
      publish(output);
    }
  }
  void right_callback(const pathing::gpio & msg) {
    if (msg.state != prev_right){
      prev_right = msg.state;
      std_msgs::String output;
      output.data = "right";
      publish(output);
    }
  }
  void brake_callback(const pathing::gpio & msg) {
    if (msg.state != prev_brake){
      prev_brake = msg.state;
      std_msgs::String output;
      output.data = "brake";
      publish(output);
    }
  }
  void wander_callback(const pathing::gpio & msg) {
    if (msg.state != prev_wander){
      prev_wander = msg.state;
      std_msgs::String output;
      output.data = "wander";
      publish(output);
    }
  }
  void guard_callback(const pathing::gpio & msg) {
    if (msg.state != prev_guard){
      prev_guard = msg.state;
      std_msgs::String output;
      output.data = "guard";
      publish(output);
    }
  }
  void patrol_callback(const pathing::gpio & msg) {
    if (msg.state != prev_patrol){
      prev_patrol = msg.state;
      std_msgs::String output;
      output.data = "patrol";
      publish(output);
    }
  }
  void advance_callback(const pathing::gpio & msg) {
    if (msg.state != prev_advance){
      prev_advance = msg.state;
      std_msgs::String output;
      output.data = "advance";
      publish(output);
    }
  }
  void return_callback(const pathing::gpio & msg) {
    if (msg.state != prev_return){
      prev_return = msg.state;
      std_msgs::String output;
      output.data = "return";
      publish(output);
    }
  }
  void log_callback(const pathing::gpio & msg) {
    if (msg.state != prev_log){
      prev_log = msg.state;
      std_msgs::String output;
      output.data = "log";
      publish(output);
    }
  }
  void recall_callback(const pathing::gpio & msg) {
    if (msg.state != prev_recall){
      prev_recall = msg.state;
      std_msgs::String output;
      output.data = "recall";
      publish(output);
    }
  }
  void explore_callback(const pathing::gpio & msg) {
    if (msg.state != prev_explore){
      prev_explore = msg.state;
      std_msgs::String output;
      output.data = "explore";
      publish(output);
    }
  }
  void search_callback(const pathing::gpio & msg) {
    if (msg.state != prev_search){
      prev_search = msg.state;
      std_msgs::String output;
      output.data = "search";
      publish(output);
    }
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "web_interface");
    WebInterface teenager;
    ros::spin();
    return 0;
}
