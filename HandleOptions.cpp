#pragma once

#include "HandleOptions.h"
#include "WindowHandle.cpp"
#include "OptionWindow.cpp"


void HandleOptions::setManagerHandle(struct ManagerHandle* _managerhandle)
{
    managerhandle = _managerhandle;
    manager = managerhandle;
}


int HandleOptions::addOption(Option* _option)
{
    OptionWindow* optionWindow = new OptionWindow(app, _option, {0, height});
    optionsLayout.addWindow(optionWindow);
    return mainOption.addSubOption(_option);
}