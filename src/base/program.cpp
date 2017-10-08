#include "program.hpp"

//

#include <algorithm>

//

#include "../shared/io.hpp"

#include "action_map.hpp"
#include "application.hpp"
#include "dynamic_library.hpp"
#include "environment.hpp"
#include "jump_list.hpp"
#include "process.hpp"
#include "window.hpp"

//

#if __cplusplus < 201402L && _MSVC_LANG < 201402L
#define constexpr
#endif

//

namespace cmdhere
{
	void program::run(std::vector<std::wstring> _args)
	{
		std::vector<std::string> args;
		args.resize(_args.size());
		
		std::transform(_args.begin(), _args.end(), args.begin(), pw::stringconvert::narrow);

		this->run(args);
	}

	void program::run(std::vector<std::string> _args)
	{
		// Create a map that associates the command line arguments with their appropriate behaviour
		pw::action_map<std::string> action_map;
		action_map.emplace(c_runas_argument, [this]() { this->open_console_elevated(); });

		// There's no possibility to check, if the jumplist has already been created on a previous startup
		// -> Create new one
		this->create_jump_list();

		if (!action_map.execute_first(_args))
		{
			this->open_console_default(_args);
		}
	}

	void program::create_jump_list()
	{
		// Create a new jumplist
		pw::jump_list jump_list;

		// Get the current location of the executable
		std::string module_file = pw::application::current().module_file();

		// Try to load the localized system file that includes the shutdown option strings
		pw::dynamic_library localized_runas;

		try
		{
			localized_runas.load(pw::io::path::combine({ pw::environment::system_directory(), pw::environment::current_locale(), c_runas_localization_library }));
		}
		catch (...)
		{
			// Nothing to do
		}

		// Read the jumplist item title from the localized system file "shell32.dll.mui"
		std::string runas = localized_runas.load_string(c_runas_title_string_id, c_runas_default_title);

		// Create and add jumpitems to the jumplist
		jump_list.jump_tasks.push_back(pw::jump_task(runas, module_file, c_runas_argument, "", c_runas_icon_library, c_runas_icon_index));

		// Push the changed jumplist to the shell
		jump_list.commit();
	}

	void program::open_console_default(std::vector<std::string> _args)
	{
		// check, if path is appended (parameter)
		if (_args.size() <= 1)
		{
			std::string current_directory;
			if (this->try_current_directory(&current_directory))
			{
				this->open_console(current_directory);
			}
			else
			{
				this->open_console();
			}
		}
		else
		{
			// -> then use that
			this->open_console(_args[1]);
		}
	}

	void program::open_console_elevated()
	{
		// first hide this console window
		pw::window &console_window = pw::application::current().console_window();
		console_window.hide();

		std::string current_directory;
		if (this->try_current_directory(&current_directory))
		{
			pw::process(console_window.module_file(), "", current_directory, true);
		}
		else
		{
			// to open console elevated, open this module elevated, but without parameters
			pw::process(console_window.module_file(), "", true);
		}
	}

	//

	bool program::try_current_directory(std::string *_path)
	{
		namespace io = pw::io;

		pw::window console_window = pw::application::current().console_window();

		std::string console_module = console_window.module_file();
		std::string plugins_directory = io::path::directory(console_module) + c_plugins_directory;
		std::vector<std::string> plugins = io::directory::files(plugins_directory + c_plugins_wildcart);

		pw::window topmost_window = pw::window::topmost(/* _exclude : */console_window);
		std::string topmost_module = io::path::file_name(topmost_window.module_file());
		std::string topmost_class = topmost_window.class_name();

		constexpr const int c_out_path_length = 256;
		char out_path[c_out_path_length];
		for (auto &plugin : plugins)
		{
			try
			{
				if (pw::dynamic_library(plugins_directory + plugin).invoke<bool>("current_directory",
					topmost_module.c_str(), topmost_class.c_str(), topmost_window.hwnd(),
					(char**)&out_path, c_out_path_length))
				{
					*_path = out_path;
					return true;
				}
			}
			catch (...)
			{
				// nothing to do
			}
		}

		return false;
	}

	void program::open_console()
	{
		this->open_console(pw::environment::user_directory());
	}

	void program::open_console(const std::string & _path)
	{
		pw::process(console_path(), _path).wait(std::numeric_limits<float>::infinity());
	}

	std::string program::console_path()
	{
		return pw::environment::system_directory() + pw::io::path::seperator() + c_cmd_file_name;
	}
}
