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
		ros::start();
	
		buffer = new queue<x_msg>();
		prevTime = Time::now();
		currTime = Time::now();
		pub = new Publisher();
		lag = 5;
		variance = 1;
		x = 0;
		shape = 0;
	}


    template<typename x_msg>
	void Lag<x_msg>::callback(x_msg msg)
	{
	    currTime = Time::now();
	   	
	    if(getShape() == 3 && toSec(currTime) >= toSec(prevTime) + computeSineLag())
	    {
	        cout << "message: " << msg << endl;
	        prevTime = currTime;
	        pub->publish(msg);
	    }
	    else if(getShape() == 2 && toSec(currTime) >= toSec(prevTime) + computeExpLag())
	    {
	    	cout << "message: " << msg << endl;
	    	prevTime = currTime;
	        pub->publish(msg);
	    }
	    else if(getShape() == 1 && toSec(currTime) >= toSec(prevTime) + computeLinearLag())
	    {
	    	cout << "message: " << msg << endl;
	    	prevTime = currTime;
	        pub->publish(msg);
	    }
	    else if(getShape() == 0 && toSec(currTime) >= toSec(prevTime) + computeConstLag())
	    {
	    	cout << "message: " << msg << endl;
	    	prevTime = currTime;
	        pub->publish(msg);
	    }
		
	    if(buffer->size() > maxLength)
	    {
	        buffer->pop();
	    }

		buffer->push(msg);
	}
	
	
	template<typename x_msg>
	float Lag<x_msg>::setLag(float lag)
	{
		this->lag=lag;
	}
	
	template<typename x_msg>
	float Lag<x_msg>::getLag()
	{
		return lag;
	}
	
	template<typename x_msg>
	float Lag<x_msg>::setVariance(float variance)
	{
		this->variance=variance;
	}
	
	template<typename x_msg>
	float Lag<x_msg>::getVariance()
	{
		return variance;
	}
	
	template<typename x_msg>
	float Lag<x_msg>::computeSineLag()
	{
		cout << variance*sin(x) + lag << endl;
	    
	    float totalLag = lag + variance*sin(x);
	    
	    if(x < 2*M_PI)
	    {
	    	x += M_PI/12.0;			//x varies between 0 and 2*pi in increments of pi/12
	    }
	    else if(x >= 2*M_PI)
	    {
	    	x = 0;					//resets when x > 2*pi
	    }
		
		return totalLag;
	}
	
	template<typename x_msg>
	float Lag<x_msg>::computeExpLag()
	{
		cout << x*exp(lag) << endl;	//FIXME: messages stop producing after a few seconds 
									//due to exponential lag time
	    float totalLag = x*exp(lag);
	    
	    x += variance/100;			//divided by 100 because x was increasing too quickly
		
		return totalLag;
	}
	
	template<typename x_msg>
	float Lag<x_msg>::computeLinearLag()
	{
		cout << lag*x << endl;		//FIXME: lag becomes very large due to linearity
	    
	    float totalLag = lag*x;
	    
	    x += variance/100;			//divided by 100 because x was increasing too quickly
	    
		return totalLag;
	}
	
	template<typename x_msg>
	float Lag<x_msg>::computeConstLag()
	{
		cout << lag << endl;
	    
	    float totalLag = lag;		//NOTE: Variance is not a factor here
	    
		return totalLag;
	}
	
	template<typename x_msg>
	float Lag<x_msg>::setShape(float shape)
	{
		this->shape=shape;
	}
	
	template<typename x_msg>
	float Lag<x_msg>::getShape()
	{
		return shape;
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
