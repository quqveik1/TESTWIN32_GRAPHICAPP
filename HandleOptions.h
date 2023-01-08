#pragma once


#include "WindowHandle.h"
#include "Option.cpp"
#include "LinearLayout.cpp"
#include "OptionWindow.h"
#include "List.h"


struct HandleOptions : WindowHandle
{
    struct ManagerHandle* managerhandle = NULL;
    Option mainOption;
    LinearLayout optionsLayout;
    vector<List*> optionsList;
    vector<OptionWindow*> optionsWindow;

    HandleOptions(AbstractAppData* _app, double _height) :
        WindowHandle(_app, _height),
        optionsLayout(_app, {}, LinearLayout::FLAG_HORIZONTAL)
    {
        addWindow(optionsLayout);
    }

    virtual void setManagerHandle(struct ManagerHandle* _managerhandle);
    virtual int addOption(Option* _option);

    
    virtual int onSize(Vector managerSize, Rect newRect = {}) override;
};
