#pragma once
#include <Windows.h>

struct CLoadLib
{
    vector<HMODULE> libs;
    size_t defaultSize;

    virtual HMODULE loadLib(const char* path);

    CLoadLib(size_t _defaultSize = 10);
    ~CLoadLib();

};