#pragma once
#include "Slider3.h"


Slider3Horizontal::Slider3Horizontal(AbstractAppData* _app, Rect _rect, int* _parametr, int* _minParameter, int* _maxParameter) :
    Slider2 (_app, _rect, _parametr, _minParameter, _maxParameter)
{
    leftArrow.loadImage(app, "arrow3Horizontal.bmp");
    app->DEBUGsaveImage(leftArrow);
}

