#ifndef __PW_DYNAMIC_LIBRARY_HPP__
#define __PW_DYNAMIC_LIBRARY_HPP__

#include "exception.hpp"

namespace pw
{
	class dynamic_library
	{

	public:

		dynamic_library();
		dynamic_library(const std::string &_path);
		~dynamic_library();

		void load(const std::string &_path);
		void unload();

		void invoke(const std::string &_function);
		template<typename _Result>
		_Result invoke(const std::string &_function);
		template<typename _Result, typename _Param0, typename _Param1, typename _Param2, typename _Param3, typename _Param4>
		_Result invoke(const std::string &_function, _Param0 _param0, _Param1 _param1, _Param2 _param2, _Param3 _param3, _Param4 _param4);

		std::string load_string(unsigned int _id, int _max_string_length = 256) const;
		std::string load_string(unsigned int _id, const std::string &_fallback, int _max_string_length = 256) const;

	private:

		void *m_module;

	};

	template<typename _Result>
	_Result dynamic_library::invoke(const std::string &_function)
	{
		pw::contract::ensure<pw::invalid_operation_exception>(m_module != nullptr, "Module has to be loaded before calling invoke");

		typedef _Result(*procedure)();
		procedure proc = (procedure)GetProcAddress((HMODULE)m_module, _function.c_str());

		pw::contract::ensure<pw::invalid_operation_exception>(proc != nullptr, "Procedure hasn't been found in the module.");
		return proc();
	}

	template<typename _Result, typename _Param0, typename _Param1, typename _Param2, typename _Param3, typename _Param4>
	_Result dynamic_library::invoke(const std::string &_function, _Param0 _param0, _Param1 _param1, _Param2 _param2, _Param3 _param3, _Param4 _param4)
	{
		pw::contract::ensure<pw::invalid_operation_exception>(m_module != nullptr, "Module has to be loaded before calling invoke");

		typedef _Result(*procedure)(_Param0, _Param1, _Param2, _Param3, _Param4);
		procedure proc = (procedure)GetProcAddress((HMODULE)m_module, _function.c_str());
		
		pw::contract::ensure<invalid_operation_exception>(proc != nullptr, "Procedure hasn't been found in the module.");
		return proc(_param0, _param1, _param2, _param3, _param4);
	}
}

//

#endif
