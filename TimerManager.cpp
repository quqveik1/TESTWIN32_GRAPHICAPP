#pragma once
#include "TimerManager.h"



int TimerManager::isEmpty(UINT_PTR number)
{
    for (int i = 0; i < currLen; i++)
    {
        if (timers[i] == number)
        {
            return false;
        }
    }
    return 1;
}

int TimerManager::regNum(UINT_PTR number)
{
    if (isEmpty(number))
    {
        if (currLen < TimersLength)
        {
            timers[currLen] = number;
            currLen++;
            return currLen;
        }
    }
    return 0;
}

UINT_PTR TimerManager::getNewTimerNum()
{
    for (;;)
    {
        UINT_PTR num = rand();
        if (regNum(num))
        {
            return num;
        }
    }
}