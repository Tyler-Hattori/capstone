#include <ros/ros.h>

#include <ackermann_msgs/AckermannDriveStamped.h>
#include <ackermann_msgs/AckermannDrive.h>
#include <nav_msgs/Odometry.h>

#include <iostream>
#include <cstdlib>

class Wanderer {
    
private:
    ros::NodeHandle n;
    ros::Subscriber odom_sub;
    ros::Publisher drive_pub;
    
    double max_speed, max_steering_angle;
    double prev_angle=0.0;

public:
    Wanderer() {
        n = ros::NodeHandle("~");
        
        std::string drive_topic, odom_topic;
        n.getParam("rand_drive_topic", drive_topic);
        n.getParam("odom_topic", odom_topic);

        n.getParam("max_speed", max_speed);
        n.getParam("max_steering_angle", max_steering_angle);

        drive_pub = n.advertise<ackermann_msgs::AckermannDriveStamped>(drive_topic, 10);
        odom_sub = n.subscribe(odom_topic, 1, &Wanderer::odom_callback, this);
    }


    void odom_callback(const nav_msgs::Odometry & msg) {
        ackermann_msgs::AckermannDriveStamped drive_st_msg;
        ackermann_msgs::AckermannDrive drive_msg;

        /// SPEED CALCULATION:
        double random_speed = ((double) rand() / RAND_MAX);
        drive_msg.speed = random_speed * 3.0 * max_speed / 4.0;

        /// STEERING ANGLE CALCULATION
        double random_angle_bias = ((double) rand() / RAND_MAX) - 0.5;
        double range = max_steering_angle;
        double rand_angle = range * random_angle_bias;

        drive_msg.steering_angle = std::min(std::max(prev_angle + rand_angle, -max_steering_angle), max_steering_angle);
        prev_angle = drive_msg.steering_angle;
        drive_st_msg.drive = drive_msg;

        drive_pub.publish(drive_st_msg);
    }

};

int main(int argc, char ** argv) {
    ros::init(argc, argv, "wanderer");
    Wanderer randomdriver;
    ros::spin();
    return 0;
}
