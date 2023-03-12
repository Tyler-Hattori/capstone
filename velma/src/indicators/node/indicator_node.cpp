#include <ros/ros.h>

#include <std_msgs/String.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <std_msgs/Int8MultiArray.h>

class IndicatorNode {
  
private:
  ros::NodeHandle n;
  ros::Subscriber drive_sub;
  ros::Publisher indicator;
  
public:
  IndicatorNode () {
    n = ros::NodeHandle("~");
    
    std::string indicator_topic, drive_topic;
    n.getParam("indicator_topic", indicator_topic);
    n.getParam("drive_topic", drive_topic);
    
    indicator = n.advertise<std::String>(indicator_topic, 100);
    drive_sub = n.subscribe(drive_topic, 10, &IndicatorNode::indicator_callback, this);
  }
  
  void publish() {
    std::String ind;
    
    
    
    indicator.publish(ind);
  }
  
  void drive_callback(const ackermann_msgs::AckermannDriveStamped & msg) {
    
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "indicator_node");
    IndicatorNode indicator;
    ros::spin();
    return 0;
}
