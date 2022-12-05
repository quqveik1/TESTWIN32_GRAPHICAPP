#pragma once
#include "Slider3.h"
#include "Slider2.cpp"


Slider3Horizontal::Slider3Horizontal(AbstractAppData* _app, Rect _rect, int* _parametr, int* _minParameter, int* _maxParameter, bool* _confirmed/* = NULL*/) :
    Slider2 (_app, _rect, _parametr, _minParameter, _maxParameter, _confirmed)
{
    leftArrow.loadImage(app, "arrow3HorizontalLeft.bmp");
    rightArrow.loadImage(app, "arrow3HorizontalRight.bmp");
    pointSliderSize = { 20, _rect.getSize().y };
    //scrollRect.loadImage(app, "SliderRect.bmp");
    
    app->DEBUGsaveImage(rightArrow);
}



void Slider3Horizontal::draw()
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
        app->rectangle(rect-rect.pos, finalDC);
        app->bitBlt(finalDC, {}, {}, leftArrow);
        double _rightPosX = getSize().x - rightArrow.getSize().x;
        app->bitBlt(finalDC, { _rightPosX, 0}, {}, rightArrow);

        app->setColor(TX_WHITE, finalDC);
        app->rectangle(pointSliderPos, pointSliderPos + pointSliderSize, finalDC);

        //app->transparentBlt(finalDC, pointSliderPos.x, 0, 0, 0, scrollRect);
    }
    setMbLastTime();
}

