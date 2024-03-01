#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <pathing/PixyData.h>
#include <pathing/PixyResolution.h>
#include <tf/transform_listener.h>
#include <led_control/gpiowrite.h>
#include <pathing/calcTimes.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include "math.h"

struct Coor {
    double x;
    double y;
};

class Search {
    
private:
  ros::NodeHandle n;
  ros::Publisher nav_goal;
  ros::Publisher sum_cm;
  ros::Subscriber time_cm;
  ros::Subscriber ease_cm;
  ros::Subscriber obstacle_cm;
  ros::Subscriber unsearched_area_cm;
  ros::Subscriber frontier_cm;
  ros::Subscriber bucket;
  ros::Subscriber search_status;
  ros::Subscriber frontier_status;
  ros::Publisher detection_led;
  ros::Publisher calc_times;
 
  nav_msgs::OccupancyGrid sum_costmap;
  nav_msgs::OccupancyGrid time_costmap;
  nav_msgs::OccupancyGrid ease_costmap;
  nav_msgs::OccupancyGrid obstacle_costmap;
  nav_msgs::OccupancyGrid unsearched_area_costmap;
  nav_msgs::OccupancyGrid frontier_costmap;
    
  ros::Timer timer;
  double pub_time;
  
  
  // double time_cm_weight;
  double ease_cm_weight;
  // double obstacle_cm_weight;
  double unsearched_area_cm_weight;
  double frontier_cm_weight;
  
  bool environment_mapped;
  bool environment_searched;
    
  bool frontier_cm_recieved;
  bool ua_cm_recieved;
  bool ease_cm_recieved;
  bool time_cm_recieved;
  bool obstacle_cm_recieved;
    
  bool found;
  double a;
  double b;
  double c;
  double stopping_distance;
    
  double map_origin_y;
  double map_origin_x;
    
  double search_detail;
  double frontier_detail;
    
  bool use_ease;
  bool use_time;
    
  int count;
  
  double ease_calc_time;
  double ua_calc_time;
  double frontier_calc_time;
  double obstacle_calc_time;
  double time_calc_time;
    
  double ease_ave_time;
  double ua_ave_time;
  double frontier_ave_time;
  double obstacle_ave_time;
  double time_ave_time;
    
  int calc_time_depth;
  double area;
  double res;
    
  std::vector<double> ease_calc_times;
  std::vector<double> ua_calc_times;
  std::vector<double> frontier_calc_times;
  std::vector<double> obstacle_calc_times;
  std::vector<double> time_calc_times;
  
