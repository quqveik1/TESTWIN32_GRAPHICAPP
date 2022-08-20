#pragma once
#include "AbstractApp.h"
#include "M_HGDIOBJ.h"
#include "M_HDC.h"
#include "DrawBibliothek.h"

struct HGDIManager
{
    AbstractAppData* app = NULL;

    int currlen = 0;
    const int maxLen = 10000;
    M_HGDIOBJ* objs[10000] = {};

    HGDIManager(AbstractAppData* _app) :
        app (_app)
    {
    }
    ~HGDIManager();

    virtual M_HDC* getHDC();
    virtual M_HGDIOBJ* getHGDIOBJ();
};