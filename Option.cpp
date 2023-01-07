#pragma once
#include "Option.h"

int Option::addSubOption(Option* _option)
{
    subOptions.push_back(_option);
    return 1;
}