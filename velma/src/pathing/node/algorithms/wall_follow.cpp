#include <ros/ros.h>

#include <ackermann_msgs/AckermannDriveStamped.h>
#include <sensor_msgs/LaserScan.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include "math.h"

#define KP 1.00
#define KD 0.001
#define KI 0.005
#define SERVO_OFFSET 0.00
#define ANGLE_RANGE 270
#define DISIRED_DISTANCE_RIGHT 0.9
#define DISIRED_DISTANCE_LEFT 1.20
#define CAR_LENGTH 0.50
#define PI 3.1415927

class WallFollow {

private:
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    double prev_error = 0.0;
    double prev_tmoment = ros::Time::now().toSec();
    double error = 0.0;
    double integral = 0.0;
    double velocity = 0.0;
    double del_time = 0.0;

public:
    WallFollow() {
        pub_ = n_.advertise<ackermann_msgs::AckermannDriveStamped>("/wall_follow_drive", 1000);
        sub_ = n_.subscribe("/scan", 1000, &WallFollow::callback, this);
    }

    void callback(const sensor_msgs::LaserScan& lidar_info) {
        unsigned int b_indx = (unsigned int)(floor((90.0 / 180.0 * PI - lidar_info.angle_min) / lidar_info.angle_increment));
        double b_angle = 90.0 / 180.0 * PI;
        double a_angle = 45.0 / 180.0 * PI;
        unsigned int a_indx;
        if (lidar_info.angle_min > 45.0 / 180.0 * PI) {
            a_angle = lidar_info.angle_min;
            a_indx = 0;
        } else {
            a_indx = (unsigned int)(floor((45.0 / 180.0 * PI - lidar_info.angle_min) / lidar_info.angle_increment));
        }
        double a_range = 0.0;
        double b_range = 0.0;
        if (!std::isinf(lidar_info.ranges[a_indx]) && !std::isnan(lidar_info.ranges[a_indx])) {
            a_range = lidar_info.ranges[a_indx];
        } else {
            a_range = 100.0;
        }
        if (!std::isinf(lidar_info.ranges[b_indx]) && !std::isnan(lidar_info.ranges[b_indx])) {
            b_range = lidar_info.ranges[b_indx];
        } else {
            b_range = 100.0;
        }
        
        double alpha = atan((a_range * cos(b_angle - a_angle) - b_range) / (a_range * sin(b_angle - a_angle)));
        double d_t = b_range * cos(alpha);
        double d_t1 = d_t + 1.00 * sin(alpha);
        error = DISIRED_DISTANCE_LEFT - d_t1;
        WallFollow::pid_control();
    }

    void pid_control() {
        ackermann_msgs::AckermannDriveStamped ackermann_drive_result;
        double tmoment = ros::Time::now().toSec();
        del_time = tmoment - prev_tmoment;
        integral += prev_error * del_time;
        ackermann_drive_result.drive.steering_angle = -(KP * error + KD * (error - prev_error) / del_time + KI * integral);
        prev_tmoment = tmoment;
        if (abs(ackermann_drive_result.drive.steering_angle) > 20.0 / 180.0 * PI) {
            ackermann_drive_result.drive.speed = 0.5;
            velocity = 0.5;
        } else if (abs(ackermann_drive_result.drive.steering_angle) > 10.0 / 180.0 * PI) {
            ackermann_drive_result.drive.speed = 1.0;
            velocity = 0.5;
        } else {
            ackermann_drive_result.drive.speed = 1.5;
            velocity = 0.5;
        }
        pub_.publish(ackermann_drive_result);
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "patroller");
    WallFollow patroller;
    ros::spin();
    return 0;
}
