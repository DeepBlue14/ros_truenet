#include "../include/ros_truenet/Lag.hpp"

namespace tnt
{
    template class Lag<std_msgs::String>;

	template<typename x_msg>
	Lag<x_msg>::Lag(const char* reroutedTopicName, unsigned int maxBufferLength) : NANO(1000000000.0)
	{
		int argc = 0;
		char** argv;
		init(argc, argv, "lag");
		//NodeHandle nh;
		ros::start();
	
		buffer = new queue<x_msg>();
		prevTime = Time::now();
		currTime = Time::now();
		pub = new Publisher();
		lag = 0.5;
	}


    template<typename x_msg>
	void Lag<x_msg>::callback(x_msg msg)
	{
	    currTime = Time::now();
	    
	    //cout << "prevTime=" << prevTime.nsec << " | currTime=" << currTime.nsec << endl;
	    //cout << (currTime.nsec / 1000000000.0) << endl; //nsec is nanoseconds
	    //cout << toSec(currTime) << " >=? " << toSec(prevTime) << endl;
	    
	    //if(currTime.sec >= prevTime.sec + 5)
	    if(toSec(currTime) >= toSec(prevTime) + lag)
	    {
	        cout << "message: " << msg << endl;
	        prevTime = currTime;
	        pub->publish(msg);
	    }
	    
	    
	    if(buffer->size() > maxLength)
	    {
	        //buffer->pop_front();
	        buffer->pop();
	    }
		
		//buffer->push_back(msg);
		buffer->push(msg);
	}
	
	
	template<typename x_msg>
	float Lag<x_msg>::setLag(float lag)
	{
		this->lag=lag;
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
