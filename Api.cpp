#pragma once 
#include "Api.h"
#include <iostream>

int Api::setColor(COLORREF color, HDC dc, int thickness/* = 1*/)
{
    HBRUSH newSolidBrush = CreateSolidBrush(color);
    HBRUSH oldSolidBrush = (HBRUSH)SelectObject(dc, (HGDIOBJ)newSolidBrush);
    if (oldSolidBrush)
    {
        DeleteObject(oldSolidBrush);
    }


    HPEN newPen = CreatePen(PS_SOLID, thickness, color);
    HPEN oldPen = (HPEN)SelectObject(dc, (HGDIOBJ)newPen);
    if (oldPen)
    {
        DeleteObject(oldPen);
    }
    return NULL;
}

int Api::line(double x1, double y1, double x2, double y2, HDC dc)
{
    bool result = MoveToEx(dc, std::lround(x1), std::lround(y1), NULL);
    result *= LineTo(dc, std::lround(x2), std::lround(y2));
    return NULL;

}

int Api::ellipse(double x1, double y1, double x2, double y2, HDC dc)
{
    return Ellipse(dc, std::lround(x1), std::lround(y1), std::lround(x2), std::lround(y2));
}

int Api::rectangle(double x1, double y1, double x2, double y2, HDC dc)
{
    return Rectangle(dc, std::lround(x1), std::lround(y1), std::lround(x2), std::lround(y2));
}

bool Api::getAsyncKeyState(int symbol)
{
    return GetAsyncKeyState(symbol);
}


