#pragma once
#include "DrawBibliothek.h"

struct Frame : Window
{
    HDC managerDC = NULL;

    Frame(AbstractAppData* _app, COLORREF color, HDC _managerDC) : 
        Window(_app, {}, color),
        managerDC (_managerDC)
    {
    }

    virtual void draw() override;
};
