#include "jump_task.hpp"

namespace pw
{
    jump_task::jump_task()
    {
    }

    jump_task::jump_task(const std::string &_title, const std::string &_application_path, const std::string &_arguments, const std::string &_description, const std::string &_icon_resource_path, int _icon_resource_index) :
        title(_title),
        application_path(_application_path),
        arguments(_arguments),
        description(_description),
        icon_resource_path(_icon_resource_path),
        icon_resource_index(_icon_resource_index)
    {
    }
}
