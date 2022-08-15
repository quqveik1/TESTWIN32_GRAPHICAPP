#pragma once
#include "DrawBibliothek.h"
#include "ProgrammeDate.h"



struct ToolLay
{
    CLay* lay = NULL;
    Rect toolZone = {};
    Vector size = { 1, 1 };//rotates between[0; unlim)
    const char* name = NULL;
    struct Tool* tool = NULL;
    char* toolsData = NULL;
    ProgrammeDate* data = NULL;
    int thickness = 1;

    bool needToShow = 1;
    

    //condition block
    bool isToolFinished = false;
    bool isEditing = false;


    virtual void needRedraw();


    virtual bool useTool(ProgrammeDate* data);
    virtual void addTool(Tool* _tool);
    HDC drawTool(HDC dc = NULL);
    void editTool(ProgrammeDate* data);
    virtual bool isInToolZone(ProgrammeDate* data, Vector mp);
    virtual char*& getToolsData();
    virtual ProgrammeDate* getProgDate();
    virtual int setProgDate(ProgrammeDate* data);
    virtual HDC getPermanentDC();
    virtual HDC getOutputDC();
    virtual void setShowMode(int mode);

    virtual bool isFinished();
    virtual bool isStarted();
    virtual Tool* getTool();

    ~ToolLay();
};