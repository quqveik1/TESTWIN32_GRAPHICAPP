#pragma once
#include "WindowsLib.cpp"
#include "Slider2.h"

struct Slider3Horizontal : Slider2
{
    M_HDC leftArrow;
    M_HDC rightArrow;
    //M_HDC scrollRect;
    Slider3Horizontal(AbstractAppData* _app, Rect _rect, int* _parametr, int* _minParameter, int* _maxParameter, bool* _confirmed = NULL);

    //Rect getPointSliderRect();

    virtual void draw() override;
};