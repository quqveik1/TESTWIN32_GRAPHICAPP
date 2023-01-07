#pragma once
#include "LinearLayout.h"
#include "Layout.cpp"

int LinearLayout::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    Vector nextStartPos = {};
    for (int i = 0; i < pointers.size(); i++)
    {
        if (pointers[i])
        {
            pointers[i]->MoveWindowTo(nextStartPos);
            if (flags == FLAG_VERTICAL)
            {
                nextStartPos.y = pointers[i]->rect.finishPos.y + deltaBetweenButtons;
            }
            if (flags == FLAG_HORIZONTAL)
            {
                nextStartPos.x = pointers[i]->rect.finishPos.x + deltaBetweenButtons;
            }
        }
    }

    Rect newRect = calcRect();

    if (newRect != rect)
    {
        resize(newRect);
    }

    return 0;
}



Rect LinearLayout::calcRect()
{
    Rect newRect = { .pos = {DBL_MAX, DBL_MAX}, .finishPos = {DBL_MIN, DBL_MIN} };
    for (int i = 0; i < pointers.size(); i++)
    {
        if (pointers[i])
        {
            if (pointers[i]->rect.pos.x < newRect.pos.x)
            {
                newRect.pos.x = pointers[i]->rect.pos.x;
            }

            if (pointers[i]->rect.pos.y < newRect.pos.y)
            {
                newRect.pos.y = pointers[i]->rect.pos.y;
            }

            if (pointers[i]->rect.finishPos.x > newRect.finishPos.x)
            {
                newRect.finishPos.x = pointers[i]->rect.finishPos.x;
            }

            if (pointers[i]->rect.finishPos.x > newRect.finishPos.x)
            {
                newRect.finishPos.x = pointers[i]->rect.finishPos.x;
            }

        }
    }

    return newRect;

}