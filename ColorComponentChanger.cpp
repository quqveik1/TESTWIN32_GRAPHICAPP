#pragma once
#include "ColorComponentChanger.h"

void ColorComponentChanger::draw()
{
    app->setColor(color, finalDC);
    app->rectangle(0, 0, getSize().x, getSize().y, finalDC);

    slider->draw();
    app->transparentBlt(finalDC, slider->rect.pos.x, slider->rect.pos.y, 0, 0, slider->finalDC);   
    inputButton->draw();
    app->transparentBlt(finalDC, inputButton->rect.pos.x, inputButton->rect.pos.y, 0, 0, inputButton->finalDC);
}

int ColorComponentChanger::onMouseMove(Vector mp, Vector delta)
{
    if (componentType == 1)
    {
        *component = GetRValue(app->systemSettings->DrawColor);
    }
    if (componentType == 2)
    {
        *component = GetGValue(app->systemSettings->DrawColor);
    }
    if (componentType == 3)
    {
        *component = GetBValue(app->systemSettings->DrawColor);
    }

    app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);


    if (componentType == 1)
    {
        app->systemSettings->DrawColor = RGB(*component, GetGValue(app->systemSettings->DrawColor), GetBValue(app->systemSettings->DrawColor));
    }
    if (componentType == 2)
    {
        app->systemSettings->DrawColor = RGB(GetRValue(app->systemSettings->DrawColor), *component, GetBValue(app->systemSettings->DrawColor));
    }
    if (componentType == 3)
    {
        app->systemSettings->DrawColor = RGB(GetRValue(app->systemSettings->DrawColor), GetGValue(app->systemSettings->DrawColor), *component);
    }


    return 0;
}

void ColorComponentChanger::onClick(Vector mp)
{
    setActiveWindow(this);
    if (slider->rect.inRect(mp)) slider->onClick(mp - slider->rect.pos);
    if (inputButton->rect.inRect(mp)) inputButton->onClick(mp - inputButton->rect.pos);
}