#ifndef __PW_COM_EXCEPTION_HPP__
#define __PW_COM_EXCEPTION_HPP__

#include <exception>
#include <string>

namespace pw
{

	class com_exception : public std::exception
	{

	public:

		com_exception() {}
		com_exception(const std::string &_what);

	};

}

#endif
