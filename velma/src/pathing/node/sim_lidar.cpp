#include <ros/ros.h>

// interactive marker
#include <interactive_markers/interactive_marker_server.h>

#include <ackermann_msgs/AckermannDriveStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/PointStamped.h>

#include <tf2/impl/utils.h>
#include <tf2/LinearMath/Quaternion.h>

#include "pathing/ackermann_kinematics.hpp"
#include "pathing/scan_simulator_2d.hpp"

#include "pathing/car_state.hpp"
#include "pathing/car_params.hpp"
#include "pathing/ks_kinematics.hpp"
#include "pathing/st_kinematics.hpp"
#include "pathing/precompute.hpp"

#include <iostream>
#include <math.h>


using namespace racecar_simulator;

class LidarSimulator {
	
private:
    ros::NodeHandle n;

    std::string map_frame, base_frame, scan_frame;

    // obstacle states (1D index) and parameters
    std::vector<int> added_obs;
    // listen for clicked point for adding obstacles
    ros::Subscriber obs_sub;
    int obstacle_size;

    // interactive markers' server
    interactive_markers::InteractiveMarkerServer im_server;

    CarState state;
	
    ScanSimulator2D scan_simulator;
    double map_free_threshold;
	
    ros::Timer update_lidar_timer;
	
    ros::Subscriber map_sub;
    ros::Subscriber odom_sub;
    bool map_exists = true;
	
    ros::Publisher scan_pub;
    ros::Publisher map_pub;

    // keep an original map for obstacles
    nav_msgs::OccupancyGrid original_map;
    nav_msgs::OccupancyGrid current_map;

    std::vector<double> cosines;

    // scan parameters
    double scan_fov;
    double scan_ang_incr;
    double scan_distance_to_base_link;

    const double PI = 3.1415;
	
    int map_width, map_height;
    double map_resolution, origin_x, origin_y;
	
    // precompute distance from lidar to edge of car for each beam
    std::vector<double> car_distances;

public:

