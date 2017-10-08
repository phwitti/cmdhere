#include "com_exception.hpp"

namespace pw
{
	com_exception::com_exception(const std::string &_what) : std::exception(_what.c_str())
	{
	}
}
