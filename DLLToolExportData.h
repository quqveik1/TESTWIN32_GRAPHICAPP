#pragma once


#pragma once
#include "Tool2.h"

struct DLLToolExportData
{
    int size;
    int currlen = 0;
    int lastGuid = 0;
    struct Tool2** tools = NULL;

    DLLToolExportData(int _size) :
        size(_size),
        tools(new struct Tool2* [_size])
    {
    }

    int addTool(struct Tool2* tool);
};