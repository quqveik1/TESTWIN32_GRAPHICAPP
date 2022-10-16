#pragma once
#include <Windows.h>

struct TimerManager
{
    static const int TimersLength = 1000;
    UINT_PTR timers[TimersLength] = {};
    int currLen = 0;

    virtual int isEmpty(UINT_PTR number);
    virtual UINT_PTR getNewTimerNum();
    virtual int regNum(UINT_PTR number);
    
};