#include "application.hpp"

#include "../shared/stringconvert.hpp"
#include "../shared/windows.hpp"
#include "window.hpp"

namespace pw
{
    // instance

	application::application()
	{
	}

	pw::window application::console_window() const
	{
		return ::GetConsoleWindow();
	}

	const std::string &application::module_file() const
    {
        return m_module_file;
    }


    // static

	std::unique_ptr<application> application::s_current;

	application &application::current()
	{
		initialize();
		return *s_current;
	}

    void application::initialize()
    {
        if (!s_current)
        {
			s_current.reset(new application());

            wchar_t applicationPath[MAX_PATH];
            GetModuleFileNameW(nullptr, applicationPath, _countof(applicationPath));

			s_current->m_module_file = pw::stringconvert::narrow(applicationPath);
        }
    }
}
