#pragma once
#include "DrawBibliothek.h"
#include "SystemSettings.h"
#include "ZoneSizeControl.h"

struct MainManager : Manager
{
    Vector mousePos = {};
    int clicked = 0;
    Window* activeWindow = 0;
    Vector screenSizeLastTime = {};
    ZoneSizeControl zoneSizeControl;
    Vector minimumAppSize = {};
    Rect zone = {};
    bool needFrameToWork = false;
    Manager* handle = NULL;


    MainManager(AbstractAppData* _app, Rect _rect, int _length, Manager* _handle) :
        Manager(_app, _rect, _length, true, NULL, {}, TX_WHITE),
        minimumAppSize({app->systemSettings->BUTTONWIDTH * 6, app->systemSettings->HANDLEHEIGHT * 3 }),
        zoneSizeControl ((Manager*)this, &zone, &needFrameToWork, &minimumAppSize),
        handle (_handle)
    {
    }


    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int onSize(Vector managerSize) override;

    void controlWorkSpace();

    virtual void screenChanged() override;

    virtual int getMBCondition() override { return clicked; };

    virtual Vector getMousePos() override { return mousePos; }
    
    virtual Window* getActiveWindow() override { return activeWindow; };

    virtual void setActiveWindow(Window* window) override { activeWindow = window; };
};