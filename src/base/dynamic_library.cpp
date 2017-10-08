#include "dynamic_library.hpp"

#include <exception>
#include <memory>

#include "../shared/stringconvert.hpp"
#include "../shared/windows.hpp"
#include "exception.hpp"


//

namespace pw
{
	dynamic_library::dynamic_library() :
        m_module(nullptr)
    {
    }

	dynamic_library::dynamic_library(const std::string &_path) :
		m_module(nullptr)
	{
		load(_path);
	}

	dynamic_library::~dynamic_library()
    {
        try
        {
            unload();
        }
        catch (...)
        {
            // Nothing to do
        }
    }

    //

    void dynamic_library::load(const std::string &_path)
    {
        pw::contract::ensure<pw::argument_null_exception>(_path != "", "Input parameter cannot be an empty string");
        pw::contract::ensure<pw::invalid_operation_exception>(m_module == nullptr, "There's still a module loaded. Call Unload before loading another module.");

        m_module = LoadLibraryW(pw::stringconvert::widen(_path).c_str());

        if (m_module == nullptr)
        {
            throw pw::winapi_exception();
        }
    }

    void dynamic_library::unload()
    {
        if (m_module != nullptr)
        {
            if (!FreeLibrary(static_cast<HMODULE>(m_module)))
            {
                throw pw::winapi_exception();
            }
            m_module = nullptr;
        }
    }

    //

	void dynamic_library::invoke(const std::string & _function)
	{
		if (m_module != nullptr)
		{
			typedef void(*procedure)();

			procedure proc = (procedure)GetProcAddress((HMODULE)m_module, _function.c_str());
			if (proc != nullptr)
			{
				proc();
			}
		}
	}

    std::string dynamic_library::load_string(unsigned int _id, int _max_string_length) const
    {
        pw::contract::ensure<pw::invalid_operation_exception>(m_module != nullptr, "Module hasn't been loaded yet.");

		std::unique_ptr<std::wstring::value_type[]> buffer(new std::wstring::value_type[_max_string_length]);
        LoadStringW(static_cast<HINSTANCE>(m_module), _id, buffer.get(), _max_string_length);

		return pw::stringconvert::narrow(buffer.get());
    }

    std::string dynamic_library::load_string(unsigned int _id, const std::string &_fallback, int _max_string_length) const
    {
        try
        {
            std::string out = load_string(_id, _max_string_length);
            if (out != "")
            {
                return out;
            }

            throw pw::invalid_operation_exception("String could not be read from the module.");
        }
        catch (...)
        {
            return _fallback;
        }
    }
}
