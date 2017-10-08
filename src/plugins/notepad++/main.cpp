#include "main.hpp"

#include <algorithm>
#include <string>

#include "../../shared/tolower.hpp"
#include "../../shared/windows.hpp"

extern "C" __declspec(dllexport) bool current_directory(
	char *_in_module_name, char *_in_class_name, void* _handle,
	char **_out_string, int _in_max_length
)
{
	const std::string c_sNotepadModuleName = "notepad++.exe";
	const std::string c_sNotepadWClass = "Notepad++";

	std::string sModuleName(_in_module_name);
	std::string sClassName(_in_class_name);
	HWND hwnd = (HWND)_handle;

	typedef char out_string_t[];
	out_string_t *out_string = (out_string_t*)_out_string;

	if (pw::tolower(sModuleName) == c_sNotepadModuleName && sClassName == c_sNotepadWClass)
	{
		try
		{
			std::wstring title(GetWindowTextLength(hwnd) + 1, L'\0');
			GetWindowTextW(hwnd, &title[0], title.size()); //note: C++11 only

			//if (!arg.compare(0, prefix.size(), prefix))

			return false;
		}
		catch (...)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}