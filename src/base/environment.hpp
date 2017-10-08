#ifndef __PW_ENVIRONMENT_HPP__
#define __PW_ENVIRONMENT_HPP__

#include <string>

namespace pw
{
	class environment
	{

	public:

		static std::string system_directory();
		static std::string user_directory();
		static std::string current_locale();

	};
}

#endif
