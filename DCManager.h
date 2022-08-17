#pragma once
#include "Windows.h"
#include "AbstractApp.h"

struct DCManager
{
    AbstractAppData* app = NULL;

    const int maxLen = 10000;
    int currLen = 0;
    HDC dcs[10000] = {};

    virtual int addDC(HDC dc);

    DCManager(AbstractAppData* _app);
    ~DCManager();
};