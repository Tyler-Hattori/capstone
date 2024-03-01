#ifndef CHANNEL_H
#define CHANNEL_H

#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>

class NavMux;

class NavChannel {
private:
    // Publish drive data to simulator/car
    ros::Publisher nav_pub;

    // Listen to drive data from a specific topic
    ros::Subscriber channel_sub;

    // nav mux index for this channel
    int nav_mux_idx;

    // Pointer to nav mux object (to access nav mux controller and nodeHandle)
    NavMux* mp_nav_mux;


public:
    NavChannel();

    NavChannel(std::string channel_name, std::string drive_topic, int mux_idx_, NavMux* mux);

    void nav_callback(const geometry_msgs::PoseStamped & msg);
};


#endif // CHANNEL_H
