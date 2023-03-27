#pragma once
#include "CoordinatSystemWindow.h"
#include <vector>


struct ColorfullCoordinatSystemWindow : CoordinatSystemWindow
{
    mutex pointsColorArrMutex;
    vector<COLORREF> pointsColorArr;

    ColorfullCoordinatSystemWindow(AbstractAppData* _app) :
        CoordinatSystemWindow(_app)
    {
    };


    virtual size_t clearSys() override;
    virtual size_t addPoint(Vector point, COLORREF _pointColor = NULL);
    virtual int setPointColor(Vector point, COLORREF newColor = NULL);
    virtual int setPointColor(int pos, COLORREF newColor = NULL);
    virtual void drawPoints() override;
};