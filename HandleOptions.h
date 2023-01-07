#pragma once


#include "WindowHandle.h"
#include "Option.cpp"
#include "LinearLayout.cpp"


struct HandleOptions : WindowHandle
{
    struct ManagerHandle* managerhandle = NULL;
    Option mainOption;

    HandleOptions(AbstractAppData* _app, double _height) :
        WindowHandle(_app, _height)
    {

    }

    virtual void setManagerHandle(struct ManagerHandle* _managerhandle);
    virtual int addOption(Option* _option);


};
