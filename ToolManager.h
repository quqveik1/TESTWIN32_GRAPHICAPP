#pragma once
#include "Tool.h"


struct CToolManager
{

    struct AbstractAppData* app = NULL;
    const int ToolsLength = 10;
    struct Tool** tools = new Tool* [ToolsLength] {};
    int currentLength = 0;
    int activeToolNum = 0;
    struct Tool** hidenTools = new Tool* [ToolsLength] {};  
    int currentHidenToolsLength = 0;
    


    virtual Tool* getActiveTool();
    virtual int getActiveToolNum();
    virtual int setActiveToolNum(int num);
    virtual int setActiveTool(Tool* tool);
    virtual int addTool(Tool* tool, bool needToHide = false);

    CToolManager(AbstractAppData* _app);
    ~CToolManager();
};