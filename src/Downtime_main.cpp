#include <ros/ros.h>

#include <std_msgs/String.h>

#include "../include/ros_truenet/Downtime.hpp"

using namespace ros;
using namespace tnt;

int main(int argc, char** argv)
{
    init(argc, argv, "lag");
    
    NodeHandle nh;
    Lag<std_msgs::String> lag("/chatter/out", 10);
    Subscriber sub = nh.subscribe("/chatter/in",
                                  1,
                                  &Lag<std_msgs::String>::callback,
                                  &lag);
    Publisher* pub = lag.getPublisher();
    *pub = nh.advertise<std_msgs::String>("/chatter/out", 1);
    
    spin();

    return EXIT_SUCCESS;
}
