#ifndef Downtime_HPP
#define Downtime_HPP

#include <iostream>
#include <string>
#include <queue>

#include <ros/ros.h>

#include <std_msgs/String.h>

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
			Publisher* getPublisher() const;
			const char* toString() const;
			~Lag();

		private:
		    int toNsec(Time time) const;
		    double toSec(Time time) const;
		
		    const float NANO;// = 1000000000.0;
			queue<x_msg>* buffer;
			bool isPublishing;
			Time prevTime;
			Time currTime;
			Publisher* pub;
			unsigned int maxLength;
			
		
	};
}
#include "../../src/Downtime.tpp"

#endif /* Downtime_HPP */
