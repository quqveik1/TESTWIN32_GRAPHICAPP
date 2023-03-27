#pragma once
#include "ColorfullCoordinatSystemWindow.h"


struct CustomRCoordinatSystemWindow : ColorfullCoordinatSystemWindow
{
    mutex pointsRArrMutex;
    vector<int> pointsRArr;

    CustomRCoordinatSystemWindow(AbstractAppData* _app) :
        ColorfullCoordinatSystemWindow(_app)
    {
    };


    virtual size_t clearSys() override;
    virtual size_t addPoint(Vector point, COLORREF _pointColor = NULL, int _r = 0);
    virtual int setPointR(int pos, int _r = 0);
    virtual void drawPoints() override;
};
