#include <ros/ros.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sensor_msgs/LaserScan.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include "math.h"

class Recall {
    
private:
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    
public:
    Recall() {
        pub_ = n_.advertise<geometry_msgs::PoseWithCovarianceStamped>("/recall_goal", 1000);
        sub_ = n_.subscribe("/scan", 1000, &Recall::callback, this);
    }

    void callback(const sensor_msgs::LaserScan& lidar_info) {
        
        Recall::next_best_point();
    }

    void next_best_point() {
        geometry_msgs::PoseWithCovarianceStamped output;
        
        pub_.publish(output);
    }

};

int main(int argc, char** argv) {
    ros::init(argc, argv, "waypoint_pursuer");
    Recall wapf;
    ros::spin();
    return 0;
}
