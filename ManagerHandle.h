#pragma once

#include "WindowsLibApi.cpp"
#include "WindowHandle.h"
#include "MainWindow.cpp"

struct ManagerHandle : MainWindow
{
    struct WindowHandle* handle;

    ManagerHandle(AbstractAppData* _app, WindowHandle* _handle = NULL) :
        MainWindow(_app),
        handle(_handle)
    {
        setHandle(_handle);
    }

    virtual void setHandle(WindowHandle* _handle) { handle = _handle; handle->manager = this; };
    virtual void setHandleHeight(int height);
    virtual void createHandle() {};

    virtual void draw() override;
    virtual int hitTest(Vector mp) override;
    virtual void onClick(Vector mp) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;  
    virtual int onSize(Vector managerSize, Rect newRect = {}) override;
};