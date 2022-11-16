#pragma once
#include "DrawBibliothek.h"
#include "Lay.h"

struct CLay
{
    AbstractAppData* app = NULL;

    struct Canvas* canvas = NULL;

    //Lay lay = {};
    M_HDC lay; 
    int toolLength = 0;
    int activeToolNum = -1;
    bool isNewToolLayCreated = false;
    bool needToRedraw = false;
    int oneLayToolLimit = NULL;
    int DrawingModeLastTime = -1;

    struct PragrammeDate* data = NULL;
    struct ToolLay** toolLays = NULL;


    virtual void createLay(AbstractAppData* _app, struct Canvas* _canvas, Vector _size = {});
    virtual ToolLay* createToolLay();
    virtual void addToolLay (ToolLay* tool);
    virtual void setActiveLastToolLay();

    virtual M_HDC getOutputDC ();
    virtual RGBQUAD* getOutputBuf();
    virtual M_HDC getPermanentDC();
    virtual RGBQUAD* getPermanentBuf();


    virtual ToolLay* getActiveToolLay();
    virtual ToolLay* getToolLay(int num);
    virtual int getCurrentSize();
    virtual int getActiveToolLayNum();
    virtual void setActiveToolLayNum(int num);
    virtual ToolLay** getToolLays();
    Lay* getLay();
    virtual Vector getLaySize();

    virtual void needRedraw();
    virtual void noMoreRedraw();
    virtual bool redrawStatus();
    virtual void redraw();
    virtual void editTool(ProgrammeDate* data);
    virtual void controlTool(ProgrammeDate* data);

    ~CLay();
};