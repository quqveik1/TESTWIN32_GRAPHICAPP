#pragma once
#include "CoordinatSystemWindow.h"

void CoordinatSystemWindow::setCCells(Vector _cScreenCells)
{
    cCells = _cScreenCells;
    invalidateButton();
}

Vector CoordinatSystemWindow::getDensity()
{
    Vector _currSize = getSize();

    Vector density = _currSize / cCells;
    return density;
}

Vector CoordinatSystemWindow::getPixNullCoordinats()
{
    Vector ans = {};
    Vector currSize = getSize();
    ans.x = currSize.x * pixNullPercantage.x;
    ans.y = currSize.y * (1 - pixNullPercantage.y);
    return ans;
}

Vector CoordinatSystemWindow::getHumanCellStep()
{
    Vector cellStep = {};
    cellStep.x = humanRound(cCells.x / cCellsLines.x);
    cellStep.y = humanRound(cCells.y / cCellsLines.y);
    return cellStep;
}

Vector CoordinatSystemWindow::getPixCellStep()
{
    Vector pixCellStep = getHumanCellStep() * getDensity();

    return pixCellStep;
}


Vector CoordinatSystemWindow::fromCellToPix(Vector cells)
{
    cells -= cellNull;
    Vector density = getDensity();
    Vector pixCells = {};
    pixCells.x = cells.x * density.x;
    pixCells.y = - (cells.y * density.y);
    pixCells += getPixNullCoordinats();

    return pixCells;
}

Vector CoordinatSystemWindow::fromPixToCell(Vector pixs)
{
    Vector density = getDensity();
    Vector _nullPixCoor = getPixNullCoordinats();
    pixs.x -= _nullPixCoor.x;
    pixs.y = _nullPixCoor.y - pixs.y;
    Vector cells = {};
    cells.x = pixs.x / density.x;
    cells.y = (pixs.y / density.y);
    cells += cellNull;

    return cells;
}


Vector CoordinatSystemWindow::getXCellBound()
{
    Vector answer = {};
    answer.x = fromPixToCell({ 0, 0}).x;
    answer.y = fromPixToCell({ getSize().x, 0}).x;
    answer.sort();
    return answer;
}

Vector CoordinatSystemWindow::getYCellBound()
{
    Vector answer = {};
    answer.x = fromPixToCell({ 0, 0}).y;
    answer.y = fromPixToCell({ 0, getSize().y}).y;
    answer.sort();
    return answer;
}


size_t CoordinatSystemWindow::addPoint(Vector point, bool needToUpdateWindow/* = true*/)
{
    pointsMutex.lock();
    size_t _size = points.size();
    points.push_back(point);
    if(needToUpdateWindow)invalidateButton();
    pointsMutex.unlock();
    return _size;
}

size_t CoordinatSystemWindow::getPointsSize()
{
    size_t _size = 0;
    pointsMutex.lock();
    _size = points.size();
    pointsMutex.unlock();
    return _size;
}

size_t CoordinatSystemWindow::clearSys()
{
    try
    {
        scoped_lock pointsLock(pointsMutex);
        size_t _size = points.size();
        if (points.size() > 0) points.clear();
        invalidateButton();
        return _size;
    }
    catch(...)
    {
        printf("Exception: %s", __FUNCTION__);
        return 0;
    }
    return 0;
    
}

void CoordinatSystemWindow::invalidateSysConfig()
{
    onSize({}, {});
    invalidateButton();
}

int CoordinatSystemWindow::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    Window::onSize(managerSize, _newRect);
    return 0;
}

void CoordinatSystemWindow::drawAxis(M_HDC& _dc)
{
    app->setColor(color, _dc);
    app->rectangle({}, _dc.getSize(), _dc);

    Vector pixStep = getPixCellStep();
    Vector cellStep = getHumanCellStep();

    app->setColor(axisColor, _dc);
    char textNum[MAX_PATH] = {};
    for (int x = 0; x <= lround(cCellsLines.x); x++)
    {
        drawOneXLine(x, cellStep, textNum, _dc);
    }
    for (int x = -1; x >= -lround(cCellsLines.x); x--)
    {
        drawOneXLine(x, cellStep, textNum, _dc);
    }

    for (int y = 0; y <= lround(cCellsLines.y); y++)
    {
        drawOneYLine(y, cellStep, textNum, _dc);
    }
    for (int y = -1; y >= -lround(cCellsLines.y); y--)
    {
        drawOneYLine(y, cellStep, textNum, _dc);
    }

}

void CoordinatSystemWindow::draw()
{
    bool state = isValidViewState();
    cout << "isValidViewState: " << state << endl;
    if (!state)
    {
        int timestart = clock();
        if (isStretching)
        {
            M_HDC& destHdc = getFinalDC();
            app->stretchBlt(destHdc, {}, destHdc.getSize(), hdcCopyForStretching, {}, hdcCopyForStretching.getSize());
        }
        else
        {
            Window::draw();

            drawAxis(getFinalDC());
            drawPoints();
            drawAxisName(getFinalDC());
        }

        int timefinish = clock();

        cout << "CoordinatSystemWindow::draw():" << timefinish - timestart << endl;
    }
}

int CoordinatSystemWindow::onEnterWindowSizeMove()
{
    isStretching = true;
    M_HDC& _finaldc = getFinalDC();
    Vector destSize = _finaldc.getSize();
    hdcCopyForStretching.setSize(destSize, app);
    app->bitBlt(hdcCopyForStretching, {}, _finaldc);
    sizeBeforeMoving = getSize();
    return 1;
}

