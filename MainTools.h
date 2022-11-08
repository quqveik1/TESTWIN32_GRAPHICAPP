#pragma once
#include "DrawBibliothek.h"
struct CToolManager
{
    const int ToolsLength = 10;
    struct Tool** tools = new Tool* [ToolsLength];
    int currentLength = 0;


    virtual void addTool(Tool* tool);
};


struct ToolLay
{
    CLay* lay = NULL;
    Rect toolZone = {};
    Vector size = { 1, 1 };//rotates between[0; unlim)
    const char* name = NULL;
    struct Tool* tool = NULL;
    void* toolsData = NULL;
    int thickness = 1;
    

    //condition block
    bool isToolFinished = false;
    bool isEditing = false;


    virtual void needRedraw();


    virtual bool useTool(ProgrammeDate* data);
    HDC drawTool(HDC dc = NULL);
    void editTool(ProgrammeDate* data);
    virtual bool isInToolZone(ProgrammeDate* data, Vector mp, int mbCondition);
    virtual void* getToolsData() { return toolsData; };
    virtual HDC getPermanentDC();
    virtual HDC getOutputDC();

    virtual bool isFinished();
    virtual bool isStarted();
    virtual Tool* getTool();
};