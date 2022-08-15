#pragma once
#include "TXLib.cpp"

struct CLoadLib
{
    HMODULE libs[10] = {};
    int currLibsLenght = 0;
    int maxLibsLenght = 10;

    virtual HMODULE loadLib(const char* path);


    ~CLoadLib();

};