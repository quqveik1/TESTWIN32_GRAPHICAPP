#pragma once 
#include "LoadLib.h"


HMODULE CLoadLib::loadLib(const char* path)
{
    HMODULE result = NULL;
    int libsAmount = libs.size();
    result = LoadLibrary(path);
    if (result)
    {
        libs.push_back(result);
    }
    return result;
}

CLoadLib::CLoadLib(size_t _defaultSize/* = 10*/) :
    defaultSize (_defaultSize)
{
    libs.reserve(defaultSize);
}

CLoadLib::~CLoadLib()
{
    for (int i = 0; i < libs.size(); i++)
    {
        if (libs[i])
        {
            int result = FreeLibrary(libs[i]);
            //int lastError = GetLastError();
            //printf("");
        }
    }
}