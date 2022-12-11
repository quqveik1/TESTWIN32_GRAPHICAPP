#pragma once 
#include "Slider2.h"


void Slider2::confirm()
{
    if (confirmed)*confirmed = true;
}

Rect Slider2::getsliderRect()
{
    Rect tempRect = { .pos = sliderPos, .finishPos = sliderPos + sliderSize };
    return tempRect;
}

void Slider2::draw()
{
    if (needToShow)
    {
        //sliderPos.x = doubleVersionOfParameter / kOfparameter;
        setParameter(doubleVersionOfParameter);
        app->setColor(app->systemSettings->TRANSPARENTCOLOR, finalDC);
        app->rectangle(0, 0, getSize().x, getSize().y, finalDC);

        app->setColor(color, finalDC);
        app->rectangle(sliderSize.x / 2, sliderSize.y, getSize().x - sliderSize.x / 2, getSize().y, finalDC);

        app->transparentBlt(finalDC, sliderPos.x, 0, 0, 0, slider);
    }
    setMbLastTime();

}


void Slider2::onClick(Vector mp)
{ 
    /*
    setActiveWindow(this);
    Rect sliderRect = getsliderRect();
    bool lastTimeCLicked = isClickedLastTime();
    if (sliderRect.inRect(mp) && !lastTimeCLicked)
    {
        //isSliderClicked = true;
        setMPLastTime();
    }
    */
}

int Slider2::isParameterValid(int parameter)
{
    if (*minParameter <= parameter && parameter < *maxParameter)
    {
        return 1;
    }
    return 0;
}

int Slider2::setParameter(double _data)
{
    doubleVersionOfParameter = _data;
    if (isParameterValid(lround(doubleVersionOfParameter)))
    {
        if (isBigger(doubleVersionOfParameter, (double)*maxParameter)) doubleVersionOfParameter = *maxParameter;
        if (isSmaller(doubleVersionOfParameter, (double)*minParameter)) doubleVersionOfParameter = *minParameter;
    }
    
    
    *parameter = lround(doubleVersionOfParameter);
    sliderPos.x = (doubleVersionOfParameter / kOfparameter) + possibleSliderPos.pos.x;
    return 0;
}

int Slider2::onMouseMove(Vector mp, Vector delta)
{
    if (isBigger(fabs(delta.x), 0))
    {
        if (isSliderClicked)
        {
            sliderPos.x += delta.x;
            if (isSmaller(sliderPos.x, possibleSliderPos.pos.x)) sliderPos.x = possibleSliderPos.pos.x;
            if (isBigger(sliderPos.x, possibleSliderPos.finishPos.x)) sliderPos.x = possibleSliderPos.finishPos.x;
            setParameter((sliderPos.x - possibleSliderPos.pos.x) * kOfparameter);
            /*
            doubleVersionOfParameter = (sliderPos.x - possibleSliderPos.pos.x) * kOfparameter;
            *parameter = lround(doubleVersionOfParameter);
            sliderPos.x = doubleVersionOfParameter / kOfparameter;
            */

            app->updateScreen(this);
        }
    }
    return 0;
}


int Slider2::mbDown(Vector mp, int button)
{
    //printf("MbDown\n");
    Rect _validrect = possibleSliderPos;
    _validrect.finishPos += sliderSize;
    if (_validrect.inRect(mp))
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


int Slider2::onSize(Vector newManagerSize, Rect newRect/* = {}*/)
{
    if (newRect.getSize() != 0)
    {
        resize(newRect);
    }
    kOfparameter = (*maxParameter - *minParameter) / (getSize().x - sliderSize.x);
    sliderPos.x = *parameter / kOfparameter;
    possibleSliderPos = { .pos = {0, 0}, .finishPos = {getSize().x - sliderSize.x, 0} };
    return 0;
}

