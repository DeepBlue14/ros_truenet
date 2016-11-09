#include "../include/ros_truenet/Scrambler.hpp"

namespace rtn
{
	template<typename x_msg>
	Scrambler<x_msg>::Scrambler(const char* reroutedTopicName, unsigned int maxBufferLength, Scrambler::Type type)
	{
		this->type = type;
		buffer = new queue<x_msg>();
	}


	template<typename x_msg>
	void Scrambler<x_msg>::callback(x_msg msg)
	{
		int val = (random() % 5) + 1;

		if(val == 1)
		{
			msg = scramble(msg);
		}


		pub->publish(msg);
	}


	template<typename x_msg>
	x_msg Scrambler<x_msg>::scramble(x_msg msg)
	{
		cout << "scramble message..." << endl;

		switch(type)
		{
			case STD_MSGS_STRING:
				;
				break;
			case STD_MSGS_INT:
				;
				break;
			default:
				;

		}

		return msg;
	}


	template<typename x_msg>
	Publisher* Scrambler<x_msg>::getPublisher() const
	{
		return pub;
	}


	template<typename x_msg>
	Scrambler<x_msg>::~Scrambler()
	{
		while(buffer->size() > 0)
		{
			buffer->pop();
		}
		delete buffer;
	}



}
