#pragma once
#include "DCManager.h"

int DCManager::addDC(HDC dc)
{
    if (currLen + 1 < maxLen)
    {
        dcs[currLen] = dc;
        currLen++;
        return currLen - 1;
    }
    return -1;
}

DCManager::~DCManager()
{
    for (int i = 0; i < currLen; i++)
    {
        app->deleteDC(dcs[i]);
    }
}    

DCManager::DCManager(AbstractAppData* _app) :
    app(_app)
{
}