#pragma once
#include "WindowsLib.cpp"

struct Slider3Horizontal : Manager
{
    Slider3Horizontal(AbstractAppData* _app, Rect _rect, int* _parametr, int* _minParameter, int* _maxParameter);

    Rect getPointSliderRect();

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
};