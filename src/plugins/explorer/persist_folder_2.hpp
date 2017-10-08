#ifndef __PW_PERSIST_FOLDER_2_HPP__
#define __PW_PERSIST_FOLDER_2_HPP__

#include <atlbase.h>
#include <ShObjIdl.h>
#include "com_exception.hpp"

namespace pw
{
	class persist_folder_2
	{

	public:

		typedef IPersistFolder2 interface_type;

		CComHeapPtr<ITEMIDLIST> current_folder()
		{
			LPITEMIDLIST itemidlist;
			if (SUCCEEDED(m_interface->GetCurFolder(&itemidlist)))
			{
				return CComHeapPtr<ITEMIDLIST>(itemidlist);
			}
			else
			{
				throw com_exception();
			}
		}

		persist_folder_2(interface_type* _interface) : m_interface(_interface)
		{
		}

	private:

		interface_type* m_interface;

	};
}

#endif
