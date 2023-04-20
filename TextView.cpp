#pragma once
#include "TextView.h"


int TextView::setTrancparencyOutput(int newStatus)
{
    if (newStatus)
    {
        setColor(C_TRANSPARENT);
    }
    else
    {
        setColor(app->systemSettings->BackgroundColor);
    }
    return Window::setTrancparencyOutput(newStatus);
}

int TextView::setFont(int newFont)
{
    int answer = Window::setFont(newFont);
    //Vector newSize = app->getTextExtent(text, font, fontName);
    managerOnSize();
    return answer;
}

const char* TextView::setText(const char* newText)
{
    const char* answer = Window::setText(newText);
    //Vector newSize = app->getTextExtent(text, font, fontName);
    managerOnSize();
    return answer;
} 

void TextView::setWrapStatus(bool status)
{
    setWrapStatusX(status);
    setWrapStatusY(status);
} 
void TextView::setWrapStatusX(bool status)
{
    wrapContentX = status;
    managerOnSize();
} 

void TextView::setWrapStatusY(bool status)
{
    wrapContentY = status;
    managerOnSize();
}


double TextView::setRelativeFontSize(double _size)
{
    if (isBigger(_size, 0) && isSmaller(_size, 1))
    {
        relativeFontSize = _size;
    }
    return onSize({}, {});
}


int TextView::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    Window::onSize(managerSize, _newRect);
    wrapControl();
    return 0;
}

void TextView::wrapControl()
{
    Vector textSize = app->getTextExtent(text, font, fontName);
    Vector currSize = getSize();
    Vector newSize = currSize;

    if (wrapContentY)
    {
        newSize.y = (textSize.y / relativeFontSize);
    }
    if (wrapContentX)
    {
        newSize.x = (textSize.x / relativeFontSize);
    }

    resize(newSize);
}
