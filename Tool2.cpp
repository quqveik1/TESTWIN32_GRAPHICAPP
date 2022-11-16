#pragma once
#include "Tool2.h"

ToolLay* Tool2::selectToolLay(ToolLay* toollay)
{
    ToolLay* previousToolLay = toollay;
    activeToolLay = toollay;
    return previousToolLay;
}
