#pragma once
#include "WindowsLib.h"
#include "Option.cpp"

struct OptionWindow : OpenManager
{
    Option* option;
    int deltaBetweemFrameAndOption = 5;

    OptionWindow(AbstractAppData* _app, Option* _option, Vector _size) :
        OpenManager(_app, _size),
        option(_option)
    {
        if(option)text = option->name;
        setOpeningManager((Manager*)_option->reciever);
    }

    virtual int onSize(Vector managerSize, Rect _newRect = {}) override;
};