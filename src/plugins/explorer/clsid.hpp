#ifndef __PW_CLSID_HPP__
#define __PW_CLSID_HPP__

#include <ExDisp.h>

namespace pw
{

	template<typename _InterfaceType>
	struct clsid {};

	template<>
	struct clsid<IShellWindows> { static const CLSID id() { return CLSID_ShellWindows; } };

}

#endif
