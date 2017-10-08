#ifndef __PW_WEB_BROWSER_APP_HPP__
#define __PW_WEB_BROWSER_APP_HPP__

#include <ExDisp.h>
#include "com_exception.hpp"

namespace pw
{
	class web_browser_app
	{

	public:

		typedef IWebBrowserApp interface_type;

		HWND hwnd()
		{
			HWND hwnd;
			if (SUCCEEDED(m_interface->get_HWND((LONG_PTR*)&hwnd)))
			{
				return hwnd;
			}
			else
			{
				throw pw::com_exception();
			}
		}

		web_browser_app(interface_type *_interface) : m_interface(_interface)
		{
		}

	private:

		interface_type *m_interface;

	};
}

#endif