  pathing::calcTimes calc_times_msg;
    
public:
  Search() {
    n = ros::NodeHandle("~");
    
    std::string sum_costmap_topic, time_costmap_topic, ease_costmap_topic, obstacle_costmap_topic, unsearched_area_costmap_topic, frontier_costmap_topic, detection_topic;
    n.getParam("sum_costmap_topic", sum_costmap_topic);
    n.getParam("time_costmap_topic", time_costmap_topic);
    n.getParam("ease_costmap_topic", ease_costmap_topic);
    n.getParam("obstacle_costmap_topic", obstacle_costmap_topic);
    n.getParam("unsearched_area_costmap_topic", unsearched_area_costmap_topic);
    n.getParam("frontier_costmap_topic", frontier_costmap_topic);
    n.getParam("detection_topic", detection_topic);
      
    nav_goal = n.advertise<geometry_msgs::PoseStamped>("/search_goal", 10);
    sum_cm = n.advertise<nav_msgs::OccupancyGrid>(sum_costmap_topic, 10);
    unsearched_area_cm = n.subscribe(unsearched_area_costmap_topic, 100, &Search::unsearched_area_cm_callback, this);
    time_cm = n.subscribe(time_costmap_topic, 100, &Search::time_cm_callback, this);
    ease_cm = n.subscribe(ease_costmap_topic, 100, &Search::ease_cm_callback, this);
    obstacle_cm = n.subscribe(obstacle_costmap_topic, 100, &Search::obstacle_cm_callback, this);
    frontier_cm = n.subscribe(frontier_costmap_topic, 100, &Search::frontier_cm_callback, this);
    bucket = n.subscribe("/bucket_visual", 100, &Search::bucket_callback, this);
    search_status = n.subscribe("/search_status", 100, &Search::search_status_callback, this);
    frontier_status = n.subscribe("/frontier_status", 100, &Search::frontier_status_callback, this);
    detection_led = n.advertise<led_control::gpiowrite>(detection_topic, 10);
    calc_times = n.advertise<pathing::calcTimes>("/calc_times", 10);
    
    n.getParam("search_goal_update_time", pub_time);
    timer = n.createTimer(ros::Duration(pub_time), &Search::timer_callback, this);
    
    //n.getParam("time_cm_weight", time_cm_weight);
    n.getParam("ease_cm_weight", ease_cm_weight);
    //n.getParam("object_cm_weight", object_cm_weight);
    n.getParam("unsearched_area_cm_weight", unsearched_area_cm_weight);
    n.getParam("frontier_cm_weight", frontier_cm_weight);
      
    n.getParam("pixy_dist_coef", a);
    n.getParam("pixy_dist_exp", b);
    n.getParam("pixy_angle_coef", c);
    n.getParam("stopping_distance", stopping_distance);
    n.getParam("search_detail", search_detail);
    n.getParam("frontier_detail", frontier_detail);
     
    environment_mapped = false;  
    environment_searched = false;
      
    frontier_cm_recieved = false;
    ua_cm_recieved = false;
    ease_cm_recieved = false;
    obstacle_cm_recieved = false;
    time_cm_recieved = false;
      
    found = false;
      
    map_origin_x = 0.0;
    map_origin_y = 0.0;
      
    n.getParam("use_ease_cm", use_ease);
    n.getParam("use_time_cm", use_time);
      
    count = 0;
    
    double now = ros::Time::now().toSec();
    ease_calc_time = now;
    ua_calc_time = now;
    time_calc_time = now;
    frontier_calc_time = now;
    obstacle_calc_time = now;
      
    calc_time_depth = 20;
    
    ease_ave_time = 0.0;
    ua_ave_time = 0.0;
    frontier_ave_time = 0.0;
    obstacle_ave_time = 0.0;
    time_ave_time = 0.0;
    
    area = 0;
    res = 0.2;
  }
  
  void tranform_and_publish(int height, int width, int x_offset, int y_offset) {
      double block_area = height*width;
      double pixy_distance = a*pow(block_area, b);
      double pixy_angle = (-x_offset+159)*(c*M_PI/180);
      
      //double pixy_x = (pixy_distance*cos(pixy_angle))/100;
      //double pixy_y = (pixy_distance*sin(pixy_angle))/100;
      //ROS_INFO_STREAM("dist: " << pixy_distance << ". ang: " << pixy_angle);
      //ROS_INFO_STREAM("pixy_x: " << pixy_x << ". pixy_y: " << pixy_y);
      tf::TransformListener listener;
      tf::StampedTransform pixy_to_map;
      ros::Time t = ros::Time(0);
      listener.waitForTransform("map", "base_footprint", t, ros::Duration(30));
      listener.lookupTransform("map", "base_footprint", t, pixy_to_map);
      double th = (tf::getYaw(pixy_to_map.getRotation()));
      double car_x = pixy_to_map.getOrigin().getX(); // - 2*0.4318*cos(th);
      double car_y = pixy_to_map.getOrigin().getY(); // - 2*0.4318*sin(th);
      //ROS_INFO_STREAM("car_x: " << car_x << ". car_y: " << car_y);
      
      //ROS_INFO_STREAM("car_x: " << car_x << ". car_x: " << car_y);
      
      double cell_x = car_x + ((pixy_distance+43-stopping_distance)/100)*(cos(th + pixy_angle));// - map_origin_x;
      double cell_y = car_y + ((pixy_distance+43-stopping_distance)/100)*(sin(th + pixy_angle));// - map_origin_y;
      //target_cell = int( (int(cell_y/map_resolution)-1)*map_width + int(cell_x/map_resolution) - 1);
      //ROS_INFO_STREAM("origin_x: " << map_origin_x << ". origin_y: " << map_origin_y);
      
      geometry_msgs::PoseStamped goal;
      goal.header.stamp = ros::Time::now();
      goal.header.frame_id = "map";
      goal.pose.position.x = cell_x;
      goal.pose.position.y = cell_y;
      goal.pose.orientation.w = 1.0;
      nav_goal.publish(goal);
  }
    
