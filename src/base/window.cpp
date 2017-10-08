#include "window.hpp"

#include <Psapi.h> // GetModuleFileNameEx

#include "../shared/stringconvert.hpp"

namespace pw
{
	// instance

	window::window(HWND _hwnd) : 
		m_hwnd(_hwnd)
	{
	}

	HWND window::hwnd() const
	{
		return m_hwnd;
	}

	std::string window::module_file()
	{
		std::wstring::value_type tModuleName[MAX_PATH] = { 0 };
		DWORD  dwPID;
		HANDLE hProcess;
		::GetWindowThreadProcessId(m_hwnd, &dwPID);
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, dwPID);
		GetModuleFileNameExW(hProcess, NULL, tModuleName, _countof(tModuleName) * sizeof(std::wstring::value_type));
		CloseHandle(hProcess);

		return pw::stringconvert::narrow(tModuleName);
	}

	std::string window::class_name()
	{
		std::wstring::value_type tClassName[MAX_CLASS_NAME] = { 0 };
		GetClassNameW(m_hwnd, tClassName, MAX_CLASS_NAME);
		return pw::stringconvert::narrow(tClassName);
	}

	void window::show()
	{
		::ShowWindow(m_hwnd, SW_SHOW);
	}

	void window::hide()
	{
		::ShowWindow(m_hwnd, SW_HIDE);
	}


	// static

	BOOL CALLBACK EnumWindowsCallback(__in HWND _hwnd, __in LPARAM _lparam)
	{
		HWND &topmost = *(HWND*)_lparam;
		if (::IsWindowVisible(_hwnd) && ::GetWindowTextLengthW(_hwnd) != 0 && _hwnd != topmost)
		{
			topmost = _hwnd;
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
		
	window window::topmost(const window &_exclude)
	{
		HWND topmost = _exclude.hwnd();
		::EnumWindows(EnumWindowsCallback, (LPARAM)&topmost);
		return window(topmost);
	}
}
