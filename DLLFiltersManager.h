#pragma once
#include "DrawBibliothek.h"
#include "DLLFilters\DLLExportData.h"
#include "DLLManager.cpp"


struct DLLFiltersManager : DLLManager 
{
    CFilter* dllWindows[10] = {};

    DLLFiltersManager(AbstractAppData* _app, const char *_pathToDLLList = NULL) :
        DLLManager (_app, _pathToDLLList)
    { 
        fileExtension = "filter";
    }

    void addToManager(Manager* manager);

};
