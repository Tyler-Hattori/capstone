#include <ros/ros.h>

#include <ackermann_msgs/AckermannDriveStamped.h>
#include <ackermann_msgs/AckermannDrive.h>
#include <nav_msgs/Odometry.h>

#include <iostream>
#include <cstdlib>

class PuppyGuard {
    
private:
    ros::NodeHandle n;
    ros::Subscriber odom_sub;
    ros::Publisher drive_pub;

    double max_speed, max_steering_angle;
    double prev_angle=0.0;

public:
    PuppyGuard() {
        n = ros::NodeHandle("~");

        std::string drive_topic, odom_topic;
        n.getParam("guard_drive_topic", drive_topic);
        n.getParam("odom_topic", odom_topic);

        n.getParam("max_speed", max_speed);
        n.getParam("max_steering_angle", max_steering_angle);

        drive_pub = n.advertise<ackermann_msgs::AckermannDriveStamped>(drive_topic, 10);
        odom_sub = n.subscribe(odom_topic, 1, &PuppyGuard::odom_callback, this);
    }


    void odom_callback(const nav_msgs::Odometry & msg) {
        ackermann_msgs::AckermannDriveStamped drive_st_msg;
        ackermann_msgs::AckermannDrive drive_msg;

        /// SPEED CALCULATION:
        drive_msg.speed = max_speed / 2.0;


        /// STEERING ANGLE CALCULATION
        double steering_angle = max_steering_angle / 2.0;

        drive_msg.steering_angle = std::min(steering_angle, max_steering_angle);
        prev_angle = drive_msg.steering_angle;
        drive_st_msg.drive = drive_msg;

        drive_pub.publish(drive_st_msg);
    }
}; 

int main(int argc, char ** argv) {
    ros::init(argc, argv, "puppy_guarder");
    PuppyGuard circler;
    ros::spin();
    return 0;
}
