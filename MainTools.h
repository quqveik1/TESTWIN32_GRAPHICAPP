#pragma once
#include "DrawBibliothek.h"
#include "Tool2.h"
struct CToolManager
{
    const int ToolsLength = 10;
    struct Tool2** tools = new Tool2* [ToolsLength];
    int currentLength = 0;


    virtual void addTool(struct Tool2* tool);
};


struct ToolLay
{
    struct CLay* lay = NULL;
    Rect toolZone = {};
    Vector size = { 1, 1 };//rotates between[0; unlim)
    const char* name = NULL;
    struct Tool2* tool = NULL;
    void* toolsData = NULL;
    int thickness = 1;
    

    //condition block
    bool isToolFinished = false;
    bool isEditing = false;


    virtual void needRedraw();


    //virtual bool useTool(ProgrammeDate* data);
    //HDC drawTool(HDC dc = NULL);
    //void editTool(ProgrammeDate* data);
    //virtual bool isInToolZone(ProgrammeDate* data, Vector mp, int mbCondition);
    virtual void* getToolsData() { return toolsData; };
    virtual HDC getPermanentDC();
    virtual HDC getOutputDC();

    virtual bool isFinished();
    virtual bool isStarted();
    virtual Tool2* getTool();
};