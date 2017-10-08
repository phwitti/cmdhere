#ifndef __PW_COM_HPP__
#define __PW_COM_HPP__

#include <atlbase.h>
#include <objbase.h>
#include <winerror.h>

#include <vector>

#include "clsid.hpp"
#include "com_exception.hpp"

namespace pw
{
	class com
	{

	public:

		template<typename _InterfaceType>
		CComPtr<_InterfaceType> create_instance()
		{
			_InterfaceType *_interface;
			HRESULT result = CoCreateInstance(pw::clsid<_InterfaceType>::id(), NULL, CLSCTX_ALL, __uuidof(_InterfaceType), (void**)&_interface);

			switch (result)
			{
				case S_OK: return _interface;
				case REGDB_E_CLASSNOTREG: throw pw::com_exception("REGDB_E_CLASSNOTREG: A specified class is not registered in the registration database.Also can indicate that the type of server you requested in the CLSCTX enumeration is not registered or the values for the server types in the registry are corrupt.");
				case CLASS_E_NOAGGREGATION: throw pw::com_exception("CLASS_E_NOAGGREGATION: This class cannot be created as part of an aggregate.");
				case E_NOINTERFACE: throw pw::com_exception("E_NOINTERFACE: The specified class does not implement the requested interface.");
				case E_POINTER: throw pw::com_exception("E_POINTER: The ppv parameter is NULL.");
				default: throw pw::com_exception();
			}
		}

		template<typename _InterfaceType, typename _ObjectType>
		CComPtr<_InterfaceType> query_interface(const _ObjectType &_object)
		{
			_InterfaceType *_interface;
			HRESULT result = _object->QueryInterface(__uuidof(_InterfaceType), (void**)&_interface);

			switch (result)
			{
			case S_OK: return _interface;
			case E_NOINTERFACE: throw pw::com_exception("E_NOINTERFACE: The controlling IUnknown does not expose the requested interface.");
			case E_POINTER: throw pw::com_exception("E_POINTER: The ppv parameter is NULL.");
			default: throw pw::com_exception();
			}
		}

		template<typename _InterfaceType, typename _ObjectType>
		bool try_query_interface(const _ObjectType &_object, _InterfaceType **_interface)
		{
			return SUCCEEDED(_object->QueryInterface(__uuidof(_InterfaceType), (void**)_interface));
		}

		//

	private:

		com();

	public:

		~com();
		static com initialize();

	};
}

#endif