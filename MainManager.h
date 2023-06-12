#pragma once
#include "AbstractApp.h"
#include "SystemSettings.h"
#include "ZoneSizeControl.h"
#include "ManagerHandle.h"

struct MainManager : ManagerHandle
{
    Vector mousePos = {};
    int clicked = 0;
    Window* activeWindow = 0;
    Vector screenSizeLastTime = {};
    ZoneSizeControl zoneSizeControl;
    Vector minimumAppSize = {};
    Rect zone = {};
    bool needFrameToWork = false;


    MainManager(AbstractAppData* _app, Rect _rect, int _length, WindowHandle* _handle) :
        ManagerHandle(_app, _handle),
        minimumAppSize({app->systemSettings->BUTTONWIDTH * 6, app->systemSettings->HANDLEHEIGHT * 3 }),
        zoneSizeControl ((Manager*)this, &zone, &needFrameToWork, &minimumAppSize)
    {
        resize(_rect);
    }


    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onSize(Vector managerSize, Rect newRect) override;

    void controlWorkSpace();

    virtual int getMBCondition() override { return clicked; };

    virtual Vector getMousePos() override { return mousePos; };
    
    virtual Window* getActiveWindow() override { return activeWindow; };

    virtual void setActiveWindow(Window* window) override { activeWindow = window; };
};