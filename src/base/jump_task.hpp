#ifndef __PW_JUMP_TASK_HPP__
#define __PW_JUMP_TASK_HPP__

#include <string>

namespace pw
{
    struct jump_task
    {

        jump_task();
        jump_task(const std::string &_title, const std::string &_application_path, const std::string &_arguments, const std::string &_description, const std::string &_icon_resource_path, int _icon_resource_index);
        
        //
        
        std::string title;
        std::string application_path;
        std::string arguments;
        std::string description;
        std::string icon_resource_path;
        int icon_resource_index;

    };
}

#endif
