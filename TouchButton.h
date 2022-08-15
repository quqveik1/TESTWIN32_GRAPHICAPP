#pragma once
#include "DrawBibliothek.h"

struct TouchButton : Window
{
    bool* flag = NULL;

    TouchButton(AbstractAppData* _app, Rect _rect, HDC _dc, bool* _flag = NULL) :
        Window(_app, _rect, _app->systemSettings->MenuColor, _dc),
        flag(_flag)
    {
    }

    virtual void onClick(Vector mp) override;
};