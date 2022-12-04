#pragma once
#include "DrawBibliothek.h"
#include "ProgrammeDate.h"
#include "WindowsLib.h"



struct ToolLay : Manager
{
    struct CLay* lay = NULL;
    Rect toolZone = {};
    Vector size = { 1, 1 };//rotates between[0; unlim)
    const char* name = NULL;
    struct Tool2* tool = NULL;
    char* toolsData = NULL;
    ProgrammeDate* data = NULL;
    int thickness = 1;

    bool needToShow = 1;
    

    //condition block
    bool isToolFinished = false;
    bool isEditing = false;


    ToolLay(AbstractAppData* _app);
    ~ToolLay();


    virtual void needRedraw();


    virtual bool useTool(ProgrammeDate* data);
    virtual void addTool(Tool2* _tool);
    HDC drawTool(HDC dc = NULL);
    void editTool(ProgrammeDate* data);
    virtual bool isInToolZone(ProgrammeDate* data, Vector mp);
    virtual char*& getToolsData();
    virtual ProgrammeDate* getProgDate();
    virtual int setProgDate(ProgrammeDate* data);
    virtual M_HDC* getPermanentDC();
    virtual M_HDC* getOutputDC();
    virtual void setShowMode(int mode);
    virtual int finishThisTool();


    virtual void draw() override;
    virtual int mbDown(Vector pos, int button) override;
    virtual int mbUp(Vector pos, int button) override;
    virtual int onMouseMove(Vector pos, Vector delta) override;

    virtual bool isFinished();
    virtual bool isStarted();
    virtual Tool2* getTool();

    
};