#ifndef __PW_SHELL_BROWSER_HPP__
#define __PW_SHELL_BROWSER_HPP__

#include <atlbase.h>
#include <ShObjIdl.h>
#include "com.hpp"
#include "com_exception.hpp"

namespace pw
{
	class shell_browser
	{

	public:

		typedef IShellBrowser interface_type;

		CComPtr<IShellView> active_shell_view()
		{
			IShellView *shellview;
			if (SUCCEEDED(m_interface->QueryActiveShellView(&shellview)))
			{
				return shellview;
			}
			else
			{
				throw com_exception();
			}
		}

		shell_browser(interface_type *_interface) : m_interface(_interface)
		{
		}

	private:

		interface_type *m_interface;

	};
}

#endif
