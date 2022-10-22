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
    app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);

    return 0;
}

void ColorComponentChanger::onClick(Vector mp)
{
    setActiveWindow(this);
    if (slider->rect.inRect(mp)) slider->onClick(mp - slider->rect.pos);
    if (inputButton->rect.inRect(mp)) inputButton->onClick(mp - inputButton->rect.pos);
}