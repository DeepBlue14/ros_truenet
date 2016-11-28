#include "../include/ros_truenet/Downtime.hpp"

namespace tnt
{
    template class Lag<std_msgs::String>;

	template<typename x_msg>
	Lag<x_msg>::Lag(const char* reroutedTopicName, unsigned int maxBufferLength) : NANO(1000000000.0), isPublishing(true)
	{
		buffer = new queue<x_msg>();
		prevTime = Time::now();
		currTime = Time::now();
		pub = new Publisher();
	}


    template<typename x_msg>
	void Lag<x_msg>::callback(x_msg msg)
	{
		int val = (random() % 100) + 1;	// generate random number between 1-10.
		
		if(val == 1)
		{
			isPublishing = false;		// if number == 1, then set isPublishing to false
			
			cout << "stopped publishing" << endl;
		}
		else if(val == 10)
		{
			isPublishing = true;		// else if number == 10, then set isPublishing to true
			
			cout << "started publishing" << endl;
		}
		
		if(isPublishing == true)
		{
			pub->publish(msg);			// if isPublishing == true, then pub->publish(msg)
			
			cout << "..." << endl;
		}
		else {}							// else do nothing {}
	}
	
	
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
