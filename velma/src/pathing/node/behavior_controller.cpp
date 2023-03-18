#include <ros/ros.h>
#include <ros/package.h>

#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/String.h>

#include <fstream>

#include "pathing/car_state.hpp"
#include "pathing/precompute.hpp"

using namespace racecar_simulator;

class BehaviorController {
private:
    ros::NodeHandle n;

    ros::Subscriber joy_sub;
    ros::Subscriber key_sub;
    ros::Subscriber web_sub;
    ros::Subscriber laser_sub;
    ros::Subscriber odom_sub;

    ros::Publisher mux_pub;
    ros::Publisher nav_mux_pub;
    ros::Publisher log_pub;

    // Mux indices
    int joy_mux_idx;
    int key_mux_idx;
    int web_mux_idx;
    int random_walker_mux_idx;
    int guarder_mux_idx;
    int wall_follower_mux_idx;
    int gap_follower_mux_idx;
    int navigator_mux_idx;
    int explorer_mux_idx;
    int searcher_mux_idx;
    
    // Nav mux indices
    int navigator_nav_mux_idx;
    int returner_nav_mux_idx;
    int recaller_nav_mux_idx;
    int explorer_nav_mux_idx;
    int searcher_nav_mux_idx;
    
    // Mux controller arrays
    std::vector<bool> mux_controller;
    int mux_size;
    std::vector<bool> nav_mux_controller;
    int nav_mux_size;

    // Joystick button indices
    int joy_button_idx;
    int key_button_idx;
    int web_button_idx;
    int brake_button_idx;
    int random_walk_button_idx;
    int guard_button_idx;
    int wall_follow_button_idx;
    int gap_follow_button_idx;
    int log_button_idx;
    int recall_button_idx;
    int return_button_idx;
    int navigate_button_idx;
    int explore_button_idx;
    int search_button_idx;

    // Key indices
    std::string joy_key_char;
    std::string keyboard_key_char;
    std::string web_key_char;
    std::string brake_key_char;
    std::string random_walk_key_char;
    std::string guard_key_char;
    std::string wall_follow_key_char;
    std::string gap_follow_key_char;
    std::string log_key_char;
    std::string recall_key_char;
    std::string return_key_char;
    std::string navigate_key_char;
    std::string explore_key_char;
    std::string search_key_char;
    
    // Web indices
    std::string joy_web_char;
    std::string keyboard_web_char;
    std::string web_web_char;
    std::string brake_web_char;
    std::string random_walk_web_char;
    std::string guard_web_char;
    std::string wall_follow_web_char;
    std::string gap_follow_web_char;
    std::string log_web_char;
    std::string recall_web_char;
    std::string return_web_char;
    std::string navigate_web_char;
    std::string explore_web_char;
    std::string search_web_char;

    // Bool for toggling smart sense
    bool safety_on;
    
    // Bool for waypoint logger mode
    bool log;

    // To roughly keep track of vehicle state
    racecar_simulator::CarState state;

    // precompute distance from lidar to edge of car for each beam
    std::vector<double> car_distances;

    // precompute cosines of scan angles
    std::vector<double> cosines;

    // for collision detection
    double ttc_threshold;
    bool in_collision;
    bool in_danger;

    // for collision logging
    std::ofstream collision_file;
    double beginning_seconds;
    int collision_count=0;

