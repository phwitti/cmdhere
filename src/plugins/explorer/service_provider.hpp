#ifndef __PW_SERVICE_PROVIDER_HPP__
#define __PW_SERVICE_PROVIDER_HPP__

#include <atlbase.h>
#include <ShlObj.h>
#include "com.hpp"

namespace pw
{
	class service_provider
	{

	public:

		typedef IServiceProvider interface_type;

		template<typename _InterfaceType>
		CComPtr<_InterfaceType> query_service(const GUID &_service_id)
		{
			_InterfaceType *_interface;
			if (SUCCEEDED(m_interface->QueryService(_service_id, __uuidof(_InterfaceType), (void**)&_interface)))
			{
				return _interface;
			}
			else
			{
				throw pw::com_exception();
			}
		}

		service_provider(interface_type *_interface) : m_interface(_interface)
		{
		}

	private:

		interface_type *m_interface;

	};
}

#endif
