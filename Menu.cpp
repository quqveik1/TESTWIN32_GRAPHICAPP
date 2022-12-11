#pragma once
#include "Menu.h"


void Menu::draw()
{
    if (dc) app->bitBlt(finalDC, 0, 0, 0, 0, dc);

    controlHandle();

    drawBeforeMainBlock();

    handle.print (finalDC);

    for (int i = 0; i < currentSectionLen; i++)
    {
        drawOneLine(i);
    }

    drawAfterMainBlock();
}

void Menu::onClick(Vector mp)
{
    setActiveWindow(this);

    int missClicked = true;
    if (needToShow)
    {
        reDraw = true;
        missClicked = onClickLine(mp);
    }
}


Rect Menu::getSectionRect(int num)
{
    Rect _answer = {};
    _answer.pos.x = oneSection.pos.x;
    _answer.pos.y = handle.rect.finishPos.y + oneSection.finishPos.y * (num-1);
    _answer.finishPos.x = oneSection.finishPos.x;
    _answer.finishPos.y = handle.rect.finishPos.y + oneSection.finishPos.y * (num - 1) + oneSection.getSize().y;

    return _answer;
}


int Menu::findSectionNum(Vector mp)
{
    Vector _mpwithoutHandle = mp;
    _mpwithoutHandle.y = mp.y - handle.rect.finishPos.y;

    int resultNum = _mpwithoutHandle.y / oneSection.finishPos.y;

    Rect _sectionRect = getSectionRect(resultNum);

    if (_sectionRect.inRect(mp))
    {
        return resultNum;
    }
    return -1;

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

int Menu::onSize(Vector newManagerSize, Rect newRect = {})
{
    
    if (sliderStatus)
    {
        Rect _sliderRect = { .pos = {oneSection.finishPos.x, handle.rect.finishPos.y}, .finishPos = {oneSection.finishPos.x + sliderwidth, } };
    }
    resize(newRect);
}
