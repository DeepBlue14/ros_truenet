#ifndef RTN_OBJECT_HPP
#define RTN_OBJECT_HPP

#include <iostream>
#include <string>
#include <queue>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::queue;

namespace rtn
{
	template<typename x_msg>
	class RtnObject
	{
		public:
			virtual void callback(x_msg msg) = 0;
			virtual const char* toString() const = 0;
			virtual ~RtnObject();

		protected:
			queue* buffer;
	};
}
