#pragma once
#include "WindowsLib.cpp"
#include "Slider2.h"

struct Slider3Horizontal : Slider2
{
    int oneArrowClickDelta = 1;
    M_HDC arrow1;//arrow1 if click on it parameter reduces for oneArrowClickDelta
    Rect arrow1Rect = {};
    M_HDC arrow2; //arrow2 if click on it parameter grows for oneArrowClickDelta
    Rect arrow2Rect = {};
    COLORREF sliderDefColor;
    //M_HDC scrollRect;
    Slider3Horizontal(AbstractAppData* _app, Rect _rect, int* _parametr, int* _minParameter, int* _maxParameter, bool* _confirmed = NULL);

    //Rect getPointSliderRect();

    virtual void draw() override;
    virtual int onSize(Vector managerSize, Rect newRect = {}) override;
    virtual void onClick(Vector mp) override;
};