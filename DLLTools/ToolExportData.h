#pragma once
#include "Tool.h"

struct DLLToolExportData
{
    int size;
    int currlen = 0;
    int lastGuid = 0;
    struct Tool** tools = NULL;

    DLLToolExportData(int _size) :
        size(_size),
        tools(new Tool*[_size])
    {
    }

    virtual void addTool(Tool *tool);
};