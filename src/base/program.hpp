#ifndef __CMDHERE_PROGRAM_HPP__
#define __CMDHERE_PROGRAM_HPP__

#include <string>
#include <vector>

#include "../shared/stringconvert.hpp"

namespace cmdhere
{
    class program
    {

    public:

		void run(std::vector<std::wstring> _args);
        void run(std::vector<std::string> _args);
        
    private:

        void create_jump_list();
		void open_console_default(std::vector<std::string> _args);
		void open_console_elevated();

		bool try_current_directory(std::string * _path);

		void open_console(const std::string &_path);
		void open_console();

		std::string console_path();

        //

    private:

		const std::string c_cmd_file_name = "cmd.exe";
		const std::string c_plugins_directory = "\\plugins\\";
		const std::string c_plugins_wildcart = "*.dll";

        // Command line arguments to start appropriate behaviour
        const std::string c_runas_argument = "--runas";

        // Use english default values, if localisation fails
		const std::string c_runas_default_title = "Run as Administrator";

        // The library that contains the localized run-as-administrator string
        const int c_runas_title_string_id = 37417;
        const std::string c_runas_localization_library = "shell32.dll.mui";

		// Library that contains the run-as-adminstrator icon
		const int c_runas_icon_index = 73;
		const std::string c_runas_icon_library = "imageres.dll";

    };
}

//

#endif
