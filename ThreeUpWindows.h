#pragma once
#include "WindowsLib.h"

struct CloseButton : Window
{
    COLORREF trueRed = RGB(180, 0, 0);

    CloseButton(AbstractAppData* _app) :
        Window(_app, {}, NULL, _app->loadManager->loadImage("CloseButton4.bmp"))
    {
    }

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
};

struct ResizeButton : Window
{
    Vector sizeLastTime;
    HDC nowIsFullScreen;
    HDC nowIsNotFullScreen; 

    COLORREF onMouseColor = NULL;


    ResizeButton(AbstractAppData* _app) :
        Window(_app),
        sizeLastTime(app->systemSettings->FullSizeOfScreen),
        nowIsFullScreen(app->loadManager->loadImage("FullScreenButton.bmp")),
        nowIsNotFullScreen(app->loadManager->loadImage("ResizeScreenButton.bmp")),
        onMouseColor (app->systemSettings->onMouseColor)
    {
    }

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
};



struct MinimizeWindow : Window
{
    COLORREF onMouseColor = NULL;

    MinimizeWindow(AbstractAppData* _app) :
        Window(_app, {}, NULL, _app->loadManager->loadImage("MinimizeWindowButton.bmp")),
        onMouseColor(app->systemSettings->onMouseColor)
    {}


    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
};


