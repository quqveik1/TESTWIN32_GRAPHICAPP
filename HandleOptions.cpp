#pragma once

#include "HandleOptions.h"
#include "WindowHandle.cpp"


void HandleOptions::setManagerHandle(struct ManagerHandle* _managerhandle)
{
    managerhandle = _managerhandle;
    manager = managerhandle;
}


int HandleOptions::addOption(Option* _option)
{
    return mainOption.addSubOption(_option);
}