  void bucket_callback(const pathing::PixyData & msg) {
      //count++;
      if (!msg.blocks.empty() && int(msg.blocks[0].age) >= 200) { // int(msg.blocks[0].roi.height*msg.blocks[0].roi.width) != 0) {
          found = true;
          ROS_INFO_STREAM("Found the object.");
          led_control::gpiowrite on;
          on.state = true;
          detection_led.publish(on);
          tranform_and_publish((int)msg.blocks[0].roi.height, (int)msg.blocks[0].roi.width, (int)msg.blocks[0].roi.x_offset, (int)msg.blocks[0].roi.y_offset);
          //pub_time = 25;
          //timer = n.createTimer(ros::Duration(pub_time), &Search::timer_callback, this);
      }
      else {
          found = false;
          led_control::gpiowrite off;
          off.state = false;
          detection_led.publish(off);
      }
  }
  
  void timer_callback(const ros::TimerEvent&) {
      if (!found && obstacle_cm_recieved && ua_cm_recieved && frontier_cm_recieved && (ease_cm_recieved || !use_ease) && (time_cm_recieved || !use_time)) {
        found = false;
        geometry_msgs::PoseStamped goal;
        sum_costmap.header = obstacle_costmap.header;
        sum_costmap.info = obstacle_costmap.info;

        apply_weights();
        Coor goal_point = find_best_goal();
          
        goal.header = sum_costmap.header;
        goal.pose.position.x = goal_point.x;
        goal.pose.position.y = goal_point.y;
        goal.pose.orientation.w = 1.0;

        nav_goal.publish(goal);
      }
      
        ua_cm_recieved = false;
        ease_cm_recieved = false;
        obstacle_cm_recieved = false;
        time_cm_recieved = false;
        frontier_cm_recieved = false;
      
      calc_times_msg.ua = ua_ave_time;
      calc_times_msg.frontier = frontier_ave_time;
      calc_times_msg.ease = ease_ave_time;
      calc_times_msg.time = time_ave_time;
      calc_times_msg.obstacle = obstacle_ave_time;
      calc_times_msg.map_area = area * res * res * 3.28084 * 3.28084;
      calc_times.publish(calc_times_msg);
  }
  
  void apply_weights() {
    std::vector<double> weights;
    double highest_weight = 0.0;

    for (int i = 0; i < int(obstacle_costmap.data.size()); i++) {
        double weight = 1;
        if (frontier_cm_recieved) weight += frontier_cm_weight*double(frontier_costmap.data[i]);
        if (ua_cm_recieved) weight += unsearched_area_cm_weight*double(unsearched_area_costmap.data[i]); 
        if (environment_mapped && environment_searched && time_cm_recieved && use_time) weight += double(time_costmap.data[i]);
        if (ease_cm_recieved && use_ease) weight *= double(ease_costmap.data[i])/100.0;
        if (obstacle_cm_recieved) weight *= double(obstacle_costmap.data[i]);
            
        if (weight > highest_weight) highest_weight = weight;
        weights.push_back(weight);
    }
  
    // normalize
    std::vector<signed char, std::allocator<signed char>> normalized_weights;
    for (int i = 0; i < int(weights.size()); i++) {
        normalized_weights.push_back( (signed char)(100 * ( weights[i] / highest_weight )) );
    }
    sum_costmap.data = normalized_weights;
    sum_cm.publish(sum_costmap);
  }
    
  Coor find_best_goal() {
      std::vector<int> best_cells;
      int highest_weight = 0;
      for (int i = 0; i < int(sum_costmap.data.size()); i++) {
          int cell_weight = int(sum_costmap.data[i]);
          if (cell_weight > highest_weight) {
              best_cells.clear();
              best_cells.push_back(i);
              highest_weight = cell_weight;
          }
          else if (cell_weight == highest_weight) best_cells.push_back(i);
      }
      
      int rand_cell = rand() % int(best_cells.size());
      int best_cell = best_cells[rand_cell];
      
      std::vector<double> coor = cell_to_world(best_cell);
      Coor best_goal = {coor[0], coor[1]};
      
      return best_goal;
  }
              
