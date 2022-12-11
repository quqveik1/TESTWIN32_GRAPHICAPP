#pragma once
#include "WindowsLib.cpp"

struct WindowHandle : Window
{
    WindowHandle(AbstractAppData* _app) :
        Window(AbstractAppData* _app)
    {
    };
};