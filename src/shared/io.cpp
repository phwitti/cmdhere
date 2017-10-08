#include "io.hpp"

#include <sstream>
#include <Windows.h>
#include <Shlwapi.h>

#include "stringconvert.hpp"

namespace pw
{
	namespace io
	{
		std::string path::file_name(const std::string &_path)
		{
			std::wstring _wpath = pw::stringconvert::widen(_path);
			std::wstring::value_type* wpath = new std::wstring::value_type[_wpath.length() + 1];
			wpath[_wpath.length()] = '\0';
			StrCpyW(wpath, _wpath.c_str());
			PathStripPathW(wpath);
			std::wstring wstring_path(wpath);
			delete[] wpath;
			return pw::stringconvert::narrow(wstring_path);
		}

		std::string path::directory(const std::string &_path)
		{
			std::wstring _wpath = pw::stringconvert::widen(_path);
			std::wstring::value_type* wpath = new std::wstring::value_type[_wpath.length() + 1];
			wpath[_wpath.length()] = '\0';
			StrCpyW(wpath, _wpath.c_str());
			PathRemoveFileSpecW(wpath);
			std::wstring wstring_path(wpath);
			delete[] wpath;
			return pw::stringconvert::narrow(wstring_path);
		}

		std::string path::seperator()
		{
			return "\\";
		}

		std::string path::combine(const std::initializer_list<std::string> &_parts)
		{
			std::basic_stringstream<std::string::value_type> stringstream;
			unsigned int i = 1;
			for (const std::string &string : _parts)
			{
				stringstream << string;

				if (i != _parts.size())
					stringstream << path::seperator();

				i++;
			}
			return stringstream.str();
		}

		//

		std::vector<std::string> directory::files(const std::string &_path)
		{
			std::wstring _wpath = pw::stringconvert::widen(_path);
			std::vector<std::string> result;

			WIN32_FIND_DATA findFileData;
			HANDLE hFind = FindFirstFileW(_wpath.c_str(), &findFileData);

			if (INVALID_HANDLE_VALUE == hFind)
			{
				return result;
			}

			do
			{
				if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) ||
					(findFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE && !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)))
				{
					result.push_back(pw::stringconvert::narrow(findFileData.cFileName));
				}
			} while (FindNextFileW(hFind, &findFileData) != 0);

			FindClose(hFind);

			return result;
		}

	}
}
