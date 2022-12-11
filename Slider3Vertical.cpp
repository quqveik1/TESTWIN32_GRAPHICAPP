#pragma once
#include "Slider3Vertical.h"

Slider3Vertical::Slider3Vertical(AbstractAppData* _app, Rect _rect, int* _parameter, int* _minParameter, int* _maxParameter, bool* _confirmed/* = NULL*/) :
    Slider3Horizontal(_app, _rect, _parameter, _minParameter, _maxParameter, _confirmed)
{
    arrow1.loadImage(app, "arrow3HorizontalDown.bmp");
    arrow2.loadImage(app, "arrow3HorizontalUp.bmp");
    color = RGB(62, 62, 62);
}