#pragma once

#include "WindowHandle.h"

#include "Option.cpp"

struct HandleOptions : WindowHandle
{
    struct ManagerHandle* managerhandle = NULL;
    Option mainOption;

    HandleOptions(AbstractAppData* _app) :
        WindowHandle(_app)
    {

    }

    virtual void setManagerHandle(struct ManagerHandle* _managerhandle);
    virtual int addOption(Option* _option);
};
