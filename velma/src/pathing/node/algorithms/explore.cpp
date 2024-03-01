#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/OccupancyGrid.h>

#include "math.h"

class Explore {
    
private:
    ros::NodeHandle n;
    ros::Publisher goal_pub;
    ros::Subscriber cm_sub;
    ros::Timer timer;
    
    nav_msgs::OccupancyGrid explore_cm;
    int frontiers;
    int map_width;
    double res;
    double origin_x;
    double origin_y;
    
public:
    Explore() {
        n = ros::NodeHandle("~");
        
        std::string costmap_topic;
        n.getParam("frontier_costmap_topic", costmap_topic);
        
        goal_pub = n.advertise<geometry_msgs::PoseStamped>("/explore_goal", 10);
        cm_sub = n.subscribe(costmap_topic, 10, &Explore::cm_callback, this);
        
        double reset_time;
        n.getParam("explore_reset_goal_time", reset_time);
        timer = n.createTimer(ros::Duration(reset_time), &Explore::timer_callback, this);
        
        frontiers = 0;
    }
    
    void timer_callback(const ros::TimerEvent&) {
        std::vector<int> frontier_cells;
        for (int i = 0; i < int(explore_cm.data.size()); i++) {
            if (explore_cm.data[i] != 0) frontier_cells.push_back(i);
        }
        frontiers = int(frontier_cells.size());
        
        if (frontiers != 0) {
            geometry_msgs::PoseStamped goal;
            int rand_cell = rand() % frontiers;
            int index = frontier_cells[rand_cell];
            
            int y = int(index/map_width);
            int x = index % map_width;
            goal.pose.position.x = x * res + origin_x;
            goal.pose.position.y = y * res + origin_y;
            goal.pose.orientation.w = 1.0;
            
            goal.header.stamp = ros::Time::now();
            goal.header.frame_id = "map";
            goal_pub.publish(goal);
        }
    }

    void cm_callback(const nav_msgs::OccupancyGrid& cm) {
        explore_cm = cm;
        map_width = cm.info.width;
        origin_x = cm.info.origin.position.x;
        origin_y = cm.info.origin.position.y;
        res = cm.info.resolution;
    }
}; 

int main(int argc, char** argv) {
    ros::init(argc, argv, "explorer");
    Explore frontiersman;
    ros::spin();
    return 0;
}
