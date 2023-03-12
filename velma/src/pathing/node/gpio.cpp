#include <ros/ros.h>

#include <std_msgs/String.h>
#include <pathing/gpio.h>
#include <std_msgs/Int8MultiArray.h>

class ControlInterface {
private:
  ros::NodeHandle n;
  ros::Publisher output;
  
  /*ros::Subscriber joy_sub;
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
  ros::Subscriber search_sub; */
  
  ros::Subscriber r0;
  ros::Subscriber r1;
  ros::Subscriber r2;
  ros::Subscriber r3;
  ros::Subscriber r4;
  
  /*bool prev_joy;
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
  bool prev_search; */
  
  bool prev_r0;
  bool prev_r1;
  bool prev_r2;
  bool prev_r3;
  bool prev_r4;
  
  std::vector<bool> input;
  
public:
  ControlInterface () {
    n = ros::NodeHandle("~");
    
    /* std::string output_topic, joy_topic, key_topic, web_topic, forward_topic, backward_topic, left_topic, right_topic, brake_topic, wander_topic, guard_topic, patrol_topic, advance_topic, return_topic, log_topic, recall_topic, explore_topic, search_topic;
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
    n.getParam("search_web_topic", search_topic); */
    
    std::string r0_topic, r1_topic, r2_topic, r3_topic, r4_topic;
    n.getParam("r0_topic", r0_topic);
    n.getParam("r1_topic", r1_topic);
    n.getParam("r2_topic", r2_topic);
    n.getParam("r3_topic", r3_topic);
    n.getParam("r4_topic", r4_topic);
    
    output = n.advertise<std_msgs::String>(output_topic, 100);
    intput.reserve(5);
    for (int i = 0; i < 5; i++) {
      input[i] = false;
    }
    
    r0 = n.subscribe(r0_topic, 10, &ControlInterface::r0_callback, this);
    r1 = n.subscribe(r1_topic, 10, &ControlInterface::r1_callback, this);
    r2 = n.subscribe(r2_topic, 10, &ControlInterface::r2_callback, this);
    r3 = n.subscribe(r3_topic, 10, &ControlInterface::r3_callback, this);
    r4 = n.subscribe(r4_topic, 10, &ControlInterface::r4_callback, this);
    
    /*joy_sub = n.subscribe(joy_topic, 10, &ControlInterface::joy_callback, this);
    key_sub = n.subscribe(key_topic, 10, &ControlInterface::key_callback, this);
    web_sub = n.subscribe(web_topic, 10, &ControlInterface::web_callback, this);
    forward_sub = n.subscribe(forward_topic, 10, &ControlInterface::forward_callback, this);
    backward_sub = n.subscribe(backward_topic, 10, &ControlInterface::backward_callback, this);
    left_sub = n.subscribe(left_topic, 10, &ControlInterface::left_callback, this);
    right_sub = n.subscribe(right_topic, 10, &ControlInterface::right_callback, this);
    brake_sub = n.subscribe(brake_topic, 10, &ControlInterface::brake_callback, this);
    wander_sub = n.subscribe(wander_topic, 10, &ControlInterface::wander_callback, this);
    guard_sub = n.subscribe(guard_topic, 10, &ControlInterface::guard_callback, this);
    patrol_sub = n.subscribe(patrol_topic, 10, &ControlInterface::patrol_callback, this);
    advance_sub = n.subscribe(advance_topic, 10, &ControlInterface::advance_callback, this);
    return_sub = n.subscribe(return_topic, 10, &ControlInterface::return_callback, this);
    log_sub = n.subscribe(log_topic, 10, &ControlInterface::log_callback, this);
    recall_sub = n.subscribe(recall_topic, 10, &ControlInterface::recall_callback, this);
    explore_sub = n.subscribe(explore_topic, 10, &ControlInterface::explore_callback, this);
    search_sub = n.subscribe(search_topic, 10, &ControlInterface::search_callback, this);
    
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
    prev_search = false; */
    
    prev_r0 = false;
    prev_r1 = false;
    prev_r2 = false;
    prev_r3 = true;
    prev_r4 = false;
  }
  
  void publish() {
    std::string msg;
    
    output.publish(msg);
  }
  
  void r0_callback(const pathing::gpio & msg) {
    if (msg.state != prev_r0){
      prev_r0 = msg.state;
      input[0] = msg.state; 
      publish();
    }
  }
  void r1_callback(const pathing::gpio & msg) {
    if (msg.state != prev_r1){
      prev_r1 = msg.state;
      input[1] = msg.state; 
      publish();
    }
  }
  void r2_callback(const pathing::gpio & msg) {
    if (msg.state != prev_r2){
      prev_r2 = msg.state;
      input[2] = msg.state; 
      publish();
    }
  }
  void r3_callback(const pathing::gpio & msg) {
    if (msg.state != prev_r3){
      prev_r3 = msg.state;
      input[3] = msg.state; 
      publish();
    }
  }
  void r4_callback(const pathing::gpio & msg) {
    if (msg.state != prev_r4){
      prev_r4 = msg.state;
      input[4] = msg.state; 
      publish();
    }
  }
  
  /* void joy_callback(const pathing::gpio & msg) {
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
  } */
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "control_interface");
    ControlInterface teenager;
    ros::spin();
    return 0;
}
