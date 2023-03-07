#pragma once
#include "WindowsLib.h" 
#include "Layout.h"
#include "LinearLayoutInfo.h"

struct LinearLayout : Layout
{
    const static int FLAG_VERTICAL = 0;
    const static int FLAG_HORIZONTAL = 1;
    int flags = 0;
    int deltaBetweenButtons = 0;

    LinearLayout(AbstractAppData* _app, Vector _startPos, int flag = 0) :
        Layout(_app, { .pos = _startPos, .finishPos = {}}),
        flags(flag)
    {
    }

    virtual int onSize(Vector managerSize, Rect newRect = {}) override; 
    virtual void onClick(Vector mp) override;
    virtual Rect calcRect();
    void setDeltaBetweenButttons(int _deltaBetweenButtons) { deltaBetweenButtons = _deltaBetweenButtons; };
};
