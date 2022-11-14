#pragma once
#include "Tool2.h"


struct CToolManager
{

    struct AbstractAppData* app = NULL;
    const int ToolsLength = 10;
    struct Tool2** tools = new Tool2* [ToolsLength] {};
    int currentLength = 0;
    int activeToolNum = 0;
    struct Tool2** hidenTools = new Tool2 * [ToolsLength] {};
    int currentHidenToolsLength = 0;
    


    virtual Tool2* getActiveTool();
    virtual int getActiveToolNum();
    virtual int setActiveToolNum(int num);
    virtual int setActiveTool(Tool2* tool);
    virtual int addTool(Tool2* tool, bool needToHide = false);

    CToolManager(AbstractAppData* _app);
    ~CToolManager();
};