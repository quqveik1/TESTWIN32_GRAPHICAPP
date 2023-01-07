#pragma once
#include "WindowsLib.h"
                             

struct Layout : Manager
{
    Layout(AbstractAppData* _app, Rect _rect = {}) :
        Manager(_app, _rect)
    {
    }

    virtual void print(M_HDC& finalDC) override;
};