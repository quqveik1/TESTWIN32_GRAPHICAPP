#pragma once
#include "..\ToolExportData.h"

void DLLToolExportData::addTool(Tool* tool)
{ 

    if (currlen >= size)
    {
        printf("Мест для новых функция нет");
        return;
    }
    tools[currlen++] = tool;
}
