#pragma once
#include "Slider3Horizontal.h"

struct Slider3Vertical : Slider3Horizontal
{
    Slider3Vertical(AbstractAppData* _app, Rect _rect, int* _parameter, int* _minParameter, int* _maxParameter, bool* _confirmed = NULL);

};
