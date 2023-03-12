#pragma once 
#include "LoadLib.h"


HMODULE CLoadLib::loadLib(const char* path)
{
    HMODULE result = NULL;
    string fullPath = "";
    if (appData)
    {
        if (!appData->pathToAbstractAppDataApi.empty())
        {
            fullPath += appData->pathToAbstractAppDataApi + "\\";
        }
    }
    else
    {
        assert(!"Õ≈“ ” ¿«¿“≈Àﬂ Õ¿ √À¿¬Õ€…  À¿—— œ–»ÀŒ∆≈Õ»ﬂ");
    }
    fullPath += path;
    if (currLibsLenght + 1 < maxLibsLenght)
    {
        libs[currLibsLenght] = LoadLibrary(fullPath.c_str());
        result = libs[currLibsLenght];
        currLibsLenght++;
    }
    return result;
}

CLoadLib::~CLoadLib()
{
    for (int i = 0; i < currLibsLenght; i++)
    {
        if (libs[i])
        {
            //int result = FreeLibrary(libs[i]);
            //int lastError = GetLastError();
            //printf("");
        }
    }
}