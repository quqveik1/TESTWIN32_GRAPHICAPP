#pragma once
#include "cstdio"

struct CFileSavings
{
    const int LEN = 10;
    char paths[10][MAX_PATH] = {};
    int currLen = 0;
   
    virtual void add(const char* path);
    virtual void deleteAllFiles();
};