    LidarSimulator(): im_server("racecar_sim") {
        n = ros::NodeHandle("~");
	    
        state = {.x=0, .y=0, .theta=0, .velocity=0, .steer_angle=0.0, .angular_velocity=0.0, .slip_angle=0.0, .st_dyn=false};
        
        std::string map_topic, scan_topic, odom_topic;
        n.getParam("map_topic", map_topic);
        n.getParam("scan_topic", scan_topic);
        n.getParam("odom_topic", odom_topic);

        n.getParam("odom_frame", map_frame);
        n.getParam("base_frame", base_frame);
        n.getParam("scan_frame", scan_frame);

        // Fetch the car parameters
        int scan_beams;
        double update_lidar_rate, scan_std_dev;
        n.getParam("update_lidar_rate", update_lidar_rate);
        n.getParam("scan_beams", scan_beams);
        n.getParam("scan_field_of_view", scan_fov);
        n.getParam("scan_std_dev", scan_std_dev);
        n.getParam("map_free_threshold", map_free_threshold);
        n.getParam("scan_distance_to_base_link", scan_distance_to_base_link);

        // Get obstacle size parameter
        n.getParam("obstacle_size", obstacle_size);

        // Initialize a simulator of the laser scanner
        scan_simulator = ScanSimulator2D(
            scan_beams,
            scan_fov,
            scan_std_dev);

        // Start a timer to output the lidar
        update_lidar_timer = n.createTimer(ros::Duration(update_lidar_rate), &LidarSimulator::update_lidar, this);

        scan_pub = n.advertise<sensor_msgs::LaserScan>(scan_topic, 1);
        map_sub = n.subscribe(map_topic, 1, &LidarSimulator::map_callback, this);
	odom_sub = n.subscribe(odom_topic, 1, &LidarSimulator::odom_callback, this);  
        obs_sub = n.subscribe("/clicked_point", 1, &LidarSimulator::obs_callback, this);

        scan_ang_incr = scan_simulator.get_angle_increment();

        cosines = Precompute::get_cosines(scan_beams, -scan_fov/2.0, scan_ang_incr);

        // OBSTACLE BUTTON:
        // wait for one map message to get the map data array
        boost::shared_ptr<nav_msgs::OccupancyGrid const> map_ptr;
        nav_msgs::OccupancyGrid map_msg;
        map_ptr = ros::topic::waitForMessage<nav_msgs::OccupancyGrid>("/map");
        if (map_ptr != NULL) {
            map_msg = *map_ptr;
        }
        original_map = map_msg;
        current_map = map_msg;
        std::vector<int8_t> map_data_raw = map_msg.data;
        std::vector<int> map_data(map_data_raw.begin(), map_data_raw.end());

        map_width = map_msg.info.width;
        map_height = map_msg.info.height;
        origin_x = map_msg.info.origin.position.x;
        origin_y = map_msg.info.origin.position.y;
        map_resolution = map_msg.info.resolution;

        // create button for clearing obstacles
        visualization_msgs::InteractiveMarker clear_obs_button;
        clear_obs_button.header.frame_id = "map";
        // clear_obs_button.pose.position.x = origin_x+(1/3)*map_width*map_resolution;
        // clear_obs_button.pose.position.y = origin_y+(1/3)*map_height*map_resolution;
        // TODO: find better positioning of buttons
        clear_obs_button.pose.position.x = 0;
        clear_obs_button.pose.position.y = -5;
        clear_obs_button.scale = 1;
        clear_obs_button.name = "clear_obstacles";
        clear_obs_button.description = "Clear Obstacles\n(Left Click)";
        visualization_msgs::InteractiveMarkerControl clear_obs_control;
        clear_obs_control.interaction_mode = visualization_msgs::InteractiveMarkerControl::BUTTON;
        clear_obs_control.name = "clear_obstacles_control";
        // make a box for the button
        visualization_msgs::Marker clear_obs_marker;
        clear_obs_marker.type = visualization_msgs::Marker::CUBE;
        clear_obs_marker.scale.x = clear_obs_button.scale*0.45;
        clear_obs_marker.scale.y = clear_obs_button.scale*0.65;
        clear_obs_marker.scale.z = clear_obs_button.scale*0.45;
        clear_obs_marker.color.r = 0.0;
        clear_obs_marker.color.g = 1.0;
        clear_obs_marker.color.b = 0.0;
        clear_obs_marker.color.a = 1.0;

        clear_obs_control.markers.push_back(clear_obs_marker);
        clear_obs_control.always_visible = true;
        clear_obs_button.controls.push_back(clear_obs_control);

        im_server.insert(clear_obs_button);
        im_server.setCallback(clear_obs_button.name, boost::bind(&LidarSimulator::clear_obstacles, this, _1));

        im_server.applyChanges();

        ROS_INFO("Lidar simulator constructed");
    }

    void update_lidar(const ros::TimerEvent&) {
	ros::Time timestamp = ros::Time::now();
	
	// If we have a map, perform a scan
        if (map_exists) {
            Pose2D scan_pose;
            scan_pose.x = state.x + scan_distance_to_base_link * std::cos(state.theta);
            scan_pose.y = state.y + scan_distance_to_base_link * std::sin(state.theta);
            scan_pose.theta = state.theta;

            // Compute the scan from the lidar
            std::vector<double> scan = scan_simulator.scan(scan_pose);

            // Convert to float
            std::vector<float> scan_(scan.size());
            for (size_t i = 0; i < scan.size(); i++)
                scan_[i] = scan[i];

            // Publish the laser message
            sensor_msgs::LaserScan scan_msg;
            scan_msg.header.stamp = timestamp;
            scan_msg.header.frame_id = scan_frame;
            scan_msg.angle_min = -scan_simulator.get_field_of_view()/2.;
            scan_msg.angle_max =  scan_simulator.get_field_of_view()/2.;
            scan_msg.angle_increment = scan_simulator.get_angle_increment();
            scan_msg.range_max = 100;
            scan_msg.ranges = scan_;
            scan_msg.intensities = scan_;

            scan_pub.publish(scan_msg);
        }
    }

