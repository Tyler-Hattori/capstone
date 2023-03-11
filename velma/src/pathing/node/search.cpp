#include <ros/ros.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <nav_msgs/OccupancyGrid.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include "math.h"

class Search {
    
private:
  ros::NodeHandle n;
  ros::Publisher nav_goal;
  ros::Subscriber time_cm;
  ros::Subscriber ease_cm;
  ros::Subscriber object_cm;
  ros::Subscriber obstacle_cm;
  ros::Subscriber unsearched_area_cm;
  ros::Subscriber frontier_cm;
 
  nav_msgs::OccupancyGrid time_costmap;
  nav_msgs::OccupancyGrid ease_costmap;
  nav_msgs::OccupancyGrid object_costmap;
  nav_msgs::OccupancyGrid obstacle_costmap;
  nav_msgs::OccupancyGrid unsearched_area_costmap;
  nav_msgs::OccupancyGrid frontier_costmap;
  
  nav_msgs::OccupancyGrid sum_costmap;
  
  int time_cm_weight;
  int ease_cm_weight;
  int object_cm_weight;
  int obstacle_cm_weight;
  int unsearched_area_cm_weight;
  int frontier_cm_weight;
   
public:
  Search() {
    n = ros::NodeHandle("~");
    
    std::String time_costmap, ease_costmap, object_costmap, obstacle_costmap, unsearched_area_costmap, frontier_costmap;
    n.getParam("time_costmap_topic", time_costmap);
    n.getParam("ease_costmap_topic", ease_costmap);
    n.getParam("object_costmap_topic", object_costmap);
    n.getParam("obstacle_costmap_topic", obstacle_costmap);
    n.getParam("unsearched_area_costmap_topic", unsearched_area_costmap);
    n.getParam("frontier_costmap_topic", frontier_costmap);
      
    nav_goal = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/search_goal", 1000);
    unsearched_area_cm = n.subscribe(unsearched_area_costmap, 1000, &Search::unsearched_area_cm_callback, this);
    time_cm = n.subscribe(time_costmap, 1000, &Search::time_cm_callback, this);
    ease_cm = n.subscribe(ease_costmap, 1000, &Search::ease_cm_callback, this);
    object_cm = n.subscribe(object_costmap, 1000, &Search::object_cm_callback, this);
    obstacle_cm = n.subscribe(obstacle_costmap, 1000, &Search::obstacle_cm_callback, this);
    frontier_cm = n.subscribe(frontier_costmap, 1000, &Search::frontier_cm_callback, this);
    
    n.getParam("time_cm_weight", time_cm_weight);
    n.getParam("ease_cm_weight", ease_cm_weight);
    n.getParam("object_cm_weight", object_cm_weight);
    n.getParam("obsstacle_cm_weight", obstacle_cm_weight);
    n.getParam("unsearched_area_cm_weight", unsearched_area_cm_weight);
    n.getParam("frontier_cm_weight", frontier_cm_weight);
  }
  
  void consolidate_costmaps() {
    geometry_msgs::PoseWithCovarianceStamped goal;
    
    apply_weights();
    
    //  TODO: find the highest value in sum_costmap and populate goal with its location in the world. 
    
    nav_goal.publish(goal);
  }
  
  void apply_weights() {
    //  TODO: apply the weights. Try to do this without too many for loops.
  }
  
  void unsearched_area_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    unsearched_area_costmap = cm;
    consolidate_costmaps();
  }
  void time_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    time_costmap = cm;
    consolidate_costmaps();
  }
  void ease_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    ease_costmap = cm;
    consolidate_costmaps();
  }
  void object_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    object_costmap = cm;
    consolidate_costmaps();
  }
  void obstacle_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    obstacle_costmap = cm;
    consolidate_costmaps();
  }
  void frontier_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    frontier_costmap = cm;
    consolidate_costmaps();
  }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "searcher");
    Search bucketfinder;
    ros::spin();
    return 0;
}
