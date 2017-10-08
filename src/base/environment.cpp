#include "environment.hpp"

#include "../shared/stringconvert.hpp"
#include "../shared/windows.hpp"
#include "exception.hpp"

#include <ShlObj.h>

namespace pw
{
	std::string environment::system_directory()
	{
		wchar_t directory[MAX_PATH] = { 0 };
		::GetSystemDirectoryW(directory, MAX_PATH);
		return pw::stringconvert::narrow(directory);
	}

	std::string environment::user_directory()
	{
		wchar_t directory[MAX_PATH] = { 0 };
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, SHGFP_TYPE_CURRENT, directory)))
		{
			return pw::stringconvert::narrow(directory);
		}
		else
		{
			throw pw::winapi_exception();
		}
	}

	std::string environment::current_locale()
	{
		wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
		GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
		return pw::stringconvert::narrow(localeName);
	}
}
