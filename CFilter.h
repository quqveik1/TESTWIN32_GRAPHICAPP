#pragma once
#include "DrawBibliothek.h"

struct CFilter : Manager
{
    int guid = 0;
    const char* name = NULL;

    CFilter(AbstractAppData* _app, Rect _rect, int _length, bool _advancedMode = true, HDC _dc = NULL, Rect _handle = {}) :
        Manager(_app, _rect, _length, _advancedMode, _dc, _handle)
    {
    }

    virtual void apply() = 0;
};