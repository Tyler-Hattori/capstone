#include <ros/ros.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sensor_msgs/LaserScan.h>
#include <pathing/waypoints.h>
#include <nav_msgs/Odometry.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include "math.h"

struct Point {
    float x;
    float y;
};

class Recall {
    
private:
    ros::NodeHandle n;
    ros::Publisher pub;
    ros::Subscriber waypoints_sub;
    ros::Subscriber odom_sub;
    
    int pursuing_accuracy;
    bool point_reached;
    
    Point loc;
    
public:
    Recall() {
        std::string waypoints_topic, odom_topic;
        n.getParam("waypoints_topic", waypoints_topic);
        n.getParam("odom_topic", odom_topic);
        pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/recall_goal", 1000);
        waypoints_sub = n.subscribe("/algorithms/logged_points", 1, &Recall::waypoints_callback, this);
        odom_sub = n.subscribe(odom_topic, 1, &Recall::odom_callback, this);
        
        n.getParam("pursuing_accuracy", pursuing_accuracy);
        point_reached = false;
        
        loc. x = 0.0; loc.y = 0.0;
    }

    void waypoints_callback(const pathing::waypoints& waypoints) {
        for (int i = 0; i < int(waypoints.waypoints.size()); i++) {
            navigate_to_point(waypoints.waypoints[i]);
        }
    }
    
    void odom_callback(const nav_msgs::Odometry& msg) {
        loc.x = msg.pose.pose.position.x;
        loc.y = msg.pose.pose.position.y;
    }

    void navigate_to_point(const geometry_msgs::PoseWithCovarianceStamped& point) {
        point_reached = false;
        geometry_msgs::PoseWithCovarianceStamped output;
        output.pose.pose.position.x = point.pose.pose.position.x;
        output.pose.pose.position.y = point.pose.pose.position.y;
        
        while (!point_reached) {
            pub.publish(output);
            double dist = sqrt( pow(loc.x-point.pose.pose.position.x,2) + pow(loc.y-point.pose.pose.position.y,2) );
            if (dist <= pursuing_accuracy) point_reached = true;
        }
    }

};

int main(int argc, char** argv) {
    ros::init(argc, argv, "waypoint_pursuer");
    Recall wapf;
    ros::spin();
    return 0;
}
