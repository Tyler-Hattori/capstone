#include <ros/ros.h>

#include <sensor_msgs/LaserScan.h>
#include <led_control/gpiowrite.h>

class BlindSpotNode {
  
private:
  ros::NodeHandle n;
  ros::Subscriber laser_sub;
  ros::Publisher front_left;
  ros::Publisher front_right;
  ros::Publisher back_left;
  ros::Publisher back_right;
  
  std::vector<bool> output;
  
public:
  IndicatorNode () {
    n = ros::NodeHandle("~");
    
    std::string scan_topic, front_left_topic, front_right_topic, back_left_topic, back_right_topic;
    n.getParam("scan_topic", scan_topic);
    n.getParam("front_left_sensor_topic", front_left_topic);
    n.getParam("front_right_sensor_topic", front_right_topic);
    n.getParam("back_left_sensor_topic", back_left_topic);
    n.getParam("back_right_sensor_topic", back_right_topic);
    
    front_left = n.advertise<pathing::gpiowrite>(front_left_topic, 100);
    front_right = n.advertise<pathing::gpiowrite>(front_right_topic, 100);
    back_left = n.advertise<pathing::gpiowrite>(back_left_topic, 100);
    back_right = n.advertise<pathing::gpiowrite>(back_right_topic, 100);
    laser_sub = n.subscribe(scan_topic, 10, &BlindSpotNode::laser_callback, this);
    
    output.reserve(4);
    for (int i = 0; i < 4; i++) {
      output[i] = false;
    }
    /*
    output[0] controls front_left
    output[1] controls front_right
    output[2] controls back_left
    output[3] controls back_right
    */
  }
  
  void publish() {
    pathing::gpiowrite on;
    pathing::gpiowrite off;
    
    on.state = true;
    off.state = false;
    
    if (output[0]) front_left.publish(on);
    else front_left.publish(off);
    
    if (output[1]) front_right.publish(on);
    else front_right.publish(off);
    
    if (output[2]) back_left.publish(on);
    else back_left.publish(off);
    
    if (output[3]) back_right.publish(on);
    else back_right.publish(off);
  }
  
  void check_for_close_obstacles(const sensor_msgs::LaserScan & msg) {
    
  }
  
  void laser_callback(const sensor_msgs::LaserScan & msg) {
    check_for_close_obstacles(msg);
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "blind_spot_node");
    BlindSpotNode indicator;
    ros::spin();
    return 0;
}
