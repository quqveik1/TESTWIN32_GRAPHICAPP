#pragma once
#include "DLLToolExportData.h"

int DLLToolExportData::addTool(struct Tool2* tool)
{
    if (currlen < size)
    {
        tools[currlen++] = tool;
        return currlen;
    }

    printf("���������� �� ��������� � �������� ��������\n");
    return -1;

}