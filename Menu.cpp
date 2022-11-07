#pragma once
#include "Menu.h"


void Menu::draw()
{
    if (dc) app->bitBlt(finalDC, 0, 0, 0, 0, dc);

    controlHandle();

    onUpdate();

    handle.print (finalDC);

    for (int i = 0; i < currentSize; i++)
    {
        drawOneLine(i);
    }
}

void Menu::onClick(Vector mp)
{
    setActiveWindow(this);

    int missClicked = true;

    mp.y -= handle.rect.finishPos.y;

    int mx = std::lround(mp.x);
    int my = std::lround(mp.y);




    if (needToShow)
    {
        reDraw = true;
        missClicked = onClickLine(mp);
    }
}

int Menu::mbDown(Vector mp, int button)
{
    clickHandle();
    return 0;
}

int Menu::mbUp(Vector mp, int button)
{
    mbUpHandle();
    return 0;
} 

int Menu::onMouseMove(Vector mp, Vector delta)
{
    moveHandle(delta);
    return 0;
}
