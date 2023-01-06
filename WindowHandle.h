#pragma once
#pragma once
#include "Window.h"
#include "AbstractApp.h"

struct WindowHandle : Window
{
    double height;
    WindowHandle(AbstractAppData* _app, double _height = 0) :
        Window(_app), 
        height (_height)
    {
    };
    virtual int onSize(Vector managerSize, Rect mewRect = {}) override;
    virtual void print(M_HDC& _dc) override;
};