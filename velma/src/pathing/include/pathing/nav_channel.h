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

    // Mux index for this channel
    int mux_idx;

    // Pointer to nav mux object (to access mux controller and nodeHandle)
    NavMux* mp_mux;


public:
    NavChannel();

    NavChannel(std::string channel_name, std::string drive_topic, int mux_idx_, NavMux* mux);

    void nav_callback(const geometry_msgs::PoseWithCovarianceStamped & msg);
};


#endif // CHANNEL_H
