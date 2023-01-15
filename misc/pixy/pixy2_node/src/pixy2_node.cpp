#include <ros/ros.h>
#include <pixy2_msgs/PixyData.h>
#include <pixy2_msgs/PixyBlock.h>
#include <pixy2_msgs/PixyResolution.h>
#include <pixy2_msgs/Servo.h>

#include "libpixyusb2.h"

#define DEFAULT_MAX_RETRIES 10
#define DEFAULT_RETRY_DURATION 10.0

class Pixy2Node
{
public:
    Pixy2Node();
    void spin();
private:
    void update();
    void setServo(const pixy2_msgs::Servo& msg);

    ros::NodeHandle node_handle_;
    ros::NodeHandle private_node_handle_;

    ros::Rate rate_;

    ros::Publisher publisher_;
    ros::Subscriber servo_subscriber_;
    std::string frame_id;

    ros::Publisher constantsPublisher_;

    bool use_servos_;

    Pixy2 pixy;

    uint16_t servoPositions[2] = {PIXY_RCS_CENTER_POS, PIXY_RCS_CENTER_POS};
};

Pixy2Node::Pixy2Node() :
                node_handle_(),
                private_node_handle_("~"),
                use_servos_(false),
                rate_(50.0)
{
    private_node_handle_.param<std::string>(std::string("frame_id"), frame_id, std::string("pixy_frame"));

    double rate;
    private_node_handle_.param("rate", rate, 50.0);
    rate_ = ros::Rate(rate);

    private_node_handle_.param("use_servos", use_servos_, false);

    if (use_servos_) {
        servo_subscriber_ = node_handle_.subscribe("servo_cmd", 20, &Pixy2Node::setServo, this);
    }

    double retryWaitTime;
    int maxRetries;

    private_node_handle_.param("maxRetries", maxRetries, DEFAULT_MAX_RETRIES);
    private_node_handle_.param("retryWaitTime", retryWaitTime, DEFAULT_RETRY_DURATION);

    int ret;
    int numTries = 0;
    while ((ret = pixy.init()) != 0 && ros::ok()) {
        numTries++;
        if (numTries > 10) {
            ROS_FATAL("Could not connect at all and reached max retries");
            ROS_BREAK();;
            break;
        }

        if (numTries == 1) {
            ROS_INFO("Will retry a maximum of %d times, waiting %f each time", maxRetries, retryWaitTime);
        }

        ROS_WARN("Attempt %d/%d failed. Retrying in %f seconds", numTries, maxRetries, retryWaitTime);

        if (numTries < 10) {
            ros::Duration(retryWaitTime).sleep();
        }
    }

    bool enable_lamp;
    private_node_handle_.param("enable_lamp", enable_lamp, false);

    if (enable_lamp) {
        pixy.setLamp(1,0);
    } else {
        pixy.setLamp(0,0);
    }

    int queue_size;
    private_node_handle_.param("queue_size", queue_size, 50);
    
    publisher_ = node_handle_.advertise<pixy2_msgs::PixyData>("block_data", queue_size);
    constantsPublisher_ = node_handle_.advertise<pixy2_msgs::PixyResolution>("pixy2_resolution", 5, true);

    // Publish the resolution message
    pixy2_msgs::PixyResolution resolution;
    resolution.width = pixy.frameWidth;
    resolution.height = pixy.frameHeight;

    constantsPublisher_.publish(resolution);
}

void Pixy2Node::update()
{
    // Query pixy for blocks
    pixy.ccc.getBlocks();

    pixy2_msgs::PixyData data;

    if (pixy.ccc.numBlocks > 0) {
        data.header.stamp = ros::Time::now();

        for (int i = 0; i < pixy.ccc.numBlocks; i++) {
            pixy2_msgs::PixyBlock pixy_block;

            Block raw_block = pixy.ccc.blocks[i];

            if (raw_block.m_signature > CCC_MAX_SIGNATURE) {
                pixy_block.type = pixy2_msgs::PixyBlock::COLOR_CODE;
            }
            else {
                pixy_block.type = pixy2_msgs::PixyBlock::NORMAL_SIGNATURE;
            }

            pixy_block.signature = raw_block.m_signature;
            pixy_block.roi.x_offset = raw_block.m_x;
            pixy_block.roi.y_offset = raw_block.m_y;
            pixy_block.roi.width = raw_block.m_width;
            pixy_block.roi.height = raw_block.m_height;
            pixy_block.roi.do_rectify = false;
            pixy_block.index = raw_block.m_index;
            pixy_block.age = raw_block.m_age;

            pixy_block.angle = (pixy_block.type == pixy2_msgs::PixyBlock::COLOR_CODE) ?
                                raw_block.m_angle : 0.0;

            data.blocks.push_back(pixy_block);
        }
    }
    else if (pixy.ccc.numBlocks < 0) {
        ROS_INFO("Pixy2 read error");
        return;
    }

    publisher_.publish(data);
}

void Pixy2Node::setServo(const pixy2_msgs::Servo& msg)
{
    if(msg.channel < 0 || msg.channel > 1) {
        return;
    }

    servoPositions[msg.channel] = msg.position;

    pixy.setServos(servoPositions[0], servoPositions[1]);
}

void Pixy2Node::spin()
{
    while(node_handle_.ok()) {
        update();

        ros::spinOnce();
        rate_.sleep();
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "pixy2_node");

    ROS_INFO("Pixy2Node for ROS");

    Pixy2Node myPixy2;
    myPixy2.spin();

    return 0;
}
