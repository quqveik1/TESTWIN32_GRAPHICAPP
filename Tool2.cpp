#pragma once
#include "Tool2.h"
#include "MainTools.h"
#include "WindowsLib.cpp"

ToolLay* Tool2::selectToolLay(ToolLay* toollay)
{
    ToolLay* previousToolLay = toollay;
    activeToolLay = toollay;
    return previousToolLay;
}