    std::string active_controller;

public:
    BehaviorController() {
        // Initialize the node handle
        n = ros::NodeHandle("~");

        // get topic names
        std::string scan_topic, odom_topic, joy_topic, keyboard_topic, web_topic, mux_topic, nav_mux_topic; 
        n.getParam("scan_topic", scan_topic);
        n.getParam("odom_topic", odom_topic);
        n.getParam("joy_topic", joy_topic);
        n.getParam("mux_topic", mux_topic);
        n.getParam("nav_mux_topic", nav_mux_topic);
        n.getParam("keyboard_topic", keyboard_topic);
        n.getParam("web_topic", web_topic);

        // Make a publisher for mux messages
        mux_pub = n.advertise<std_msgs::Int32MultiArray>(mux_topic, 10);
        nav_mux_pub = n.advertise<std_msgs::Int32MultiArray>(nav_mux_topic, 10);
        
        log_pub = n.advertise<std_msgs::Bool>("/log_bool", 10);

        // Start subscribers to listen to laser scan, joy, IMU, and odom messages
        laser_sub = n.subscribe(scan_topic, 1, &BehaviorController::laser_callback, this);
        joy_sub = n.subscribe(joy_topic, 1, &BehaviorController::joy_callback, this);
        odom_sub = n.subscribe(odom_topic, 1, &BehaviorController::odom_callback, this);
        key_sub = n.subscribe(keyboard_topic, 1, &BehaviorController::key_callback, this);
        web_sub = n.subscribe(web_topic, 1, &BehaviorController::web_callback, this);

        // Get mux indices
        n.getParam("joy_mux_idx", joy_mux_idx);
        n.getParam("key_mux_idx", key_mux_idx);
        n.getParam("web_mux_idx", web_mux_idx);
        n.getParam("random_walker_mux_idx", random_walker_mux_idx);
        n.getParam("guarder_mux_idx", guarder_mux_idx);
        n.getParam("wall_follower_mux_idx", wall_follower_mux_idx);
        n.getParam("gap_follower_mux_idx", gap_follower_mux_idx);
        n.getParam("navigator_mux_idx", navigator_mux_idx);
        
        // Get nav mux indices
        n.getParam("navigator_nav_mux_idx", navigator_nav_mux_idx);
        n.getParam("returner_nav_mux_idx", returner_nav_mux_idx);
        n.getParam("recaller_nav_mux_idx", recaller_nav_mux_idx);
        n.getParam("explorer_nav_mux_idx", explorer_nav_mux_idx);
        n.getParam("searcher_nav_mux_idx", searcher_nav_mux_idx);

        // Get button indices
        n.getParam("joy_button_idx", joy_button_idx);
        n.getParam("key_button_idx", key_button_idx);
        n.getParam("web_button_idx", web_button_idx);
        n.getParam("brake_button_idx", brake_button_idx);
        n.getParam("random_walk_button_idx", random_walk_button_idx);
        n.getParam("guard_button_idx", guard_button_idx);
        n.getParam("wall_follow_button_idx", wall_follow_button_idx);
        n.getParam("gap_follow_button_idx", gap_follow_button_idx);
        n.getParam("log_button_idx", log_button_idx);
        n.getParam("recall_button_idx", recall_button_idx);
        n.getParam("return_button_idx", return_button_idx);
        n.getParam("navigate_button_idx", navigate_button_idx);
        n.getParam("explore_button_idx", explore_button_idx);
        n.getParam("search_button_idx", search_button_idx);

        // Get key indices
        n.getParam("joy_key_char", joy_key_char);
        n.getParam("keyboard_key_char", keyboard_key_char);
        n.getParam("web_key_char", web_key_char);
        n.getParam("brake_key_char", brake_key_char);
        n.getParam("random_walk_key_char", random_walk_key_char);
        n.getParam("guard_key_char", guard_key_char);
        n.getParam("wall_follow_key_char", wall_follow_key_char);
        n.getParam("gap_follow_key_char", gap_follow_key_char);
        n.getParam("log_key_char", log_key_char);
        n.getParam("recall_key_char", recall_key_char);
        n.getParam("return_key_char", return_key_char);
        n.getParam("navigate_key_char", navigate_key_char);
        n.getParam("explore_key_char", explore_key_char);
        n.getParam("search_key_char", search_key_char);
        
        // Get web indices
        n.getParam("joy_web_char", joy_web_char);
        n.getParam("keyboard_web_char", keyboard_web_char);
        n.getParam("web_web_char", web_web_char);
        n.getParam("brake_web_char", brake_web_char);
        n.getParam("random_walk_web_char", random_walk_web_char);
        n.getParam("guard_web_char", guard_web_char);
        n.getParam("wall_follow_web_char", wall_follow_web_char);
        n.getParam("gap_follow_web_char", gap_follow_web_char);
        n.getParam("log_web_char", log_web_char);
        n.getParam("recall_web_char", recall_web_char);
        n.getParam("return_web_char", return_web_char);
        n.getParam("navigate_web_char", navigate_web_char);
        n.getParam("explore_web_char", explore_web_char);
        n.getParam("search_web_char", search_web_char);

        // Initialize the mux controllers
        
        n.getParam("mux_size", mux_size);
        mux_controller.reserve(mux_size);
        for (int i = 0; i < mux_size; i++) {
            mux_controller[i] = false;
        }
        
        n.getParam("nav_mux_size", nav_mux_size);
        nav_mux_controller.reserve(nav_mux_size);
        for (int i = 0; i < nav_mux_size; i++) {
            nav_mux_controller[i] = false;
        }

        // Setting to false will stop the car from trying to sense obstacles and stopping before a collision occurs
        safety_on = true;
        
        // Toggles based on user input; activates waypoint logging mode
        log = false;
        
        in_collision = false;
        in_danger = false;

        // Initialize state
        state = {.x=0.0, .y=0.0, .theta=0.0, .velocity=0.0, .steer_angle=0.0, .angular_velocity=0.0, .slip_angle=0.0, .st_dyn=false};

        // Get params for precomputation and collision detection
        int scan_beams;
        double scan_fov, scan_ang_incr, wheelbase, width, scan_distance_to_base_link;
        n.getParam("ttc_threshold", ttc_threshold);
        n.getParam("scan_beams", scan_beams);
        n.getParam("scan_distance_to_base_link", scan_distance_to_base_link);
        n.getParam("width", width);
        n.getParam("wheelbase", wheelbase);
        n.getParam("scan_field_of_view", scan_fov);
        scan_ang_incr = scan_fov / scan_beams;

        // Precompute cosine and distance to car at each angle of the laser scan
        cosines = Precompute::get_cosines(scan_beams, -scan_fov/2.0, scan_ang_incr);
        car_distances = Precompute::get_car_distances(scan_beams, wheelbase, width, 
                scan_distance_to_base_link, -scan_fov/2.0, scan_ang_incr);

        // Create collision file to be written to
        std::string filename;
        n.getParam("collision_file", filename);
        collision_file.open(ros::package::getPath("simulator") + "/logs/" + filename + ".txt");
        beginning_seconds = ros::Time::now().toSec();

        active_controller = "key";
    }

