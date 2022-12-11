#pragma once
#include "Slider3Horizontal.h"
#include "Slider2.cpp"


Slider3Horizontal::Slider3Horizontal(AbstractAppData* _app, Rect _rect, int* _parameter, int* _minParameter, int* _maxParameter, bool* _confirmed/* = NULL*/) :
    Slider2 (_app, _rect, _parameter, _minParameter, _maxParameter, _confirmed),
    sliderDefColor(RGB(104, 104, 104))
{
    leftArrow.loadImage(app, "arrow3HorizontalLeft.bmp");
    rightArrow.loadImage(app, "arrow3HorizontalRight.bmp");
    color = RGB(62, 62, 62);
}



void Slider3Horizontal::draw()
{
    if (needToShow)
    {
        
        app->setColor(app->systemSettings->TRANSPARENTCOLOR, finalDC);
        app->rectangle(0, 0, getSize().x, getSize().y, finalDC);

        app->setColor(color, finalDC);
        app->rectangle(rect-rect.pos, finalDC);
        app->bitBlt(finalDC, {}, {}, leftArrow);
        double _rightPosX = getSize().x - rightArrow.getSize().x;
        app->bitBlt(finalDC, { _rightPosX, 0}, {}, rightArrow);


        setParameter(*parameter);
        app->setColor(sliderDefColor, finalDC);
        app->rectangle(sliderPos, sliderPos + sliderSize, finalDC);
    }
    setMbLastTime();
}



int Slider3Horizontal::onSize(Vector managerSize, Rect newRect/* = {}*/)
{
    if (newRect.getSize() != 0)
    {
        resize(newRect);
    }
    sliderSize = { 20, rect.getSize().y };


    Vector leftArrowSize = leftArrow.getSize();
    Vector rightArrowSize = rightArrow.getSize();
 
    possibleSliderPos = { .pos = {leftArrowSize.x, 0}, .finishPos = {getSize().x - rightArrowSize.x - sliderSize.x, 0} };
    kOfparameter = (*maxParameter - *minParameter) / (possibleSliderPos.getSize().x);
    setParameter(*parameter);
    
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
        setParameter((double)((int)(*parameter) - 1));
        app->updateScreen(this);
    }
    if (_rightArrow.inRect(mp))
    {
        setParameter((double)((int)(*parameter) + 1));
        app->updateScreen(this);
    }
}

