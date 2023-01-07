#pragma once
#include "WindowsLib.h"
#include "Layout.h"

struct WindowHandle : Layout
{
    double height;


    WindowHandle(AbstractAppData* _app, double _height = 0) :
        Layout(_app),
        height (_height)
    {
    };
    virtual int onSize(Vector managerSize, Rect mewRect = {}) override;
};