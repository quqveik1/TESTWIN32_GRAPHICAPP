#pragma once
#include "MEM_TYPE.h"
#include "remember_mem_type.cpp"
#include <iostream>

struct LayoutInfo : remember_mem_type
{
    virtual ~LayoutInfo() {};
};

void fncDeleter(struct LayoutInfo* ptr)
{
    if (ptr)
    {
        if (ptr->memType == MT_DYNAMIC)
        {
            delete ptr;
        }
    }

}