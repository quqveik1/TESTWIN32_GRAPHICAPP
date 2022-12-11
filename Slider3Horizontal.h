#pragma once
#include "WindowsLib.cpp"
#include "Slider2.h"

struct Slider3Horizontal : Slider2
{
    M_HDC leftArrow;
    M_HDC rightArrow;
    COLORREF sliderDefColor;
    //M_HDC scrollRect;
    Slider3Horizontal(AbstractAppData* _app, Rect _rect, int* _parametr, int* _minParameter, int* _maxParameter, bool* _confirmed = NULL);

    //Rect getPointSliderRect();

    virtual void draw() override;
    virtual int onSize(Vector managerSize, Rect newRect = {}) override;
    virtual void onClick(Vector mp) override;
};