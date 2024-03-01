#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>
#include <pathing/waypoints.h>

#include "math.h"

struct Point {
    double x;
    double y;
};

class Recall {
    
private:
    ros::NodeHandle n;
    ros::Publisher goal;
    ros::Subscriber waypoints_sub;
    
    ros::Timer timer;
    
    bool recall;
    pathing::waypoints waypoints;
    int idx;
    
public:
    Recall() {
        n = ros::NodeHandle("~");
        
        std::string waypoints_topic;
        n.getParam("waypoints_topic", waypoints_topic);
        
        goal = n.advertise<geometry_msgs::PoseStamped>("/recall_goal", 1000);
        waypoints_sub = n.subscribe("/algorithms/logged_points", 1, &Recall::waypoints_callback, this);
        
        double reset_time;
        n.getParam("recalling_rate", reset_time);
        timer = n.createTimer(ros::Duration(reset_time), &Recall::timer_callback, this);
        
        recall = false;
        idx = 0;
    }

    void waypoints_callback(const pathing::waypoints& msg) {
        recall = true;
        waypoints.xs = msg.xs;
        waypoints.ys = msg.ys;
        idx = 0;
    }
    
    void timer_callback(const ros::TimerEvent&) {
        if (recall) {
            geometry_msgs::PoseStamped waypoint;
            waypoint.header.stamp = ros::Time::now();
            waypoint.header.frame_id = "map";
            waypoint.pose.position.x = waypoints.xs[idx];
            waypoint.pose.position.y = waypoints.ys[idx];
            waypoint.pose.orientation.w = 1.0;
            goal.publish(waypoint);
            idx += 1;
            if (idx == int(waypoints.xs.size())) idx = 0;
        }
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "waypoint_pursuer");
    Recall wapf;
    ros::spin();
    return 0;
}