    /// ---------------------- GENERAL HELPER FUNCTIONS ----------------------

    void publish_mux() {
        // make mux message
        std_msgs::Int32MultiArray mux_msg;
        mux_msg.data.clear();
        // push data onto message
        for (int i = 0; i < mux_size; i++) {
            mux_msg.data.push_back(int(mux_controller[i]));
        }

        // publish mux message
        mux_pub.publish(mux_msg);
    }
    
    void publish_nav_mux() {
        // make nav mux message
        std_msgs::Int32MultiArray nav_mux_msg;
        nav_mux_msg.data.clear();
        // push data onto message
        for (int i = 0; i < nav_mux_size; i++) {
            nav_mux_msg.data.push_back(int(nav_mux_controller[i]));
        }

        // publish nav mux message
        nav_mux_pub.publish(nav_mux_msg);
    }

    void change_controller(int controller_idx) {
        // This changes the controller to the input index and publishes it

        // turn everything off
        for (int i = 0; i < mux_size; i++) {
            mux_controller[i] = false;
        }
        // turn on desired controller
        mux_controller[controller_idx] = true;

        publish_mux();
    }
    
    void change_nav_controller(int controller_idx) {
        // This changes the controller to the input index and publishes it

        // turn everything off
        for (int i = 0; i < nav_mux_size; i++) {
            nav_mux_controller[i] = false;
        }
        // turn on desired controller
        nav_mux_controller[controller_idx] = true;

        publish_nav_mux();
    }

    void collision_checker(const sensor_msgs::LaserScan & msg) {
        // This function calculates TTC to see if there's a collision
        if (state.velocity != 0) {
            for (size_t i = 0; i < msg.ranges.size(); i++) {
                double angle = msg.angle_min + i * msg.angle_increment;

                // calculate projected velocity
                double proj_velocity = state.velocity * cosines[i];
                double ttc = (msg.ranges[i] - car_distances[i]) / proj_velocity;

                // if it's small, there's a collision
                if ((ttc < ttc_threshold) && (ttc >= 0.0)) { 
                    // Send a blank mux and write to file
                    brake();

                    in_collision = true;

                    collision_count++;
                    collision_file << "Collision #" << collision_count << " detected:\n";
                    collision_file << "TTC: " << ttc << " seconds\n";
                    collision_file << "Angle to obstacle: " << angle << " radians\n";
                    collision_file << "Time since start of sim: " << (ros::Time::now().toSec() - beginning_seconds) << " seconds\n";
                    collision_file << "\n";
                    return;
                }
            }
            // if it's gone through all beams without detecting a collision, reset in_collision
            in_collision = false;
        }
    }
    
