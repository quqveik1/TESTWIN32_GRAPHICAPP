#pragma once

#include "List.h"
#include "ThreeUpWindows.cpp"
#include "HandleOptions.cpp"




struct Handle : HandleOptions
{
    int addToBackElemetsPos[10] = {};
    int numberOfAddToBackElements = 0;
    bool wasCommonHandlePlaceClicked = false;
    Vector lastTimeMousePos = {};
    bool wasInFullScreenLastTime = true;
    Vector oneItemInMenuSize = {};
    Vector oneItemInBackMenuSize = {};

    HDC logo = NULL;
    Vector logoSize = { 25, 25 };
    Rect logoRect = { .pos = {}, .finishPos = logoSize };

    Option options[4] = {};
    double optionHeight = 0;
    const int maxOptionsLength = 4;
    int currentOptionsLength = 0;
    int deltaBetweenOptions = 5;
    int deltaBetweenFrameOfOption = 6;
    Vector logoStart = { (double)deltaBetweenOptions, 0};
    double startOfOptions = logoStart.x + logoSize.x + deltaBetweenOptions;
    int activeOptionNum = -1;
    int coloredOptionNum = -1;
    COLORREF onMouseColor = NULL;
    
    int isDragging = 0;
    Vector lastTimeAbsMousePos = {};

    int lastKeyMessage = 0;

    Handle(AbstractAppData* _app) :
        HandleOptions(_app, _app->systemSettings->HANDLEHEIGHT),
        onMouseColor(app->systemSettings->onMouseColor),
        logo(app->loadManager->loadImage("ImredLogo.bmp"))
    {
        wasInFullScreenLastTime = app->isFullScreen();
        oneItemInMenuSize = { app->systemSettings->BUTTONWIDTH * 3, getSize().y};
        oneItemInBackMenuSize = { app->systemSettings->BUTTONWIDTH, getSize().y};
        optionHeight = getSize().y - 4;
        font = std::lround (optionHeight) - 2;

        CloseButton* closeButton = new CloseButton(appData);
        addWindowToBack(closeButton);

        ResizeButton* resizeButton = new ResizeButton(appData);
        addWindowToBack(resizeButton);

        MinimizeWindow* minimizeButton = new MinimizeWindow(appData);
        addWindowToBack(minimizeButton);

        optionsLayout.MoveWindowTo({ (double)startOfOptions, 0 });
    }

    void setOptionsRect();
    void drawOptions();
    void controlOptionClicking();
    int onWhichOptionIsMP();
    int optionOnClick(Vector mp);
    int getOptionNum(Vector mp);
    void clickIcon();
    int isOnOptionsDown();

    void setActiveOptionNum(int num) { activeOptionNum = num; invalidateButton(); };

    virtual List* createMenuOption(const char* optionText, int* status, bool needToHideAfterClick = false);
    virtual bool addWindowToStart(Window* window);
    virtual bool addWindowToBack(Window* window);

    virtual void screenChanged() override;

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onSize(Vector managerSize, Rect newRect) override;
    virtual int onKeyboard(int key) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;

};