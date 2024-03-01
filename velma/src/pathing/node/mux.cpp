#include <ros/ros.h>

#include <ackermann_msgs/AckermannDriveStamped.h>
#include <ackermann_msgs/AckermannDrive.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Header.h>
#include <std_msgs/Int32MultiArray.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>

#include "pathing/channel.h"

class Mux {
private:
    ros::NodeHandle n;

    ros::Subscriber mux_sub;
   
    //  Sensors
    ros::Subscriber key_sub;
    ros::Subscriber web_sub;

    // Publish drive data to simulator/car
    ros::Publisher drive_pub;

    // Mux indices
    int key_mux_idx;
    int web_mux_idx;

    // Mux controller array
    std::vector<bool> mux_controller;
    int mux_size;

    // Channel array
    std::vector<Channel*> channels;

    // Make Channel class have access to these private variables
    friend class Channel;

    // For printing
    std::vector<bool> prev_mux;

    // For keyboard driving
    double max_speed, max_steering_angle;
    double prev_key_velocity=0.0;
    double prev_key_steer = 0.0;


public:
    Mux() {
        // Initialize the node handle
        n = ros::NodeHandle("~");

        // get topic names
        std::string drive_topic, mux_topic, key_topic, web_topic;
        n.getParam("drive_topic", drive_topic);
        n.getParam("mux_topic", mux_topic);
        n.getParam("keyboard_topic", key_topic);
        n.getParam("web_topic", web_topic);

        // Make a publisher for drive messages
        drive_pub = n.advertise<ackermann_msgs::AckermannDriveStamped>("/drive", 10);

        // Start a subscriber to listen to mux messages
        mux_sub = n.subscribe(mux_topic, 1, &Mux::mux_callback, this);

        // Start subscribers to listen to joy and keyboard messages
        key_sub = n.subscribe(key_topic, 1, &Mux::key_callback, this);
        web_sub = n.subscribe(web_topic, 1, &Mux::web_callback, this);

        // get mux indices
        n.getParam("key_mux_idx", key_mux_idx);
        n.getParam("web_mux_idx", web_mux_idx);

        // get params for manual control
        n.getParam("max_steering_angle", max_steering_angle);
        n.getParam("max_speed", max_speed);

        // get size of mux
        n.getParam("mux_size", mux_size);

        // initialize mux controller
        mux_controller.reserve(mux_size);
        prev_mux.reserve(mux_size);
        for (int i = 0; i < mux_size; i++) {
            mux_controller[i] = false;
            prev_mux[i] = false;
        }

        // A channel contains a subscriber to the given drive topic and a publisher to the main drive topic
        channels = std::vector<Channel*>();

        /// Add new channels here:
        // Wall Follower
        int wall_follower_mux_idx;
        std::string wall_follow_drive_topic;
        n.getParam("wall_follow_drive_topic", wall_follow_drive_topic);
        n.getParam("wall_follower_mux_idx", wall_follower_mux_idx);
        add_channel(wall_follow_drive_topic, drive_topic, wall_follower_mux_idx);

        // Gap Follower
        int gap_follower_mux_idx;
        std::string gap_follow_drive_topic;
        n.getParam("gap_follow_drive_topic", gap_follow_drive_topic);
        n.getParam("gap_follower_mux_idx", gap_follower_mux_idx);
        add_channel(gap_follow_drive_topic, drive_topic, gap_follower_mux_idx);

        // General navigation channel
        int navigator_mux_idx;
        std::string navigate_drive_topic;
        n.getParam("navigate_drive_topic", navigate_drive_topic);
        n.getParam("navigator_mux_idx", navigator_mux_idx);
        add_channel(navigate_drive_topic, drive_topic, navigator_mux_idx);
    }

    void add_channel(std::string channel_name, std::string drive_topic, int mux_idx_) {
        Channel* new_channel = new Channel(channel_name, drive_topic, mux_idx_, this);
        channels.push_back(new_channel);    
    }

