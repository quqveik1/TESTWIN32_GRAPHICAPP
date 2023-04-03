#pragma once
#include "CustomRCoordinatSystemWindow.cpp"
#include "MultiLayCoordinatSystemWindow.h"


MultiLayCoordinatSystemWindow::MultiLayCoordinatSystemWindow(AbstractAppData* _app) :
    CustomRCoordinatSystemWindow(_app)
{
    addLay();
};


size_t MultiLayCoordinatSystemWindow::addLay()
{
    scoped_lock lock1(laysMutex);
    lays.push_back(new CoordinatLay());
    size_t newElementPos = lays.size() - 1;

    return newElementPos;
}

size_t MultiLayCoordinatSystemWindow::getActiveLayIndex()
{
    return activeLayIndex;
}

size_t MultiLayCoordinatSystemWindow::setActiveLayIndex(size_t index)
{
    activeLayIndex = index;
    return 0;
}


size_t MultiLayCoordinatSystemWindow::addPoint(Vector point, COLORREF _pointColor/* = NULL*/, int _r/* = 0*/, size_t layIndex/* = 0*/, bool _needToUpdateWindow/* = true*/)
{
    scoped_lock locklay(laysMutex);
    size_t _size = lays.size();
    if (layIndex < _size)
    {
        CoordinatLay* _activeLay = lays[layIndex];
        if (_pointColor == 0)_pointColor = pointsColor;
        if (_r == 0) _r = pointsR;
        _activeLay->addPoint(point, _pointColor, _r);
    }

    if (_needToUpdateWindow) invalidateButton();
    return 0;
}

size_t MultiLayCoordinatSystemWindow::CoordinatLay::addPoint(Vector pos, COLORREF color, int r)
{
    pointsLay.push_back(pos);
    colorLay.push_back(color);
    rLay.push_back(r);
    return pointsLay.size();
}

size_t MultiLayCoordinatSystemWindow::CoordinatLay::clear() 
{
    pointsLay.clear();
    colorLay.clear(); 
    rLay.clear(); 
    return pointsLay.size();
}

void MultiLayCoordinatSystemWindow::drawPoints()
{
    M_HDC& _outDC = *getOutputDC();

    COLORREF currColor = NULL;
    app->setColor(currColor, _outDC);
    
    laysMutex.lock();
    size_t laysSize = lays.size();
    for (size_t i = 0; i < laysSize; i++)
    {
        CoordinatLay& _activeLay = *lays[i];
        size_t _activeLaySize = _activeLay.size();

        for (int i = 0; i < _activeLaySize; i++)
        {
            COLORREF newColor = _activeLay.colorLay[i];
            if (newColor != currColor)
            {
                app->setColor(newColor, _outDC);
                currColor = newColor;
            }
            Vector pixPos = fromCellToPix(_activeLay.pointsLay[i]);
            app->circle(pixPos, _activeLay.rLay[i], _outDC);
        }

    }
    laysMutex.unlock();
    
}

size_t MultiLayCoordinatSystemWindow::clearSys()
{
    scoped_lock laysLock(laysMutex);
    size_t laysSize = lays.size();
    for (size_t i = 0; i < laysSize; i++)
    {
        CoordinatLay& _activeLay = *lays[i];
        _activeLay.clear();
    }
    return laysSize;
}

size_t MultiLayCoordinatSystemWindow::clearLay(size_t layIndex)
{
    scoped_lock laysLock(laysMutex);
    size_t laysSize = lays.size();
    if (layIndex < laysSize)
    {
        size_t res = lays[layIndex]->clear();
        return res;
    }
    else
    {
        assert(layIndex < laysSize);
    }
    return 0;
}