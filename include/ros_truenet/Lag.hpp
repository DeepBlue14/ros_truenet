#ifndef LAG_HPP
#define LAG_HPP

#include <iostream>
#include <string>
#include <queue>

#include <ros/ros.h>

#include <std_msgs/String.h>

#include <dynamic_reconfigure/server.h>
#include <ros_truenet/Truenet2Config.h>

#include <cmath>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::queue;

using namespace ros;

namespace tnt
{
	template<typename x_msg>
	class Lag
	{
		public:
		    enum RoundPolicy
		    {
		        FLOOR,
		        CEILING,
		        ROUND
		    };
		    
			Lag(const char* reroutedTopicName, unsigned int maxBufferLength);
			void callback(x_msg msg);
			float setLag(float lag);
			float setVariance(float variance);
			float getVariance();
			Publisher* getPublisher() const;
			const char* toString() const;
			~Lag();

		private:
		    int toNsec(Time time) const;
		    double toSec(Time time) const;
			float lag;
			float x;
			bool goingUp;
			float variance;
		    const float NANO;// = 1000000000.0;
			queue<x_msg>* buffer;
			Time prevTime;
			Time currTime;
			Publisher* pub;
			unsigned int maxLength;
			
		
	};
}
#include "../../src/Lag.tpp"

#endif /* LAG_HPP */
