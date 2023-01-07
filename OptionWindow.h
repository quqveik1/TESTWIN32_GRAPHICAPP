#pragma once
#include "WindowsLib.h"
#include "Option.cpp"

struct OptionWindow : Window
{
    Option* option;
    Vector size = {};
    int deltaBetweemFrameAndOption = 5;

    OptionWindow(AbstractAppData* _app, Option* _option, Vector _size) :
        Window(_app),
        size(_size),
        option(_option)
    {
        if(option)text = option->name;
    }

    virtual int onSize(Vector managerSize, Rect _newRect = {}) override;
    virtual void onClick(Vector mp) override;
};