#pragma once
#include "OptionWindow.h"

int OptionWindow::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    assert(option);

    app->testDC.clear();
    app->selectFont(fontName, font, app->testDC);
    Vector sizeOfLabel = app->getTextExtent(option->name, app->testDC);
    Vector newSize =
    {
        .x = sizeOfLabel.x + (double)(deltaBetweemFrameAndOption * 2),
        .y = getSize().y
    };
    resize(newSize);
    return 0;
}
