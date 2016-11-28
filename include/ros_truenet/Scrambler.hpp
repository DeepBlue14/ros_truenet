#ifndef SCRAMBLER_HPP
#define SCRAMBLER_HPP

#include <ros/ros.h>
#include <std_msgs/String.h>

#include <iostream>
#include <string>
#include <queue>
#include <sstream>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::queue;

using namespace ros;

namespace rtn
{

	template<typename x_msg>
	class Scrambler
	{
		public:
			enum Type
			{
				STD_MSGS_STRING,
				STD_MSGS_INT,
				SENSOR_MSGS_IMAGE,
				SENSOR_MSGS_POINTCLOUD2
			};

			Scrambler(const char* reroutedTopicName, unsigned int maxBufferLength, Scrambler::Type type);
			x_msg scramble(x_msg msg);
			void callback(x_msg msg);
			Publisher* getPublisher() const;
			const char* toString() const;
			~Scrambler();

		private:
			Type type;
			queue<x_msg>* buffer;
			Publisher* pub;
			unsigned int maxLength;
	};
}

#include "../../src/Scrambler.cpp"

#endif /* SCRAMBLER_HPP */
