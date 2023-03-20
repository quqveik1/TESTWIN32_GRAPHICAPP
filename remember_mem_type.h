#pragma once
#include "MEM_TYPE.h"

struct remember_mem_type
{
    MEM_TYPE memType = MT_STATIC;
};

template <typename T>
struct Deleter_remember_mem_type
{
    void operator()(remember_mem_type* ptr) const
    {
        if (ptr)
        {
            if (ptr->memType == MT_DYNAMIC)
            {
                T* fullPointer = (T*)ptr;

                delete fullPointer;
            }
        }
    }
};


