#ifndef __PW_SHELL_WINDOWS_HPP__
#define __PW_SHELL_WINDOWS_HPP__

#include <atlbase.h>
#include <ExDisp.h>
#include "com.hpp"

namespace pw
{
	class shell_windows
	{
		friend class pw::com;

	public:

		typedef IShellWindows interface_type;

		template<typename _InterfaceType>
		std::vector<CComPtr<_InterfaceType>> to_vector()
		{
			std::vector<CComPtr<_InterfaceType>> vector;

			VARIANT variant;
			V_VT(&variant) = VT_I4;
			IDispatch* dispatch;
			for (V_I4(&variant) = 0; m_interface->Item(variant, &dispatch) == S_OK; V_I4(&variant)++)
			{
				vector.push_back(dispatch);
			}

			return vector;
		}

		shell_windows(interface_type *_interface) : m_interface(_interface)
		{
		}

	private:

		interface_type *m_interface;

	};
}

#endif
