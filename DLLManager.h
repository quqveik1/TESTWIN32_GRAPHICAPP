#pragma once
#include "wtypes.h"
#include "DrawBibliothek.h"
int findSymbol(const char* text, int size, char symbol);

struct DLLManager
{
    struct AbstractAppData* appData = NULL;

    const char* pathToDLLList = NULL;
    const int size = 2;
    int currLen = 0;
    HMODULE libs[10] = {};
    int currLoadWindowNum = 0;
    const char* fileExtension = NULL;

    DLLManager(AbstractAppData* _app, const char* _pathToDLLList = NULL) :
        pathToDLLList(_pathToDLLList),
        appData(_app)
    {
    }

    bool loadLibs ();

    virtual int getNumberOfLibs();

};