        /// ---------------------- GENERAL HELPER FUNCTIONS ----------------------

    std::vector<int> ind_2_rc(int ind) {
        std::vector<int> rc;
        int row = floor(ind/map_width);
        int col = ind%map_width - 1;
        rc.push_back(row);
        rc.push_back(col);
        return rc;
    }

    int rc_2_ind(int r, int c) {
        return r*map_width + c;
    }

    std::vector<int> coord_2_cell_rc(double x, double y) {
        std::vector<int> rc;
        rc.push_back(static_cast<int>((y-origin_y)/map_resolution));
        rc.push_back(static_cast<int>((x-origin_x)/map_resolution));
        return rc;
    }

    void add_obs(int ind) {
        std::vector<int> rc = ind_2_rc(ind);
        for (int i=-obstacle_size; i<obstacle_size; i++) {
            for (int j=-obstacle_size; j<obstacle_size; j++) {
                int current_r = rc[0]+i;
                int current_c = rc[1]+j;
                int current_ind = rc_2_ind(current_r, current_c);
                current_map.data[current_ind] = 100;
            }
        }
        map_pub.publish(current_map);
    }

    void clear_obs(int ind) {
        std::vector<int> rc = ind_2_rc(ind);
        for (int i=-obstacle_size; i<obstacle_size; i++) {
            for (int j=-obstacle_size; j<obstacle_size; j++) {
                int current_r = rc[0]+i;
                int current_c = rc[1]+j;
                int current_ind = rc_2_ind(current_r, current_c);
                current_map.data[current_ind] = 0;

            }
        }
        map_pub.publish(current_map);
    }
	
        /// ---------------------- CALLBACK FUNCTIONS ----------------------

    void obs_callback(const geometry_msgs::PointStamped &msg) {
        double x = msg.point.x;
        double y = msg.point.y;
        std::vector<int> rc = coord_2_cell_rc(x, y);
        int ind = rc_2_ind(rc[0], rc[1]);
        added_obs.push_back(ind);
        add_obs(ind);
    }
    
    void clear_obstacles(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback) {
        bool clear_obs_clicked = false;
        if (feedback->event_type == 3) {
            clear_obs_clicked = true;
        }
        if (clear_obs_clicked) {
            ROS_INFO("Clearing obstacles.");
            current_map = original_map;
            map_pub.publish(current_map);

            clear_obs_clicked = false;
        }
    }
	
    void odom_callback(const nav_msgs::Odometry & msg) {
        state.velocity = msg.twist.twist.linear.x;
        state.angular_velocity = msg.twist.twist.angular.z;
        state.x = msg.pose.pose.position.x;
        state.y = msg.pose.pose.position.y;
    }
	
    void map_callback(const nav_msgs::OccupancyGrid & msg) {
    	size_t height = msg.info.height;
    	size_t width = msg.info.width;
    	double resolution = msg.info.resolution;
    	
	// Convert the map origin to a pose
    	Pose2D origin;
    	origin.x = msg.info.origin.position.x;
    	origin.y = msg.info.origin.position.y;
    	geometry_msgs::Quaternion q = msg.info.origin.orientation;
    	tf2::Quaternion quat(q.x, q.y, q.z, q.w);
    	origin.theta = tf2::impl::getYaw(quat);

    	// Convert the map to probability values
    	std::vector<double> map(msg.data.size());
    	for (size_t i = 0; i < height * width; i++) {
	    if (msg.data[i] > 100 or msg.data[i] < 0) {
		map[i] = 0.5; // Unknown
	    }
 	    else {
		map[i] = msg.data[i]/100.;
	    }
 	}
    
 	scan_simulator.set_map(
	    map,
	    height,
	    width,
	    resolution,
	    origin,
	    map_free_threshold);
 	   
 	map_exists = true;
    }
};


int main(int argc, char ** argv) {
    ros::init(argc, argv, "lidar_simulator");
    LidarSimulator ls;
    ros::spin();
    return 0;
}
