#pragma once
#include "..\ToolExportData.h"

void DLLToolExportData::addTool(Tool2* tool)
{ 

    if (currlen >= size)
    {
        printf("���� ��� ����� ������� ���");
        return;
    }
    tools[currlen++] = tool;
}
