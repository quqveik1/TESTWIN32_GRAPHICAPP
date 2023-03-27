#pragma once
#include "CustomRCoordinatSystemWindow.h"
#include "ColorfullCoordinatSystemWindow.cpp"


size_t CustomRCoordinatSystemWindow::addPoint(Vector point, COLORREF pointColor/* = NULL*/, int _r /*=0*/)
{
    size_t res = ColorfullCoordinatSystemWindow::addPoint(point, pointColor);

    if (_r == 0) _r = pointsR;
    pointsRArrMutex.lock();
    pointsRArr.push_back(_r);
    pointsRArrMutex.unlock();
    return res;
}


int CustomRCoordinatSystemWindow::setPointR(int pos, int _r /*=0*/)
{
    if (_r == 0) _r = pointsR;
    pointsRArrMutex.lock();
    size_t currPointsSize = pointsRArr.size();
    int fncRes = 0;
    if (currPointsSize > pos)
    {
        pointsRArr[pos] = _r;
        fncRes = 1;
    }
    pointsRArrMutex.unlock();

    return fncRes;
}


size_t CustomRCoordinatSystemWindow::clearSys()
{
    try
    {
        size_t _size = ColorfullCoordinatSystemWindow::clearSys();
        pointsRArrMutex.lock();
        if (pointsRArr.size() > 0) pointsRArr.clear();
        pointsRArrMutex.unlock();
        return _size;
    }
    catch (...)
    {
        cout << "Программа упала";
    }
    return 0;
}


void CustomRCoordinatSystemWindow::drawPoints()
{
    size_t vectorSize = points.size();
    M_HDC& _outDC = *getOutputDC();

    COLORREF currColor = NULL;
    app->setColor(currColor, _outDC);

    pointsMutex.lock();
    pointsColorArrMutex.lock();
    pointsRArrMutex.lock();
    for (int i = 0; i < vectorSize; i++)
    {
        COLORREF newColor = pointsColorArr[i];
        if (newColor != currColor)
        {
            app->setColor(newColor, _outDC);
            currColor = newColor;
        }
        Vector pixPos = fromCellToPix(points[i]);
        app->circle(pixPos, pointsRArr[i], _outDC);
    }
    pointsMutex.unlock();
    pointsColorArrMutex.unlock();
    pointsRArrMutex.unlock();
}