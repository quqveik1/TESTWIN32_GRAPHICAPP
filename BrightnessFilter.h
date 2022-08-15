#pragma once
#include "TwoOptionsMenu.cpp"

struct BrightnessFilter : TwoOptionsMenu
{
    BrightnessFilter (Rect _rect, Vector _firstDomain, Vector _secondDomain, AbstractAppData *_data = NULL) :
        TwoOptionsMenu (_rect, _firstDomain, _secondDomain, _data)
    {
        name = "‘ильтр €ркостиg";
    }

   
    virtual void apply ();
};