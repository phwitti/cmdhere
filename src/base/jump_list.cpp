#include "jump_list.hpp"

//

#include <Windows.h>
#include <ShObjIdl.h>
#include <propvarutil.h>
#include <propkey.h>
#include <iostream>

//

#include "../shared/stringconvert.hpp"
#include "exception.hpp"

//

namespace pw
{
    void jump_list::commit()
    {
        commit(pw::application::current());
    }

    void jump_list::commit(const pw::application &_application)
    {
        ICustomDestinationList* destinationList;

        if (FAILED(CoCreateInstance(CLSID_DestinationList, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&destinationList))))
        {
            throw pw::winapi_exception();
        }

        //

        IObjectArray* objectArray;
        UINT c_uMinObjectArraySlots;
        if (FAILED(destinationList->BeginList(&c_uMinObjectArraySlots, IID_PPV_ARGS(&objectArray))))
        {
            throw pw::winapi_exception();
        }

        //

        IObjectCollection* shellObjectCollection;
        if (FAILED(CoCreateInstance(CLSID_EnumerableObjectCollection, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&shellObjectCollection))))
        {
            throw pw::winapi_exception();
        }

        //

        for (pw::jump_task &jump_task : jump_tasks)
        {
            IShellLink* shellLink;

            if (FAILED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&shellLink))))
            {
                throw pw::winapi_exception();
            }

            shellLink->SetArguments(pw::stringconvert::widen(jump_task.arguments).c_str());
            shellLink->SetDescription(pw::stringconvert::widen(jump_task.description).c_str());
            shellLink->SetIconLocation(pw::stringconvert::widen(jump_task.icon_resource_path).c_str(), jump_task.icon_resource_index);
            shellLink->SetPath(pw::stringconvert::widen(jump_task.application_path).c_str());

            IPropertyStore* propertyStore;
            if (FAILED(shellLink->QueryInterface(&propertyStore)))
            {
                throw pw::winapi_exception();
            }

            PROPVARIANT propertyValue;
            InitPropVariantFromString(pw::stringconvert::widen(jump_task.title).c_str(), &propertyValue);
            propertyStore->SetValue(PKEY_Title, propertyValue);
            propertyStore->Commit();
            PropVariantClear(&propertyValue);
            propertyStore->Release();

            shellObjectCollection->AddObject(shellLink);
            shellLink->Release();
        }

        //

        // Add the specified user task to the Task category of a Jump List
        IObjectArray* userTask;
        if (FAILED(shellObjectCollection->QueryInterface(&userTask)))
        {
            throw pw::winapi_exception();
        }

        destinationList->AddUserTasks(userTask);
        userTask->Release();

        //

        shellObjectCollection->Release();
        if (FAILED(destinationList->CommitList()))
        {
            throw pw::winapi_exception();
        }
        destinationList->Release();
    }
}
