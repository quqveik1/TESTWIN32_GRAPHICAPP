#pragma once
#include "AbstractAppData.h"
#include "M_HGDIOBJ.h"
#include "M_HDC.h"

struct HGDIManager
{
    M_HGDIOBJ* objs[10000] = {};

    virtual M_HDC* getHDC();
    virtual M_HGDIOBJ* getHGDIOBJ();
};