  std::vector<double> cell_to_world(int idx) {
      int width = sum_costmap.info.width;
      int y = int(idx/width);
      int x = idx % width;
      std::vector<double> coor = {x * sum_costmap.info.resolution + sum_costmap.info.origin.position.x,
                                  y * sum_costmap.info.resolution + sum_costmap.info.origin.position.y};
      return coor;
  }
    
  /*bool is_environment_mapped(nav_msgs::OccupancyGrid & cm) {
    for (int i = 0; i < int(cm.data.size()); i++) {
        if (cm.data[i] != 0) return false;
    }
    return true;
  }
    
  bool is_environment_searched(nav_msgs::OccupancyGrid & cm) {
    for (int i = 0; i < int(cm.data.size()); i++) {
        if (cm.data[i] == 100) return false;
    }
    return true;
  }*/
    
  double calculate_average_calc_time(std::vector<double> times, int depth) {
      double total = 0.0;
      for (int i = int(times.size()) - 1; i >= int(times.size()) - depth; i--) {
          total += times[i];
      }
      return total / double(depth);
  }
              
  void unsearched_area_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    unsearched_area_costmap = cm;
    ua_cm_recieved = true;
    ua_calc_times.push_back(ros::Time::now().toSec() - ua_calc_time);
    ua_ave_time = calculate_average_calc_time(ua_calc_times, calc_time_depth);
    ua_calc_time = ros::Time::now().toSec();
    //environment_searched = is_environment_searched(unsearched_area_costmap);
  }
  void time_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    time_costmap = cm;
    time_cm_recieved = true;
    time_calc_times.push_back(ros::Time::now().toSec() - time_calc_time);
    time_ave_time = calculate_average_calc_time(time_calc_times, calc_time_depth);
    time_calc_time = ros::Time::now().toSec();
  }
  void ease_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    ease_costmap = cm;
    ease_cm_recieved = true;
    ease_calc_times.push_back(ros::Time::now().toSec() - ease_calc_time);
    ease_ave_time = calculate_average_calc_time(ease_calc_times, calc_time_depth);
    ease_calc_time = ros::Time::now().toSec();
  }
  void obstacle_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    map_origin_x = cm.info.origin.position.x;
    map_origin_y = cm.info.origin.position.y;
    area = cm.info.width * cm.info.height;
    res = cm.info.resolution;
    obstacle_costmap = cm;
    obstacle_cm_recieved = true;
    obstacle_calc_times.push_back(ros::Time::now().toSec() - obstacle_calc_time);
    obstacle_ave_time = calculate_average_calc_time(obstacle_calc_times, calc_time_depth);
    obstacle_calc_time = ros::Time::now().toSec();
  }
  void frontier_cm_callback(const nav_msgs::OccupancyGrid & cm) {
    frontier_costmap = cm;
    frontier_cm_recieved = true;
    frontier_calc_times.push_back(ros::Time::now().toSec() - frontier_calc_time);
    frontier_ave_time = calculate_average_calc_time(frontier_calc_times, calc_time_depth);
    frontier_calc_time = ros::Time::now().toSec();
    //environment_mapped = is_environment_mapped(frontier_costmap);
  }
    
  void search_status_callback(const std_msgs::Float64& msg) {
      if (msg.data >= search_detail) {
          environment_searched = true;
          // ROS_INFO_STREAM("Mapped area is " << msg.data << " % searched");
      }
      else environment_searched = false;
  }
    
  void frontier_status_callback(const std_msgs::Float64& msg) {
      if (msg.data <= frontier_detail) {
          environment_mapped = true;
          // ROS_INFO_STREAM("Area has " << msg.data << " frontier points");
      }
      else environment_mapped = false;
  }
    
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "searcher");
    Search bucketfinder;
    ros::spin();
    return 0;
}
