#pragma once
#include "..\ToolExportData.h"

void DLLToolExportData::addTool(Tool2* tool)
{ 

    if (currlen >= size)
    {
        printf("Мест для новых функция нет");
        return;
    }
    tools[currlen++] = tool;
}
