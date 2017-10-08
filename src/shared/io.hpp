#ifndef __PW_IO_HPP__
#define __PW_IO_HPP__

#include <vector>

namespace pw
{
	namespace io
	{
		class path
		{

		public:

			static std::string file_name(const std::string &_path);
			static std::string directory(const std::string &_path);
			static std::string seperator();
			static std::string combine(const std::initializer_list<std::string> &_parts);

		};

		class directory
		{

		public:

			static std::vector<std::string> files(const std::string &_path);

		};
	}
}

#endif
