#pragma once
#include "Option.h"
#include "List.cpp"

int Option::addSubOption(Option* _option)
{
    subOptions.push_back(_option);
    return 1;
}



void Option::toLists(struct List* _list)
{
    for (int i = 0; i < subOptions.size(); i++)
    {
        _list->addNewItem(subOptions[i]);
    }
}