#pragma once
#include "DLLManager.cpp"
#include "DLLToolExportData.h"


struct DLLToolsManager : DLLManager
{
    DLLToolsManager(EngineAppApi* _appData, const char* _pathToDLLList = NULL) :
        DLLManager (_appData, _pathToDLLList)
    {
        fileExtension = "tool";
    }
    void addToManager(CToolManager* manager);
};