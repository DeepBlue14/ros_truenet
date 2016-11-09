#include <ros/ros.h>

#include <std_msgs/String.h>

#include "../include/ros_truenet/Scrambler.hpp"

using namespace ros;
using namespace rtn;

int main(int argc, char** argv)
{
    init(argc, argv, "lag");
    
    NodeHandle nh;
    Scrambler<std_msgs::String> scrambler("/chatter/out", 10, Scrambler<std_msgs::String>::STD_MSGS_STRING);
    Subscriber sub = nh.subscribe("/chatter/in",
                                  1,
                                  &Scrambler<std_msgs::String>::callback,
                                  &scrambler);
    Publisher* pub = scrambler.getPublisher();
    *pub = nh.advertise<std_msgs::String>("/chatter/out", 1);
    
    spin();

    return EXIT_SUCCESS;
}
