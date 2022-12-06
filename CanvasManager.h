#pragma once
#include "Canvas.h"

struct CanvasManager : Manager
{
    int activeCanvasNum = -1;
    bool addNewCanvas = false;
    int currentCanvasesLength = 0;
    Canvas* canvases[10] = {};
    Rect tabs[10] = {};
    Vector oneTabSize = {};
    Vector tabCrossSize = { 25, 25 };
    HDC tabCross = NULL;
    
    int intScale = 0;
    int minScale = 0;
    int maxScale = 1000;

    Vector scaleButtonSize = {};
    struct InputButton2* scaleButton = NULL;

    Vector plusMinusButtonSize = {};
    Rect plusButtonRect = {};
    Rect minusButtonRect = {};
    HDC plusButtonDC = NULL;
    HDC minusButtonDC = NULL;
    int lastTimeButtonClicked = 0;
    int deltaBetween2Clicks = 300;
    int lastTimeMBWasClicked = 0;
    struct ImportTool* importTool = NULL;

    struct SetCanvasButton* setCanvasButton = NULL;


    CanvasManager(AbstractAppData* _app, Vector _pos);
    virtual ~CanvasManager();

    virtual Canvas* getActiveCanvas();
    virtual int getActiveCanvasNum();
    virtual bool addCanvas(const char* name, Vector dcSize);
    virtual int openCreatingCanvasMenu();

    virtual int setDrawingMode(int num);

    Vector getCentrizedPos(Vector localSize, Vector globalSize);
    void drawTabs();
    void setTabsRect();
    int tabsOnClick();
    void controlActiveCanvas();
    void controlStretching();
    void controlPosition();
    void controlScaleButtons();
    void drawScaleButtons();
    void deleteCanvas(int num);
    int setActiveCanvas(int num);

    Window* getSetCanvasButton();


    virtual void screenChanged() override;

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
    virtual int onSize(Vector managerSize, Rect newRect) override;
    virtual int onKeyboard(int key) override;

    virtual void deleteButton() override;
};              