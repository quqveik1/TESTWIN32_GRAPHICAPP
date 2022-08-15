#pragma once
#include "DLLFiltersManager.h"
#include<io.h>








void DLLFiltersManager::addToManager(Manager* manager)
{

    if (appData->systemSettings->debugMode) printf("Инструменты начали добавляться в прожку\n");
    if (appData->systemSettings->debugMode) printf("currLen: %d\n", currLen);
    for (int i = 0; i < currLen; i++)
    {
        DLLExportData* (*initDll) (AbstractAppData * data) = (DLLExportData * (*) (AbstractAppData * data))GetProcAddress(libs[i], "initDLL");
        if (appData->systemSettings->debugMode) printf("Инструмент добавился в прожку\n");
        if (!initDll) assert(!"функция не загрузилась");
        DLLExportData* exportData = initDll(appData);

        for (int j = 0; j < exportData->currlen; j++)
        {
            assert(exportData->filters[j]);
            dllWindows[currLoadWindowNum] = exportData->filters[j];
            manager->addWindow(exportData->filters[j]);
            currLoadWindowNum++;
        }
    }
}
