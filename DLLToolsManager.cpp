#pragma once
#include "DLLToolsManager.h"
#include "ToolManager.h"

void DLLToolsManager::addToManager(CToolManager* manager)
{
    if (appData->systemSettings->debugMode) printf("Инструменты начали добавляться в прожку\n");
    if (appData->systemSettings->debugMode) printf("currLen: %d\n", currLen);
    for (int i = 0; i < currLen; i++)
    {
        DLLToolExportData* (*initDll) (AbstractAppData * data) = (DLLToolExportData * (*) (AbstractAppData * data))GetProcAddress(libs[i], "initDLL");
        if (appData->systemSettings->debugMode) printf("Инструмент добавился в прожку\n");
        if (!initDll) assert(!"функция не загрузилась");
        DLLToolExportData* exportData = initDll(appData);
        assert(exportData);
        if (!exportData) return;
        for (int j = 0; j < exportData->currlen; j++)
        {
            assert(exportData->tools[j]);
            manager->addTool(exportData->tools[j]);
        }
    }
}
