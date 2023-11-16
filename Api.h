#pragma once
#include <Windows.h>


struct Api
{
    virtual int setColor(COLORREF color, HDC dc, int thickness = 1);  
    virtual int ellipse(double x1, double y1, double x2, double y2, HDC dc);
    virtual int line(double x1, double y1, double x2, double y2, HDC dc);
    virtual int rectangle(double x1, double y1, double x2, double y2, HDC dc);

    virtual bool getAsyncKeyState(int symbol);
};