#pragma once
#include "AbstractApp.h"
#include "M_HGDIOBJ.h"
#include "M_HDC.h"
#include "AbstractApp.h"

struct HGDIManager
{
    AbstractAppData* app = NULL;

    int currlen = 0;
    static const int maxLen = 100000;
    M_HGDIOBJ* objs[maxLen] = {};
    bool isActive[maxLen] = {};

    HGDIManager(AbstractAppData* _app) :
        app (_app)
    {
    }
    ~HGDIManager();

    virtual M_HDC* getHDC();
    virtual M_HGDIOBJ* getHGDIOBJ();
}; ;