#pragma once
#include "..\ToolExportData.h"

void DLLToolExportData::addTool(Tool* tool)
{ 

    if (currlen >= size)
    {
        printf("���� ��� ����� ������� ���");
        return;
    }
    tools[currlen++] = tool;
}