    /*void sense_collision(const sensor_msgs::LaserScan & msg) {
        // TODO: write code to set in_danger to true if the car is about to crash
        
        if (in_danger) {
            ROS_INFO("You're about to crash!");
            brake();
        }
    }
    
    */

    void toggle_mux(int mux_idx, std::string driver_name) {
        // This takes in an index and the name of the planner/driver and 
        // toggles the mux appropiately
        if (mux_controller[mux_idx]) {
            ROS_INFO_STREAM(driver_name << " turned off");
            mux_controller[mux_idx] = false;
            publish_mux();
        }
        else {
            ROS_INFO_STREAM(driver_name << " turned on");
            change_controller(mux_idx);
        }
    }
    
    void toggle_nav_mux(int nav_mux_idx, std::string driver_name) {
        // This takes in an index and the name of the planner/driver and 
        // toggles the nav mux appropiately
        // It also turns on the mux idx for navigation
        if (nav_mux_controller[nav_mux_idx]) {
            ROS_INFO_STREAM(driver_name << " turned off");
            nav_mux_controller[nav_mux_idx] = false;
            mux_controller[navigator_mux_idx] = false;
            publish_nav_mux();
            publish_mux();
        }
        else {
            ROS_INFO_STREAM(driver_name << " turned on");
            change_nav_controller(nav_mux_idx);
            change_controller(navigator_mux_idx);
        }
        
        if (driver_name == "Recaller") log_pub.publish("publish");
    }
    
    void toggle_logger_mode() {
        std_msgs::String log_msg;
        if (log) {
            ROS_INFO("Logging mode deactivated. To retrace path, hit 'r'");
            command = "store";
        }
        else {
            ROS_INFO("Logging mode activated. Beginning to log the car's path");
            log = true;
            command = "start";
        }
        log_msg.data = command;
        log_pub.publish(log_msg);
    }

    void brake() {
        ROS_INFO_STREAM("Emergency brake engaged");
        
        // turn everything off
        for (int i = 0; i < mux_size; i++) {
            mux_controller[i] = false;
        }
        for (int i = 0; i < nav_mux_size; i++) {
            nav_mux_controller[i] = false;
        }

        publish_mux();
        publish_nav_mux();
    }


    /// ---------------------- CALLBACK FUNCTIONS ----------------------

    void joy_callback(const sensor_msgs::Joy & msg) {
        if (msg.buttons[joy_button_idx]) { 
            toggle_mux(joy_mux_idx, "Joystick");
            active_controller = "joy";
        }
        else if (msg.buttons[web_button_idx]) { 
            toggle_mux(web_mux_idx, "Web Interface");
            active_controller = "web";
        }
        else if (msg.buttons[key_button_idx]) { 
            toggle_mux(key_mux_idx, "Keyboard");
            active_controller = "key";
        }
        
        if (active_controller == "joy"){
            if (msg.buttons[brake_button_idx]) brake();
            else if (msg.buttons[random_walk_button_idx]) toggle_mux(random_walker_mux_idx, "Random Walker");
            else if (msg.buttons[guard_button_idx]) toggle_mux(guarder_mux_idx, "Puppy Guarder");
            else if (msg.buttons[wall_follow_button_idx]) toggle_mux(wall_follower_mux_idx, "Patroller");
            else if (msg.buttons[gap_follow_button_idx]) toggle_mux(gap_follower_mux_idx, "Advancer");
            else if (msg.buttons[log_button_idx]) toggle_logger_mode();
            else if (msg.buttons[navigate_button_idx]) toggle_nav_mux(navigator_nav_mux_idx, "Custom Navigation");
            else if (msg.buttons[return_button_idx]) toggle_nav_mux(returner_nav_mux_idx, "Returner");
            else if (msg.buttons[recall_button_idx]) toggle_nav_mux(recaller_nav_mux_idx, "Recaller");
            else if (msg.buttons[explore_button_idx]) toggle_nav_mux(explorer_nav_mux_idx, "Explorer");
            else if (msg.buttons[search_button_idx]) toggle_nav_mux(searcher_nav_mux_idx, "Searcher");
        }
    }
    
