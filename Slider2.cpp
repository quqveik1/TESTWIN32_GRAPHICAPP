#pragma once 
#include "Slider2.h"


void Slider2::confirm()
{
    if (confirmed)*confirmed = true;
}

Rect Slider2::getPointSliderRect()
{
    Rect tempRect = { .pos = pointSliderPos, .finishPos = pointSliderPos + pointSliderSize };
    return tempRect;
}

void Slider2::draw()
{
    if (needToShow)
    {
        app->setColor(app->systemSettings->TRANSPARENTCOLOR, finalDC);
        app->rectangle(0, 0, getSize().x, getSize().y, finalDC);

        app->setColor(color, finalDC);
        app->rectangle(pointSliderSize.x / 2, pointSliderSize.y, getSize().x - pointSliderSize.x / 2, getSize().y, finalDC);

        app->transparentBlt(finalDC, pointSliderPos.x, 0, 0, 0, pointSlider);

        if (isSliderClicked)
        {
            if (!getMBCondition())
            {
                isSliderClicked = false;
                confirm();
            }

            if (app->systemSettings->debugMode >= 5)printf("slider2 mp delta: %lf\n", getMousePos().x - mousePosLastTime.x);

            pointSliderPos.x += getMousePos().x - mousePosLastTime.x;
            if (isSmaller(pointSliderPos.x, 0)) pointSliderPos.x = 0;
            if (isBigger(pointSliderPos.x, getSize().x - pointSliderSize.x)) pointSliderPos.x = getSize().x - pointSliderSize.x;
            doubleVersionOfParameter = pointSliderPos.x * kOfParametr;
            *parametr = doubleVersionOfParameter;
            setMPLastTime();
        }
        else
        {
            doubleVersionOfParameter = *parametr;
        }

        pointSliderPos.x = doubleVersionOfParameter / kOfParametr;
    }
    setMbLastTime();

}


void Slider2::onClick(Vector mp)
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