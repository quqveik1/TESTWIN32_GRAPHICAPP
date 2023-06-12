#pragma once
#include "AbstractApp.h"
#include "WindowsLib.h"
#include "ConsoleOutput.cpp"


struct Tool2 : Window
{
    const char* name = NULL;
    int ToolSaveLen = 0;
    struct ToolLay* activeToolLay = NULL;

    Tool2(AbstractAppData* _app, const char* _name) :
        Window(_app),
        name(_name)
    {
    }
    
    virtual ~Tool2()
    {
        dprintf("%s", __FUNCTION__);
    }

    virtual struct ToolLay* selectToolLay(struct ToolLay* toollay);

    virtual int createNewToolCopy(struct ToolLay* toollay) = 0;
    virtual int deleteToolCopy(struct ToolLay* toollay)  = 0;
    virtual int finishToolCopy(struct ToolLay* toollay)  = 0;
};