#include "SliderBase.h"

SliderBase::SliderBase(AbstractAppData* _app, Rect _rect, int* _parametr, int* _minParameter, int* _maxParameter, Oriantation _oriantation, Vector _arrowSize/* = {}*/)  :
    Manager(_app, _rect, 1, true, NULL, {}, RGB(144, 144, 144)),
    parametr(_parametr),
    pointSlider(NULL),
    confirmed(_confirmed),
    minParameter(_minParameter),
    maxParameter(_maxParameter),
    oriantation (_oriantation),
    arrowSize (_arrowSize)
{
}


void SliderBase::draw()
{
    if (needToShow)
    {
        app->setColor(app->systemSettings->TRANSPARENTCOLOR, finalDC);
        app->rectangle(0, 0, getSize().x, getSize().y, finalDC);

        countCompress();
        if (oriantation == O_HORIZONTAL)
        {
            mainBlock(getMousePos().x, mousePosLastTime.x, finishSidePos - firstSidePos, sliderRectPos.x, sliderRectSize.x);
        }

        drawSliderBackground();

        drawSliderRect();
        drawArrows();
        

        
    }
    setMbLastTime();
}

void SliderBase::mainBlock(double _mp, double _mpLastTime, double _size, double& _sliderRectPos, double& _sliderRectSize)
{
    if (isSliderClicked)
    {
        if (!getMBCondition())
        {
            isSliderClicked = false;
            confirmUse();
        }

        if (app->systemSettings->debugMode >= 5) printf("slider[%s] mp delta: %lf\n", devName, _mp - _mpLastTime);

        _sliderRectPos += _mp - _mpLastTime;
        if (isSmaller(_sliderRectPos, 0)) _sliderRectPos = 0;
        if (isBigger(_sliderRectPos, _size - _sliderRectSize)) _sliderRectPos = _size - _sliderRectSize;
        doubleVersionOfParameter = _sliderRectPos * kompressOfParametr;
        *parametr = doubleVersionOfParameter;
        setMPLastTime();
    }
    else
    {
        doubleVersionOfParameter = *parametr;
    }

    _sliderRectPos = doubleVersionOfParameter / kompressOfParametr;

}



void SliderBase::onClick(Vector mp)
{
    setActiveWindow(this);
    Rect sliderRect = getPointSliderRect();
    bool lastTimeCLicked = isClickedLastTime();
    if (sliderRect.inRect(mp) && !lastTimeCLicked)
    {
        isSliderClicked = true;
        setMPLastTime();
    }
}

Rect SliderBase::getSliderRect()
{
    Rect tempRect = { .pos = pointSliderPos, .finishPos = pointSliderPos + pointSliderSize };
    return tempRect;
}