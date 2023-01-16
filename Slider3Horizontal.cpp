#pragma once
#include "Slider3Horizontal.h"
#include "Slider2.cpp"


Slider3Horizontal::Slider3Horizontal(EngineAppApi* _app, Rect _rect, int* _parameter, int* _minParameter, int* _maxParameter, bool* _confirmed/* = NULL*/) :
    Slider2 (_app, _rect, _parameter, _minParameter, _maxParameter, _confirmed),
    sliderDefColor(RGB(104, 104, 104))
{
    arrow1.loadImage(app, "arrow3HorizontalLeft.bmp");
    arrow2.loadImage(app, "arrow3HorizontalRight.bmp");
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
        app->bitBlt(finalDC, arrow1Rect, arrow1);
        //double _rightPosX = getSize().x - rightArrow.getSize().x;
        app->bitBlt(finalDC, arrow2Rect, arrow2);


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

    arrow1Rect = { .pos = {}, .finishPos = arrow1.getSize() };
    arrow2Rect = { .pos = {getSize().x - arrow1.getSize().x, 0}, .finishPos = {getSize().x, arrow1.getSize().y} };
 
    possibleSliderPos = { .pos = {arrow1Rect.getSize().x, 0}, .finishPos = {getSize().x - arrow2Rect.getSize().x - sliderSize.x, 0} };
    kOfparameter = (*maxParameter - *minParameter) / (possibleSliderPos.getSize().x);
    setParameter(*parameter);
    
    return 0;
}



void Slider3Horizontal::onClick(Vector mp)
{
    if (arrow1Rect.inRect(mp))
    {
        setParameter((double)((int)(*parameter) - oneArrowClickDelta));
        app->updateScreen(this);
    }
    if (arrow2Rect.inRect(mp))
    {
        setParameter((double)((int)(*parameter) + oneArrowClickDelta));
        app->updateScreen(this);
    }
}

