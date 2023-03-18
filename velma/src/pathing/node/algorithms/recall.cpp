#include <ros/ros.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sensor_msgs/LaserScan.h>
#include <pathing/waypoints.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include "math.h"

class Recall {
    
private:
    ros::NodeHandle n_;
    ros::Publisher pub;
    ros::Subscriber waypoints_sub;
    
public:
    Recall() {
        std::string waypoints_topic;
        n.getParam("waypoints_topic", waypoints_topic);
        pub = n_.advertise<geometry_msgs::PoseWithCovarianceStamped>("/recall_goal", 1000);
        waypoints_sub = n_.subscribe(waypoints_topic, 1000, &Recall::waypoints_callback, this);
    }

    void waypoints_callback(const pathing::waypoints& waypoints) {
        for (int i = 0; i < waypoints.size(); i++) {
            navigate_to_point(waypoints.waypoints[i]);
        }
    }

    void navigate_to_point(const geometry_msgs::PoseWithCovarianceStamped& point) {
        geometry_msgs::PoseWithCovarianceStamped output;
        output.pose.position.x = point.pose.posiiton.x;
        output.pose.position.y = point.pose.posiiton.y;
        pub_.publish(output);
    }

};

int main(int argc, char** argv) {
    ros::init(argc, argv, "waypoint_pursuer");
    Recall wapf;
    ros::spin();
    return 0;
}
