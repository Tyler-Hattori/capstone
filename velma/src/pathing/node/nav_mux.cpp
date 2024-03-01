#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Header.h>
#include <std_msgs/Int32MultiArray.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>

#include "pathing/nav_channel.h"

class NavMux {
private:
    ros::NodeHandle n;
    ros::Subscriber mux_sub;
    ros::Publisher nav_pub;
    
    ros::Publisher return_pub;

    // Mux controller array
    std::vector<bool> mux_controller;
    int mux_size;

    // Channel array
    std::vector<NavChannel*> channels;

    // Make Channel class have access to these private variables
    friend class NavChannel;

    // For printing
    std::vector<bool> prev_mux;
    
    int return_mux_index;

public:
    NavMux() {
        n = ros::NodeHandle("~");

        std::string nav_topic, mux_topic, return_goal_topic;
        n.getParam("nav_goal_topic", nav_topic);
        n.getParam("nav_mux_topic", mux_topic);
        n.getParam("return_nav_topic", return_goal_topic);

        nav_pub = n.advertise<geometry_msgs::PoseStamped>(nav_topic, 10);
        return_pub = n.advertise<geometry_msgs::PoseStamped>("/return_goal", 10);
        mux_sub = n.subscribe(mux_topic, 1, &NavMux::mux_callback, this);
      
        n.getParam("nav_mux_size", mux_size);

        // initialize mux controller
        mux_controller.reserve(mux_size);
        prev_mux.reserve(mux_size);
        for (int i = 0; i < mux_size; i++) {
            mux_controller[i] = false;
            prev_mux[i] = false;
        }

        // A channel contains a subscriber to the given nav topic and a publisher to the main nav topic
        channels = std::vector<NavChannel*>();
        
        // Roomba
        int random_walker_nav_mux_idx;
        std::string random_walker_nav_topic;
        n.getParam("random_walker_nav_topic", random_walker_nav_topic);
        n.getParam("wanderer_nav_mux_idx", random_walker_nav_mux_idx);
        add_channel(random_walker_nav_topic, nav_topic, random_walker_nav_mux_idx);
        
        // Navigator
        int navigator_mux_idx;
        std::string navigate_nav_topic;
        n.getParam("navigate_nav_topic", navigate_nav_topic);
        n.getParam("navigator_nav_mux_idx", navigator_mux_idx);
        add_channel(navigate_nav_topic, nav_topic, navigator_mux_idx);
        
        // Recaller
        int recaller_mux_idx;
        std::string recall_nav_topic;
        n.getParam("recall_nav_topic", recall_nav_topic);
        n.getParam("recaller_nav_mux_idx", recaller_mux_idx);
        add_channel(recall_nav_topic, nav_topic, recaller_mux_idx);
        
        // Returner
        int returner_mux_idx;
        std::string return_nav_topic = "/return_goal";
        n.getParam("returner_nav_mux_idx", returner_mux_idx);
        add_channel(return_nav_topic, nav_topic, returner_mux_idx);
        return_mux_index = returner_mux_idx;

        // Explorer
        int explorer_mux_idx;
        std::string explore_nav_topic;
        n.getParam("explore_nav_topic", explore_nav_topic);
        n.getParam("explorer_nav_mux_idx", explorer_mux_idx);
        add_channel(explore_nav_topic, nav_topic, explorer_mux_idx);

        // Searcher
        int searcher_mux_idx;
        std::string search_nav_topic;
        n.getParam("search_nav_topic", search_nav_topic);
        n.getParam("searcher_nav_mux_idx", searcher_mux_idx);
        add_channel(search_nav_topic, nav_topic, searcher_mux_idx);
    }

    void add_channel(std::string channel_name, std::string nav_topic, int mux_idx_) {
        NavChannel* new_channel = new NavChannel(channel_name, nav_topic, mux_idx_, this);
        channels.push_back(new_channel);    
    }

    void mux_callback(const std_msgs::Int32MultiArray & msg) {
        // reset mux member variable every time it's published
        for (int i = 0; i < mux_size; i++) {
            mux_controller[i] = bool(msg.data[i]);
        }

        // Prints the mux whenever it is changed
        bool changed = false;
        // checks if nothing is on
        bool anything_on = false;
        for (int i = 0; i < mux_size; i++) {
            changed = changed || (mux_controller[i] != prev_mux[i]);
            anything_on = anything_on || mux_controller[i];
        }
        if (changed) {
            if (mux_controller[return_mux_index]) {
                geometry_msgs::PoseStamped pose;
                pose.header.stamp = ros::Time::now();
                pose.header.frame_id = "map";
                pose.pose.position.x = 0.01;
                pose.pose.position.y = 0.01;
                pose.pose.orientation.w = 1.0;
                pose.pose.orientation.x = 0.0;
                pose.pose.orientation.y = 0.0;
                pose.pose.orientation.z = 0.0;
                return_pub.publish(pose);
            }
            std::cout << "NAV MUX: " << std::endl;
            for (int i = 0; i < mux_size; i++) {
                std::cout << mux_controller[i] << std::endl;
                prev_mux[i] = mux_controller[i];
            }
            std::cout << std::endl;
        }
        if (!anything_on) {
            /*geometry_msgs::PoseStamped pose;
            pose.header.stamp = ros::Time::now();
            pose.header.frame_id = "map";
            pose.pose.position.x = 0.0;
            pose.pose.position.y = 0.0;
            pose.pose.orientation.w = 1.0;
            pose.pose.orientation.x = 0.0;
            pose.pose.orientation.y = 0.0;
            pose.pose.orientation.z = 0.0;
            nav_pub.publish(pose);*/
        }
    }
};


/// Channel class method implementations

NavChannel::NavChannel() {
    ROS_INFO("NavChannel intialized without proper information");
    NavChannel("", "", -1, nullptr);
}

NavChannel::NavChannel(std::string channel_name, std::string nav_topic, int mux_idx_, NavMux* mux) 
: nav_mux_idx(mux_idx_), mp_nav_mux(mux) {
    nav_pub = mux->n.advertise<geometry_msgs::PoseStamped>(nav_topic, 10);
    channel_sub = mux->n.subscribe(channel_name, 1, &NavChannel::nav_callback, this);
}

void NavChannel::nav_callback(const geometry_msgs::PoseStamped & msg) {
    if (mp_nav_mux->mux_controller[this->nav_mux_idx]) {
        nav_pub.publish(msg);
    }
}

int main(int argc, char ** argv) {
    ros::init(argc, argv, "nav_mux_controller");
    NavMux nvmx;
    ros::spin();
    return 0;
}
