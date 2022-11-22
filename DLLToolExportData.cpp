#pragma once
#include "DLLToolExportData.h"

int DLLToolExportData::addTool(struct Tool2* tool)
{
    if (currlen < size)
    {
        tools[currlen++] = tool;
        return currlen;
    }

    printf("Инструмент не добавился в менеджер загрузки\n");
    return -1;

}