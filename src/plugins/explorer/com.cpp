#include "com.hpp"

#include "../../shared/windows.hpp"

namespace pw
{
	com::com()
	{
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	}

	com::~com()
	{
		CoUninitialize();
	}

	com com::initialize()
	{
		return com();
	}
}