#ifndef __TOLOWER_HPP__
#define __TOLOWER_HPP__

#include <locale>
#include "stringconvert.hpp"

namespace pw
{
	std::locale const utf8("en_US.UTF-8");

	std::string tolower(const std::string &_string)
	{
		std::wstring result = pw::stringconvert::widen(_string);
		for (typename std::wstring::size_type i = 0; i < result.length(); ++i)
		{
			result[i] = std::tolower(result[i], utf8);
		}
		return pw::stringconvert::narrow(result);
	}
}

#endif
