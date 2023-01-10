#pragma once

#include "Q_Vector.h"
#include "AbstractApp.h"
#include "WindowsLib.h"
struct Window;
struct Manager;


struct CWindowsLibApi
{
    virtual void resize(Window* window, Rect newRect);
    virtual void resize(Window* window, Vector newSize);
    virtual bool addWindow(Manager* manager, Window* window);
    virtual int separateWindow(Manager* manager, int pos);
    virtual int clickHandle(Manager* manager);
    virtual Vector getAbsCoordinats(Window* window, bool coordinatsWithHandle = false);
    virtual struct Window* isActiveWindowBelow(Manager* manager);
    virtual void controlHandle(Manager* manager);
    virtual void screenChanged(Manager* manager);

    virtual int standartManagerShow(struct Manager* manager);
    virtual int standartManagerHide(struct Manager* manager);

    virtual int standartWindowDraw(struct Window* window);
    virtual int standartManagerDraw(struct Manager* manager, Vector deltaFromStart = {});
    virtual int standartManagerHitTest(struct Manager* manager, Vector mp);
    virtual int standartManagerOnClick(struct Manager* manager, Vector mp);  
    virtual int standartManagerMbDown(struct Manager* manager, Vector mp, int button);
    virtual int standartManagerMbUp(struct Manager* manager, Vector mp, int button);
    virtual int standartManagerOnMouseMove(struct Manager* manager, Vector mp, Vector delta);
    virtual int standartManagerOnTimer(struct Manager* manager, UINT_PTR timerName);
    virtual int standartManagerOnSize(struct Manager* manager, Vector managerSize, Rect newRect = {});
    virtual int standartManagerOnKeyboard(struct Manager* manager, int key);
    virtual int standartManagerOnKeyboardChar(struct Manager* manager, int key);
    virtual int standartManagerOnClose(struct Manager* manager);
    virtual int standartManagerOnDestroy(struct Manager* manager);
};