    void web_callback(const std_msgs::String & msg) {
        if (msg.data == joy_web_char) {
            toggle_mux(joy_mux_idx, "Joystick");
            active_controller = "joy";
        }
        else if (msg.data == web_web_char) {
            toggle_mux(web_mux_idx, "Web Interface");
            active_controller = "web";
        }
        else if (msg.data == keyboard_web_char) {
            toggle_mux(key_mux_idx, "Keyboard");
            active_controller = "key";
        }
        
        if (active_controller == "web") {
            if (msg.data == brake_web_char) brake();
            else if (msg.data == random_walk_web_char) toggle_mux(random_walker_mux_idx, "Random Walker");
            else if (msg.data == guard_web_char) toggle_mux(guarder_mux_idx, "Guarder");
            else if (msg.data == wall_follow_web_char) toggle_mux(wall_follower_mux_idx, "Wall Follower");
            else if (msg.data == gap_follow_web_char) toggle_mux(gap_follower_mux_idx, "Gap Follower");
            else if (msg.data == log_web_char) toggle_logger_mode();
            else if (msg.data == navigate_web_char) toggle_nav_mux(navigator_nav_mux_idx, "Custom Navigation");
            else if (msg.data == return_web_char) toggle_nav_mux(returner_nav_mux_idx, "Returner");
            else if (msg.data == recall_web_char) toggle_nav_mux(recaller_nav_mux_idx, "Recaller");
            else if (msg.data == explore_web_char) toggle_nav_mux(explorer_nav_mux_idx, "Explorer");
            else if (msg.data == search_web_char) toggle_nav_mux(searcher_nav_mux_idx, "Searcher");
        }
    }

    void key_callback(const std_msgs::String & msg) {
        if (msg.data == joy_key_char) {
            toggle_mux(joy_mux_idx, "Joystick");
            active_controller = "joy";
        }
        else if (msg.data == web_key_char) {
            toggle_mux(web_mux_idx, "Web Interface");
            active_controller = "web";
        }
        else if (msg.data == keyboard_key_char) {
            toggle_mux(key_mux_idx, "Keyboard");
            active_controller = "key";
        }
        
        if (active_controller == "key") {
            if (msg.data == brake_key_char) brake();
            else if (msg.data == random_walk_key_char) toggle_mux(random_walker_mux_idx, "Random Walker");
            else if (msg.data == guard_key_char) toggle_mux(guarder_mux_idx, "Guarder");
            else if (msg.data == wall_follow_key_char) toggle_mux(wall_follower_mux_idx, "Wall Follower");
            else if (msg.data == gap_follow_key_char) toggle_mux(gap_follower_mux_idx, "Gap Follower");
            else if (msg.data == log_key_char) toggle_logger_mode();
            else if (msg.data == navigate_key_char) toggle_nav_mux(navigator_nav_mux_idx, "Custom Navigation");
            else if (msg.data == return_key_char) toggle_nav_mux(returner_nav_mux_idx, "Returner");
            else if (msg.data == recall_key_char) toggle_nav_mux(recaller_nav_mux_idx, "Recaller");
            else if (msg.data == explore_key_char) toggle_nav_mux(explorer_nav_mux_idx, "Explorer");
            else if (msg.data == search_key_char) toggle_nav_mux(searcher_nav_mux_idx, "Searcher");
        }
    }

    void laser_callback(const sensor_msgs::LaserScan & msg) {
        // check for a collision, or if a collision is about to happen
        /*
        if (safety_on)
            sense_collision(msg);
        */
        collision_checker(msg);
    }

    void odom_callback(const nav_msgs::Odometry & msg) {
        // Keep track of state to be used elsewhere
        state.velocity = msg.twist.twist.linear.x;
        state.angular_velocity = msg.twist.twist.angular.z;
        state.x = msg.pose.pose.position.x;
        state.y = msg.pose.pose.position.y;
    }
};

int main(int argc, char ** argv) {
    ros::init(argc, argv, "behavior_controller");
    BehaviorController bc;
    ros::spin();
    return 0;
}