    void publish_to_drive(double desired_velocity, double desired_steer) {
        // This will take in a desired velocity and steering angle and make and publish an 
        // AckermannDriveStamped message to the /drive topic

        // Make and publish message
        ackermann_msgs::AckermannDriveStamped drive_st_msg;
        ackermann_msgs::AckermannDrive drive_msg;
        std_msgs::Header header;
        drive_msg.speed = desired_velocity;
        drive_msg.steering_angle = desired_steer;
        header.stamp = ros::Time::now();

        drive_st_msg.header = header;

        // set drive message in drive stamped message
        drive_st_msg.drive = drive_msg;

        // publish AckermannDriveStamped message to drive topic
        drive_pub.publish(drive_st_msg);
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
            std::cout << "MUX: " << std::endl;
            for (int i = 0; i < mux_size; i++) {
                std::cout << mux_controller[i] << std::endl;
                prev_mux[i] = mux_controller[i];
            }
            std::cout << std::endl;
        }
        if (!anything_on) {
            // if no mux channel is active, halt the car
            publish_to_drive(0.0, 0.0);
        }
    }

    void key_callback(const std_msgs::String & msg) {
        // make drive message from keyboard if turned on 
        if (mux_controller[key_mux_idx]) {
            // Determine desired velocity and steering angle
            double desired_velocity = 0.0;
            double desired_steer = 0.0;
            
            bool publish = true;

            if (msg.data == "w") {
                // Forward
                if (prev_key_velocity + 0.15 <= max_speed) desired_velocity = prev_key_velocity + 0.15;
                if (prev_key_velocity <= 0) desired_velocity = 0.6;
                desired_steer = prev_key_steer;
            } else if (msg.data == "s") {
                // Backwards
                if (prev_key_velocity - 0.15 >= -max_speed) desired_velocity = prev_key_velocity - 0.15;
                if (prev_key_velocity >= 0) desired_velocity = -0.6;
                desired_steer = prev_key_steer;
            } else if (msg.data == "a") {
                // Steer left and keep speed
                if (prev_key_steer + 0.1 <= max_steering_angle) desired_steer = prev_key_steer + 0.1;
                else desired_steer = max_steering_angle;
                desired_velocity = prev_key_velocity;
            } else if (msg.data == "d") {
                // Steer right and keep speed
                if (prev_key_steer - 0.1 >= -max_steering_angle) desired_steer = prev_key_steer - 0.1;
                else desired_steer = -max_steering_angle;
                desired_velocity = prev_key_velocity;
            } else if (msg.data == "u") {
                //steer left at 0.36 rad
                desired_steer = 0.36;
                desired_velocity = prev_key_velocity;
            } else if (msg.data == "i") {
                //steer right at 0.36
                desired_steer = -0.36;
                desired_velocity = prev_key_velocity;
            } else if ((msg.data == "q")) {
                //stop the car
                desired_steer = 0;
                desired_velocity = 0.75;
            } else if (msg.data == "b") {
                // publish zeros to slow down/straighten out car
            } else {
                // so that it doesn't constantly publish zeros when you press other keys
                publish = false;
                desired_steer=prev_key_steer;
                desired_velocity=prev_key_velocity;
            }

            if (publish) {
                //ROS_INFO_STREAM("velocity command: " << desired_velocity << " m/s");
                //ROS_INFO_STREAM("steering command: " << desired_steer << " rad");
                publish_to_drive(desired_velocity, desired_steer);
                prev_key_velocity = desired_velocity;
                prev_key_steer = desired_steer;
            }
        }
    }
    
    void web_callback(const std_msgs::String & msg) {
        // make drive message from web if turned on 
        if (mux_controller[web_mux_idx]) {
            // Determine desired velocity and steering angle
            double desired_velocity = 0.0;
            double desired_steer = 0.0;
            
            bool publish = true;

            if (msg.data == "forward") {
                if (prev_key_velocity + 0.15 <= max_speed) desired_velocity = prev_key_velocity + 0.15;
                if (prev_key_velocity <= 0) desired_velocity = 0.6;
                desired_steer = prev_key_steer;
            } else if (msg.data == "backward") {
                if (prev_key_velocity - 0.15 >= -max_speed) desired_velocity = prev_key_velocity - 0.15;
                if (prev_key_velocity >= 0) desired_velocity = -0.6;
                desired_steer = prev_key_steer;
            } else if (msg.data == "left") {
                // Steer left and keep speed
                if (prev_key_steer + 0.1 <= max_steering_angle) desired_steer = prev_key_steer + 0.1;
                else desired_steer = prev_key_steer;
                desired_velocity = prev_key_velocity;
            } else if (msg.data == "right") {
                // Steer right and keep speed
                if (prev_key_steer - 0.1 >= -max_steering_angle) desired_steer = prev_key_steer - 0.1;
                else desired_steer = prev_key_steer;
                desired_velocity = prev_key_velocity;
            } else if (msg.data == " ") {
                // publish zeros to slow down/straighten out car
            } else {
                // so that it doesn't constantly publish zeros when you press other keys
                publish = false;
            }

            if (publish) {
                //ROS_INFO_STREAM("velocity command: " << desired_velocity << " m/s");
                //ROS_INFO_STREAM("steering command: " << desired_steer << " rad");
                publish_to_drive(desired_velocity, desired_steer);
                prev_key_velocity = desired_velocity;
                prev_key_steer = desired_steer;
            }
        }
    }


};


/// Channel class method implementations

Channel::Channel() {
    ROS_INFO("Channel intialized without proper information");
    Channel("", "", -1, nullptr);
}

Channel::Channel(std::string channel_name, std::string drive_topic, int mux_idx_, Mux* mux) 
: mux_idx(mux_idx_), mp_mux(mux) {
    drive_pub = mux->n.advertise<ackermann_msgs::AckermannDriveStamped>(drive_topic, 10);
    channel_sub = mux->n.subscribe(channel_name, 1, &Channel::drive_callback, this);
}

void Channel::drive_callback(const ackermann_msgs::AckermannDriveStamped & msg) {
    if (mp_mux->mux_controller[this->mux_idx]) {
        drive_pub.publish(msg);
    }
}

int main(int argc, char ** argv) {
    ros::init(argc, argv, "mux_controller");
    Mux mx;
    ros::spin();
    return 0;
}
