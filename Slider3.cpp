#pragma once
#include "Slider3.h"
#include "Slider2.cpp"


Slider3Horizontal::Slider3Horizontal(AbstractAppData* _app, Rect _rect, int* _parametr, int* _minParameter, int* _maxParameter, bool* _confirmed/* = NULL*/) :
    Slider2 (_app, _rect, _parametr, _minParameter, _maxParameter, _confirmed)
{
    leftArrow.loadImage(app, "arrow3HorizontalLeft.bmp");
    rightArrow.loadImage(app, "arrow3HorizontalRight.bmp");
    
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



int Slider3Horizontal::onSize(Vector managerSize, Rect newRect/* = {}*/)
{
    if (newRect.getSize() != 0)
    {
        resize(newRect);
    }
    pointSliderSize = { 20, rect.getSize().y };


    Vector leftArrowSize = leftArrow.getSize();
    Vector rightArrowSize = rightArrow.getSize();
 
    possibleSliderPos = { .pos = {leftArrowSize.x, 0}, .finishPos = {getSize().x - rightArrowSize.x - pointSliderSize.x, 0} };
    kOfParametr = (*maxParameter - *minParameter) / (possibleSliderPos.getSize().x);
    setParameter(*parametr);
    
    return 0;
}



void Slider3Horizontal::onClick(Vector mp)
{
    Vector leftArrowSize = leftArrow.getSize();
    Vector rightArrowSize = rightArrow.getSize();
    Rect _leftArrow = { .pos = {}, .finishPos = leftArrowSize };
    Rect _rightArrow = { .pos = {getSize().x - rightArrowSize.x, 0}, .finishPos = {getSize().x, rightArrowSize.y} };
    if (_leftArrow.inRect(mp))
    {
    }
    if (_rightArrow.inRect(mp))
    {
    }
}