int CoordinatSystemWindow::onExitWindowSizeMove()
{
    isStretching = false;
    Vector sizeAfterMoving = getSize();

    if (sizeAfterMoving != sizeBeforeMoving)
    {
        invalidateButton();
    }
    return 1;
}


void CoordinatSystemWindow::onClick(Vector mp)
{
    Window::onClick(mp);
    Vector clickedCellPos = fromPixToCell(mp);

    //cout << clickedCellPos.getStr() << endl;

    if (onClickListener)
    {                          
        char message[3]{};
        sprintf(message, "%d", getMBCondition());
        onClickListener->sendMessage(message, &clickedCellPos);
    }
}

void CoordinatSystemWindow::drawPoints()
{
    size_t vectorSize = points.size();
    M_HDC& _outDC = *getOutputDC();
    app->setColor(pointsColor, _outDC);

    Vector halfSize = { (double)pointsR, (double)pointsR };

    pointsMutex.lock();
    for (int i = 0; i < vectorSize; i++)
    {
        Vector pixPos = fromCellToPix(points[i]);
        app->ellipse(pixPos, halfSize, _outDC);
    }
    pointsMutex.unlock();
}


void CoordinatSystemWindow::drawAxisName(M_HDC& destDC)
{
    app->setColor(app->systemSettings->TextColor, destDC);
    Vector xBound = getXCellBound();
    Vector yBound = getYCellBound();
    
    Vector xAxisNameTopRight = fromCellToPix({ xBound.y, cellNull.y });
    Vector xAxisNameBottomLeft = { xAxisNameTopRight.x - 200, xAxisNameTopRight.y + 200 };

    Rect rectXAxisName = { xAxisNameTopRight, xAxisNameBottomLeft };
    rectXAxisName.sort();  

    app->setColor(app->systemSettings->TextColor, destDC);
    app->drawText(rectXAxisName, axisXName.c_str(), destDC, DT_RIGHT | DT_TOP);

    Vector yAxisNameLeftTop = fromCellToPix({ cellNull.x, yBound.y});
    Vector yAxisNameRightBottom = { yAxisNameLeftTop.x + 200, yAxisNameLeftTop.y + 200 };

    Rect rectYAxisName = { yAxisNameLeftTop, yAxisNameRightBottom };
    rectYAxisName.sort();

    app->setColor(app->systemSettings->TextColor, destDC);
    app->drawText(rectYAxisName, axisYName.c_str(), destDC, DT_LEFT | DT_TOP);
}

void CoordinatSystemWindow::drawOneYLine(int stepNum, const Vector& cellStep, char* textBuf, M_HDC& destDc)
{
    double outputNum = cellNull.y+ stepNum * cellStep.y;
    sprintf(textBuf, "%.2lf", outputNum);

    Rect drawRect = {};
    Vector pixPos = fromCellToPix({ cellNull.x, outputNum });
    
    drawRect.finishPos.x = pixPos.x;
    drawRect.pos.x = drawRect.finishPos.x - 100;

    drawRect.pos.y = pixPos.y;
    drawRect.finishPos.y = drawRect.pos.y + 100;

    Rect lineRect = {};
    lineRect.pos.x = 0;
    lineRect.pos.y = pixPos.y;

    lineRect.finishPos.x = getSize().x;
    lineRect.finishPos.y = lineRect.pos.y;

    app->line(lineRect, destDc);

    app->drawText(drawRect, textBuf, destDc, DT_RIGHT);
}

void CoordinatSystemWindow::drawOneXLine(int stepNum, const Vector& cellStep, char* textBuf, M_HDC& destDc)
{
    double outputNum = cellNull.x + stepNum * cellStep.x;
    sprintf(textBuf, "%.2lf", outputNum);

    Rect drawRect = {};
    Vector pixPos = fromCellToPix({ outputNum, cellNull.y });

    drawRect.pos = pixPos;
    drawRect.finishPos = drawRect.pos + 100;

    Rect lineRect = {};
    lineRect.pos.x = pixPos.x;
    lineRect.pos.y = 0;

    lineRect.finishPos.x = pixPos.x;
    lineRect.finishPos.y = getSize().y;

    app->line(lineRect, destDc);

    app->drawText(drawRect, textBuf, destDc, DT_LEFT);
}

double CoordinatSystemWindow::humanRound(double delta)
{
    /*
    * 0.1 -> 0.1
    * 0.12 -> 0.1
    * 0.2  -> ??
    * 0.23 -> 0.25
    * 0.25 -> 0.25
    * 0.28 -> 0.25
    * 0.3  -> 0.25
    * 0.35 - >0.5
    * 0.4  0.5
    * 0.5  0.5
    * 0.6  0.5
    * 0.7  1
    * 0.8  1
    * 0.9  1
    * 3.14 exp:1
    *
    */

    //printf ("\n::%d::\n", delta);
    delta = fabs(delta);
    double exp = log10(delta);
    double mantissa = delta / (pow(10, ceil(exp)));

    //double mantissa = frexp (delta, &order);

    //printf ("Delta: %lf\tExp: %lf \tMantissa: %lf\n", delta, exp, mantissa);

    if (mantissa < 0.15) mantissa = 0.1;
    if (0.15 <= mantissa && mantissa < 0.23) mantissa = 0.2;
    if (0.23 <= mantissa && mantissa < 0.35) mantissa = 0.25;
    if (0.35 <= mantissa && mantissa < 0.65) mantissa = 0.5;
    if (0.65 <= mantissa && mantissa <= 1)   mantissa = 1;

    //printf ("delta: %lf, fDelta: %lf\n", delta, mantissa * pow (10, ceil(exp)));


    return mantissa * pow(10, ceil(exp));
}