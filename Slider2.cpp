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
        if (!isSliderClicked)
        {
            doubleVersionOfParameter = *parametr;
        }
        pointSliderPos.x = doubleVersionOfParameter / kOfParametr;
        app->setColor(app->systemSettings->TRANSPARENTCOLOR, finalDC);
        app->rectangle(0, 0, getSize().x, getSize().y, finalDC);

        app->setColor(color, finalDC);
        app->rectangle(pointSliderSize.x / 2, pointSliderSize.y, getSize().x - pointSliderSize.x / 2, getSize().y, finalDC);

        app->transparentBlt(finalDC, pointSliderPos.x, 0, 0, 0, pointSlider);
    }
    setMbLastTime();

}


void Slider2::onClick(Vector mp)
{ 
    /*
    setActiveWindow(this);
    Rect sliderRect = getPointSliderRect();
    bool lastTimeCLicked = isClickedLastTime();
    if (sliderRect.inRect(mp) && !lastTimeCLicked)
    {
        //isSliderClicked = true;
        setMPLastTime();
    }
    */
}

int Slider2::onMouseMove(Vector mp, Vector delta)
{
    if (isBigger(fabs(delta.x), 0))
    {
        if (isSliderClicked)
        {
            pointSliderPos.x += delta.x;
            if (isSmaller(pointSliderPos.x, 0)) pointSliderPos.x = 0;
            if (isBigger(pointSliderPos.x, getSize().x - pointSliderSize.x)) pointSliderPos.x = getSize().x - pointSliderSize.x;
            doubleVersionOfParameter = pointSliderPos.x * kOfParametr;
            *parametr = lround(doubleVersionOfParameter);
            pointSliderPos.x = doubleVersionOfParameter / kOfParametr;

            app->updateScreen(this);
        }
    }
    return 0;
}


int Slider2::mbDown(Vector mp, int button)
{
    //printf("MbDown\n");
    if ((rect - rect.pos).inRect(mp))
    {
        
        isSliderClicked = true;
    }
    return 0;
}

int Slider2::mbUp(Vector mp, int button)
{
    //printf("MbUp\n");
    if (isSliderClicked)
    {
        app->updateScreen(this);
        isSliderClicked = false;
        confirm();
    }
    
    return 0;
}

