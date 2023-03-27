#pragma once 
#include "ColorfullCoordinatSystemWindow.h"


size_t ColorfullCoordinatSystemWindow::addPoint(Vector point, COLORREF pointColor/* = NULL*/)
{
    size_t res = CoordinatSystemWindow::addPoint(point);

    if (pointColor == 0) pointColor = pointsColor;
    pointsColorArrMutex.lock();
    pointsColorArr.push_back(pointColor);
    pointsColorArrMutex.unlock();
    return res;
}

int ColorfullCoordinatSystemWindow::setPointColor(Vector point, COLORREF newColor/* = NULL*/)
{
    if (newColor == 0) newColor = pointsColor;
    pointsMutex.lock();
    pointsColorArrMutex.lock();
    //int pos = std::find(points.begin(), points.end(), point);  
    int findedPos = app->findElement<Vector>(points, point);
    if (findedPos >= 0)
    {
        pointsColorArr[findedPos] = newColor;
    }
    pointsMutex.unlock();
    pointsColorArrMutex.unlock();
    return newColor;
}

int ColorfullCoordinatSystemWindow::setPointColor(int pos, COLORREF newColor/* = NULL*/)
{
    if (newColor == 0) newColor = pointsColor;
    pointsColorArrMutex.lock();
    size_t currPointsSize = pointsColorArr.size();
    int fncRes = 0;
    if (currPointsSize > pos)
    {
        pointsColorArr[pos] = newColor;
        fncRes = 1;
    }
    pointsColorArrMutex.unlock();

    return fncRes;
}


size_t ColorfullCoordinatSystemWindow::clearSys()
{
    try
    {
        size_t _size = CoordinatSystemWindow::clearSys();
        pointsColorArrMutex.lock();
        if (pointsColorArr.size() > 0) pointsColorArr.clear();
        pointsColorArrMutex.unlock();
        return _size;
    }
    catch (...)
    {
        cout << "Программа упала";
    }
    return 0;
}


void ColorfullCoordinatSystemWindow::drawPoints()
{
    size_t vectorSize = points.size();
    M_HDC& _outDC = *getOutputDC();
    
    COLORREF currColor = NULL;
    app->setColor(currColor, _outDC);

    Vector halfSize = { (double)pointsR, (double)pointsR };

    pointsMutex.lock();
    pointsColorArrMutex.lock();
    for (int i = 0; i < vectorSize; i++)
    {
        COLORREF newColor = pointsColorArr[i];
        if (newColor != currColor)
        {
            app->setColor(newColor, _outDC);
            currColor = newColor;
        }
        Vector pixPos = fromCellToPix(points[i]);
        app->ellipse(pixPos, halfSize, _outDC);
    }
    pointsMutex.unlock();
    pointsColorArrMutex.unlock();
}
