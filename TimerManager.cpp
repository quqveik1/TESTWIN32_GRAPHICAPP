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
    scoped_lock lock1(timersMutex);
    if (isEmpty(number))
    {
        timers.push_back(number);
        currLen++;
        return currLen;
    }
    return 0;
}

UINT_PTR TimerManager::getNewTimerNum()
{
    for (;;)
    {
        UINT_PTR num = rand() %100000;
        if (regNum(num))
        {
            return num;
        }
    }
}

