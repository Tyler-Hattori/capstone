#include <ros/ros.h>

#include <ackermann_msgs/AckermannDriveStamped.h>
#include <pathing/gpiowrite.h>

class IndicatorNode {
  
private:
  ros::NodeHandle n;
  ros::Subscriber drive_sub;
  ros::Publisher left_blinker;
  ros::Publisher right_blinker;
  ros::Publisher brake_lights;
  ros::Publisher reverse_lights;
  
  std::vector<bool> output;
  
public:
  IndicatorNode () {
    n = ros::NodeHandle("~");
    
    std::string drive_topic, left_blinker_topic, right_blinker_topic, brake_lights_topic, reverse_lights_topic;
    n.getParam("drive_topic", drive_topic);
    n.getParam("left_signal_topic", left_blinker_topic);
    n.getParam("right_signal_topic", right_blinker_topic);
    n.getParam("brake_lights_topic", brake_lights_topic);
    n.getParam("reverse_lights_topic", reverse_lights_topic);
    
    left_blinker = n.advertise<std_msgs::String>(left_blinker_topic, 100);
    right_blinker = n.advertise<std_msgs::String>(right_blinker_topic, 100);
    brake_lights = n.advertise<std_msgs::String>(brake_lights_topic, 100);
    reverse_lights = n.advertise<std_msgs::String>(reverse_lights_topic, 100);
    drive_sub = n.subscribe(drive_topic, 10, &IndicatorNode::drive_callback, this);
    
    output.reserve(5);
    for (int i = 0; i < 5; i++) {
      output[i] = false;
    }
    /*
    output[0] controls left_blinker
    output[1] controls right_blinker
    output[2] controls brake_lights
    output[3] controls reverse_lights
    output[4] controls head_lights
    */
  }
  
  void publish() {
    pathing::gpiowrite on;
    pathing::gpiowrite off;
    
    on.state = true;
    off.state = false;
    
    if (output[0]) left_blinker.publish(on);
    else left_blinker.publish(off);
    
    if (output[1]) right_blinker.publish(on);
    else right_blinker.publish(off);
    
    if (output[2]) brake_lights.publish(on);
    else brake_lights.publish(off);
    
    if (output[3]) reverse_lights.publish(on);
    else reverse_lights.publish(off);
  }
  
  void drive_callback(const ackermann_msgs::AckermannDriveStamped & msg) {
    if (msg.drive.steering_angle > .1 && !output[0]) publish("left_blinker") {
      output[0] = true;
      publish();
    }
    if (msg.drive.steering_angle < -0.1 && !output[1]) publish("right_blinker"){
      output[1] = true;
      publish();
    }
    if (msg.drive.speed <= 0.5 && msg.drive.speed >= -0.5 && !output[2]) {
      output[2] = true;
      publish();
    }
    if (msg.drive.speed < 0 && !output[3]) {
      output[3] = true;
      publish();
    }
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "indicator_node");
    IndicatorNode indicator;
    ros::spin();
    return 0;
}
