#pragma once
#include "Windows.h"

struct M_HGDIOBJ
{
    HGDIOBJ obj = NULL;
    struct HGDIManager* gdiManager = NULL;
    int pNumber = -1;
    struct M_HDC* motherHDC = NULL;
    int status = 0; //1 - active  // 2+ selected
    const char* name = NULL;

    virtual int deleteObj();
    virtual HGDIOBJ setObj(HGDIOBJ  _obj);
};