#include <ros/ros.h>

#include <std_msgs/String.h>
#include <pathing/gpioread.h>
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
  
  ros::Subscriber r0_controller;
  ros::Subscriber r1_controller;
  
  ros::Subscriber r0_logging;
  
  ros::Subscriber r0_pathing;
  ros::Subscriber r1_pathing;
  ros::Subscriber r2_pathing;
  ros::Subscriber r3_pathing;
  
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
  
  /*bool prev_r0_controller;
  bool prev_r1_controller;
  bool prev_r0_logging;
  bool prev_r0_pathing;
  bool prev_r1_pathing;
  bool prev_r2_pathing;
  bool prev_r3_pathing;*/
  
  std::vector<bool> controller;
  bool logger;
  std::vector<bool> pather;
  
  // Web indices
  std::string joy_web_char;
  std::string keyboard_web_char;
  std::string web_web_char;
  std::string brake_web_char;
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
    
    std::string output_topic;
    n.getParam("web_topic", output_topic);
    
    std::string r0_controller_topic, r1_controller_topic;
    std::string r0_logging_topic;
    std::string r0_pathing_topic, r1_pathing_topic, r2_pathing_topic, r3_pathing_topic;
    n.getParam("r0_controller_topic", r0_controller_topic);
    n.getParam("r1_controller_topic", r1_controller_topic);
    n.getParam("r0_logging_topic", r0_logging_topic);
    n.getParam("r0_pathing_topic", r0_pathing_topic);
    n.getParam("r1_pathing_topic", r1_pathing_topic);
    n.getParam("r2_pathing_topic", r2_pathing_topic);
    n.getParam("r3_pathing_topic", r3_pathing_topic);
    
    output = n.advertise<std_msgs::String>(output_topic, 100);
    
    controller.reserve(2);
    for (int i = 0; i < 2; i++) {
      controller[i] = false;
    }
    
    pather.reserve(4);
    for (int i = 0; i < 4; i++) {
      pather[i] = false;
    }
    
    logger = false;
    
    r0_controller = n.subscribe(r0_controller_topic, 10, &ControlInterface::r0_controller_callback, this);
    r1_controller = n.subscribe(r1_controller_topic, 10, &ControlInterface::r1_controller_callback, this);
    r0_logging = n.subscribe(r0_logging_topic, 10, &ControlInterface::r0_logging_callback, this);
    r0_pathing = n.subscribe(r0_pathing_topic, 10, &ControlInterface::r0_pathing_callback, this);
    r1_pathing = n.subscribe(r1_pathing_topic, 10, &ControlInterface::r1_pathing_callback, this);
    r2_pathing = n.subscribe(r2_pathing_topic, 10, &ControlInterface::r2_pathing_callback, this);
    r3_pathing = n.subscribe(r3_pathing_topic, 10, &ControlInterface::r3_pathing_callback, this);
    
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
    
    /*prev_r0_controller = false;
    prev_r1_controller = false;
    prev_r0_logging = false;
    prev_r0_pathing = false;
    prev_r1_pathing = false;
    prev_r2_pathing = false;
    prev_r3_pathing = false;*/
    
    // Get web indices
    n.getParam("joy_web_char", joy_web_char);
    n.getParam("keyboard_web_char", keyboard_web_char);
    n.getParam("web_web_char", web_web_char);
    n.getParam("brake_web_char", brake_web_char);
    n.getParam("random_walk_web_char", random_walk_web_char);
    n.getParam("guard_web_char", guard_web_char);
    n.getParam("wall_follow_web_char", wall_follow_web_char);
    n.getParam("gap_follow_web_char", gap_follow_web_char);
    n.getParam("log_web_char", log_web_char);
    n.getParam("recall_web_char", recall_web_char);
    n.getParam("return_web_char", return_web_char);
    n.getParam("navigate_web_char", navigate_web_char);
    n.getParam("explore_web_char", explore_web_char);
    n.getParam("search_web_char", search_web_char);
  }
  
  void publish() {
    std_msgs::String msg;
    
    if (!controller[0] && !controller[1]) msg = joy_web_char;
    else if (controller[0] && !controller[1]) msg = keyboard_web_char;
    else if (!controller[0] && controller[1]) msg = web_web_char;
    else if (logger) msg = log_web_char;
    else if (!pather[0] && !pather[1] && !pather[2] && !pather[3]) msg = brake_web_char;
    else if (pather[0] && !pather[1] && !pather[2] && !pather[3]) msg = guard_web_char;
    else if (!pather[0] && pather[1] && !pather[2] && !pather[3]) msg = random_walk_web_char;
    else if (pather[0] && pather[1] && !pather[2] && !pather[3]) msg = wall_follow_web_char;
    else if (!pather[0] && !pather[1] && pather[2] && !pather[3]) msg = gap_follow_web_char;
    else if (pather[0] && !pather[1] && pather[2] && !pather[3]) msg = return_web_char;
    else if (!pather[0] && pather[1] && pather[2] && !pather[3]) msg = recall_web_char;
    else if (pather[0] && pather[1] && pather[2] && !pather[3]) msg = navigate_web_char;
    else if (!pather[0] && !pather[1] && !pather[2] && pather[3]) msg = explore_web_char;
    else if (pather[0] && !pather[1] && !pather[2] && pather[3]) msg = search_web_char;
    
    output.publish(msg);
  }
  
  void r0_controller_callback(const pathing::gpioread & msg) {
    if (msg.state != controller[0]){
      controller[0] = msg.state; 
      publish();
    }
  }
  void r1_controller_callback(const pathing::gpioread & msg) {
    if (msg.state != controller[1]){
      controller[1] = msg.state; 
      publish();
    }
  }
  void r0_logging_callback(const pathing::gpioread & msg) {
    if (msg.state != logger){
      logger = msg.state;
      publish();
    }
  }
  void r0_pathing_callback(const pathing::gpioread & msg) {
    if (msg.state != pather[0]){
      pather[0] = msg.state; 
      publish();
    }
  }
  void r1_pathing_callback(const pathing::gpioread & msg) {
    if (msg.state != pather[1]){
      pather[1] = msg.state; 
      publish();
    }
  }
  void r2_pathing_callback(const pathing::gpioread & msg) {
    if (msg.state != pather[2]){
      pather[2] = msg.state; 
      publish();
    }
  }
  void r3_pathing_callback(const pathing::gpioread & msg) {
    if (msg.state != pather[3]){
      pather[3] = msg.state; 
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
