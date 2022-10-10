#pragma once
#include "DrawBibliothek.h"
#include "List.h"
#include "ThreeUpWindows.cpp"


struct Option
{
    Vector size = {};
    Rect rect = {};
    char name[MAX_PATH] = {};
    int* optionStatus = {};
    List* list = NULL;
};

struct Handle : Manager
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
    COLORREF onMouseColor = NULL;

    int lastKeyMessage = 0;

    Handle(AbstractAppData* _app, Rect _rect) :
        Manager(_app, _rect, 10, true, NULL, {}, _app->systemSettings->MenuColor),
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
    }

    void setOptionsRect();
    void drawOptions();
    void controlOptionClicking();
    int onWhichOptionIsMP();
    int optionOnClick(Vector mp);
    int getOptionNum(Vector mp);
    void clickIcon();

    virtual List* createMenuOption(const char* optionText, int* status, bool needToHideAfterClick = false);
    virtual bool addWindowToStart(Window* window);
    virtual bool addWindowToBack(Window* window);

    virtual void screenChanged() override;

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int onSize(Vector managerSize) override;
    virtual int onKeyboard(int key) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;

};