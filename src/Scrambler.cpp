#include "ros/ros.h"
#include "std_msgs/String.h"
#include "stdlib.h"

#include <iostream>
using namespace std;

std_msgs::String oldMsg;

ros::Publisher chatter_pub;

void callback(std_msgs::String msg);

void send(std_msgs::String msg);

void callback(std_msgs::String msg)
{
	int val = (random() % 5) + 1;
	
	if(val == 1)
	{
		cout << val << endl;
	}
	
	

	send(msg);
}


void send(std_msgs::String msg)
{
	chatter_pub.publish(msg);
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "listener");

    ros::NodeHandle n;

	srandom(1);

    ros::Subscriber sub = n.subscribe("chatter/in", 1000, callback);

    chatter_pub=n.advertise<std_msgs::String>("chatter", 1000);

    ros::spin();
    
    return 0;
}
