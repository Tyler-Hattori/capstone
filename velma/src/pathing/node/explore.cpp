#include <ros/ros.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sensor_msgs/LaserScan.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include "math.h"

class Explore {
    
private:
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    
public:
    Explore() {
        pub_ = n_.advertise<geometry_msgs::PoseWithCovarianceStamped>("/explore_goal", 1000);
        sub_ = n_.subscribe("/scan", 1000, &Explore::callback, this);
    }

    void callback(const sensor_msgs::LaserScan& lidar_info) {
        
        Explore::find_frontier();
    }

    void find_frontier() {
        geometry_msgs::PoseWithCovarianceStamped output;
        
        pub_.publish(output);
    }
    
}; 

int main(int argc, char** argv) {
    ros::init(argc, argv, "explorer");
    Explore frontiersman;
    ros::spin();
    return 0;
}
