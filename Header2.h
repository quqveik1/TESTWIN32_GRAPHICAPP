#pragma once
#include "TXLib.cpp"

struct CLoadLib
{
    HMODULE libs[10] = {};

    virtual HMODULE loadLib(const char* path);

}