#pragma once 
#include "LoadLib.h"


HMODULE CLoadLib::loadLib(const char* path)
{
    HMODULE result = NULL;
    if (currLibsLenght + 1 < maxLibsLenght)
    {
        libs[currLibsLenght] = LoadLibrary(path);
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