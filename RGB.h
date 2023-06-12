#pragma once

#include <Windows.h>

struct RGB_Struct
{
    int red = 0;
    int green = 0;
    int blue = 0;

    RGB_Struct()
    {};

    RGB_Struct(COLORREF color)
    {
        red = GetRValue(color);
        green = GetGValue(color);
        blue = GetBValue(color);
    }

    operator COLORREF()
    {
        return RGB(red, green, blue);
    }


    void setRed(int val) { red = val; };
    void setGreen(int val) { green = val; };
    void setBlue(int val) { blue = val; };
};