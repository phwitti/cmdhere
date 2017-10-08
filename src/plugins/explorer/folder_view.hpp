#ifndef __PW_FOLDER_VIEW_HPP__
#define __PW_FOLDER_VIEW_HPP__

#include <atlbase.h>
#include <ShObjIdl.h>
#include "com.hpp"
#include "com_exception.hpp"

namespace pw
{
	class folder_view
	{

	public:

		typedef IFolderView interface_type;

		template<typename _FolderType>
		CComPtr<_FolderType> folder()
		{
			_FolderType *folder;
			if (SUCCEEDED(m_interface->GetFolder(__uuidof(_FolderType), (void**)&folder)))
			{
				return folder;
			}
			else
			{
				throw com_exception();
			}
		}

		folder_view(interface_type *_interface) : m_interface(_interface)
		{
		}

	private:

		interface_type *m_interface;

	};
}

#endif
