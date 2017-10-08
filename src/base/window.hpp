#ifndef __PW_WINDOW_HPP__
#define __PW_WINDOW_HPP__

#include <string>
#include "../shared/windows.hpp"

namespace pw
{

	class window
	{

		// instance

	public:

		window(HWND _hwnd);

		HWND hwnd() const;

		std::string module_file();
		std::string class_name();

		void show();
		void hide();

	private:

		HWND m_hwnd;


		// static

	public:
		
		static window topmost(const window &_exclude);

	};
}

#endif
