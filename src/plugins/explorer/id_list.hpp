#ifndef __PW_ID_LIST_HPP__
#define __PW_ID_LIST_HPP__

#include <atlbase.h>
#include <ShlObj.h>

#include "../../shared/stringconvert.hpp"
#include "com_exception.hpp"

namespace pw
{
	class id_list
	{

	public:

		typedef ITEMIDLIST object_type;

		std::string path()
		{
			std::wstring::value_type path[MAX_PATH] = { 0 };
			if (!SHGetPathFromIDList(m_object, path))
			{
				throw com_exception("not a directory");
			}
			return pw::stringconvert::narrow(path);
		}

		id_list(object_type *_object) : m_object(_object)
		{
		}

	private:

		object_type *m_object;

	};
}

#endif
