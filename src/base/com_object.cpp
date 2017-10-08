#include "com_object.hpp"

#include <Windows.h>

namespace pw
{
    com_object::com_object()
    {
        CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    }

    com_object::~com_object()
    {
        CoUninitialize();
    }
}
