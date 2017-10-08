#ifndef __PW_JUMP_LIST_HPP__
#define __PW_JUMP_LIST_HPP__

//

#include <list>

#include "application.hpp"
#include "com_object.hpp"
#include "jump_task.hpp"

//

namespace pw
{
    class jump_list : public com_object
    {

    public:
        
        void commit();
        void commit(const pw::application &_application);
        
        //
        
        std::list<jump_task> jump_tasks;

    };
}

//

#endif
