
#include <iostream>

#include "application.hpp"
#include "program.hpp"

extern "C"
int wmain(int _argc, wchar_t** _argv)
{
	try
	{
		cmdhere::program().run(std::vector<std::wstring>(_argv, _argv + _argc));
	}
	catch (std::exception &_exception)
	{
		std::cerr << _exception.what() << std::endl;
	}
}
