#pragma once
#include "LayoutInfo.h"
#include "Q_Rect.h"

struct LinearLayoutInfo : LayoutInfo
{
    //pos - startMargin finishPos - finishMargin
    Rect margin = {};
};