#include <ros/ros.h>

#include <std_msgs/String.h>

#include "../include/ros_truenet/Lag.hpp"

#include <dynamic_reconfigure/server.h>
#include <ros_truenet/Truenet2Config.h>

using namespace ros;
using namespace tnt;

Lag<std_msgs::String> lag("/chatter/out", 10);

void callback(ros_truenet::Truenet2Config &config, uint32_t level) {
  ROS_INFO("Reconfigure Request: %f %d %s %d", 
            config.Lag, config.Variance,
            config.Activate?"True":"False", 	//FIXME: config.Activate not yet implemented
            config.Shape);
  if(config.Variance <= config.Lag)
  {
  	lag.setVariance(config.Variance);
  }
  else
  {
  	config.Variance = lag.getVariance();
  }
  if(config.Lag >= config.Variance)
  {
  	lag.setLag(config.Lag);
  }
  else
  {
  	config.Lag = lag.getLag();
  }
  lag.setShape(config.Shape);
}

int main(int argc, char** argv)
{
    init(argc, argv, "lag");
    
    NodeHandle nh;
    
    Subscriber sub = nh.subscribe("/chatter/in",
                                  1,
                                  &Lag<std_msgs::String>::callback,
                                  &lag);
    Publisher* pub = lag.getPublisher();
    *pub = nh.advertise<std_msgs::String>("/chatter/out", 1);
    
    dynamic_reconfigure::Server<ros_truenet::Truenet2Config> server;
  	dynamic_reconfigure::Server<ros_truenet::Truenet2Config>::CallbackType f;

  	f = boost::bind(&callback, _1, _2);
  	server.setCallback(f);

  	ROS_INFO("Spinning node");
    spin();

    return EXIT_SUCCESS;
}
