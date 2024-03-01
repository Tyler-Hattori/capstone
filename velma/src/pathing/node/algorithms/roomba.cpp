#include <ros/ros.h>

#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PoseStamped.h>

#include <iostream>
#include <cstdlib>

class Roomba {
    
private:
    ros::NodeHandle n;
    ros::Subscriber cm_sub;
    ros::Publisher coor_pub;
    
    ros::Timer timer;
    
    double reset_time;
    double roomba_buffer;
    double res;
    int map_width;
    int map_height;
    double origin_x;
    double origin_y;
    
    std::vector<int> indeces;

public:
    Roomba() {
        n = ros::NodeHandle("~");
        
        std::string goal_topic;
        n.getParam("random_walker_nav_topic", goal_topic);

        coor_pub = n.advertise<geometry_msgs::PoseStamped>(goal_topic, 10);
        cm_sub = n.subscribe("/map", 10, &Roomba::map_callback, this);
        
        n.getParam("roomba_reset_time", reset_time);
        n.getParam("roomba_buffer", roomba_buffer);
        timer = n.createTimer(ros::Duration(reset_time), &Roomba::timer_callback, this);
    }
    
    void map_callback(const nav_msgs::OccupancyGrid& cm) {
        res = cm.info.resolution;
        map_width = cm.info.width;
        map_height = cm.info.height;
        origin_x = cm.info.origin.position.x;
        origin_y = cm.info.origin.position.y;
        
        int min_roomba_width_in_cells = int(roomba_buffer / res);
        
        std::vector<int> valid_indeces;
        for (int idx = 0; idx < int(cm.data.size()); idx++) {
            if (cm.data[idx] == 0) {
                bool valid = true;
                for (int row = int(idx/map_width) - int(min_roomba_width_in_cells/2); row <= int(idx/map_width) + int(min_roomba_width_in_cells/2); row++) {
                  for (int col = int(idx % map_width) - int(min_roomba_width_in_cells/2); col <= int(idx % map_width) + int(min_roomba_width_in_cells/2); col++) {
                      if (row >= 0 && row < map_height && col >= 0 && col < map_width) {
                          int i = row*map_width + col;
                          if (cm.data[i] > 0) {
                              valid = false;
                              break;
                          }
                      }
                  }
                  if (!valid) break;
                }
                if (valid) valid_indeces.push_back(idx);
            }
        }
        
        indeces = valid_indeces;
    }
  
    void timer_callback(const ros::TimerEvent&) {
     if (int(indeces.size()) != 0) {
      geometry_msgs::PoseStamped goal;
      goal.header.stamp = ros::Time::now();
      goal.header.frame_id = "map";
        
      int rand_index = rand() % int(indeces.size());
      int idx = indeces[rand_index];  
        
      int y = int(idx/map_width);
      int x = idx % map_width;
        
      goal.pose.position.x = x * res + origin_x;
      goal.pose.position.y = y * res + origin_y;
      goal.pose.orientation.w = 1.0;

      coor_pub.publish(goal);
     }
    }
};

int main(int argc, char ** argv) {
    ros::init(argc, argv, "roomba");
    Roomba randodrive;
    ros::spin();
    return 0;
}
