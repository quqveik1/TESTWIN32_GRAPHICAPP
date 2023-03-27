#pragma once
#include <Windows.h>
#include <vector>
#include <mutex>
using namespace std;

struct TimerManager
{
    static const int TimersLength = 10;
    mutex timersMutex;
    vector<UINT_PTR> timers;
    int currLen = 0;

    virtual int isEmpty(UINT_PTR number);
    virtual UINT_PTR getNewTimerNum();
    virtual int regNum(UINT_PTR number); 
};