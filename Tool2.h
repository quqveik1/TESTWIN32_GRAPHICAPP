#pragma once
#include "DrawBibliothek.h"
#include "MainTools.h"
#include "WindowsLib.h"


struct Tool2 : Window
{
    const char* name = NULL;
    int ToolSaveLen = 0;
    ToolLay* activeToolLay = NULL;

    Tool2(AbstractAppData* _app, const char* _name) :
        Window(_app),
        name(_name)
    {
    }

    virtual ToolLay* selectToolLay(ToolLay* toollay);

    virtual int createNewToolCopy(ToolLay* toollay) = NULL;
    virtual int deleteToolCopy(ToolLay* toollay) = NULL;
    virtual int finishToolCopy(ToolLay* toollay) = NULL;
};