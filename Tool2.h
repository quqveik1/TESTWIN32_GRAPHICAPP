#pragma once
#include "DrawBibliothek.h"
#include "MainTools.h"
#include "WindowsLib.h"


struct Tool2 : Window
{
    const char* name = NULL;
    int ToolSaveLen = 0;

    Tool2(AbstractAppData* _app, const char* _name) :
        Window(_app),
        name(_name)
    {
    }

    virtual int selectToolLay(ToolLay* toollay);

    virtual int createNewToolCopy(ToolLay* toollay);
    virtual int finishToolCopy(ToolLay* toollay);
};