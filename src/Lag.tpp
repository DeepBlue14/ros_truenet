#include "../include/ros_truenet/Lag.hpp"

namespace tnt
{
    template class Lag<std_msgs::String>;

	template<typename x_msg>
	Lag<x_msg>::Lag(const char* reroutedTopicName, unsigned int maxBufferLength) : NANO(1000000000.0)
	{
		buffer = new queue<x_msg>();
		prevTime = Time::now();
		currTime = Time::now();
		pub = new Publisher();
	}


    //callback here
	
	
	template<typename x_msg>
	Publisher* Lag<x_msg>::getPublisher() const
	{
	    return pub;
	}
	
	
	template<typename x_msg>
	int Lag<x_msg>::toNsec(Time time) const
	{
	    return (time.sec * NANO) + time.nsec;
	}
	
	
	template<typename x_msg>
	double Lag<x_msg>::toSec(Time time) const
	{
	    return (time.nsec / NANO) + static_cast<double>(time.sec);
	}


	template<typename x_msg>
	const char* Lag<x_msg>::toString() const
	{
		string str("---Lag---");

		return str.c_str();
	}
	
	
	template<typename x_msg>
	Lag<x_msg>::~Lag()
	{
		;
	}
}
