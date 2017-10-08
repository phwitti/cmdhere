#ifndef __PW_APPLICATION_HPP__
#define __PW_APPLICATION_HPP__

#include <memory>
#include <string>

namespace pw
{
	class window;
    class application
    {

		// instance:

	private:

		application();

    public:

		pw::window console_window() const;
        const std::string &module_file() const;
        
    private:

		std::string m_module_file;


		// static:

	public:

		static application &current();

	private:

		static void initialize();
        static std::unique_ptr<application> s_current;

    };
}

//

#endif
