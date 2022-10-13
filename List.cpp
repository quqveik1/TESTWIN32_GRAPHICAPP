#pragma once
#include "List.h"


void List::addNewItem(Window* openButton, HDC dc/* = NULL*/, const char* text/* = NULL*/, int* option/*=NULL*/, int keybind/* = NULL*/)
{
    Rect newRect = { .pos = {0, (double)(currLen)*itemHeight}, .finishPos = {rect.getSize().x, (double)(currLen + 1) * itemHeight} };

    app->selectFont(fontName, font, finalDC);
    items[currLen]->rect = newRect;
    items[currLen]->font = font;
    items[currLen]->color = color;
    items[currLen]->keyBind = keybind;
    if (option)
    {
        items[currLen]->opening = option;
        items[currLen]->mode = 1;
    }
    items[currLen]->getOpeningManager() = (Manager*)openButton;
    items[currLen]->dc = dc;
    items[currLen]->text = text;
    items[currLen]->reInit();


    addWindow(items[currLen]);
}


void List::controlRect()
{
    rect.finishPos = { rect.pos.x + oneItemSize.x, rect.pos.y + oneItemSize.y * currLen };
}


List* List::addSubList(const char* ListText, int newListLength/* = NULL*/)
{
    if (!newListLength) return NULL;
    List* subList = new List(app, getNewSubItemCoordinats(), oneItemSize, newListLength);

    isThisItemList[currLen] = true;
    addNewItem(subList, NULL, ListText);

    return subList;
}

Vector List::getNewSubItemCoordinats()
{
    return Vector{ rect.finishPos.x, rect.pos.y + (double)(currLen)*itemHeight };
}




void List::draw()
{

    controlRect();
    app->windowsLibApi->standartManagerDraw(this);

    for (int i = 0; i < currLen; i++)
    {
        if (needToShow)
        {
            app->setColor(app->systemSettings->SecondMenuColor, finalDC, app->systemSettings->SIDETHICKNESS);
            app->line(0, i * itemHeight, rect.getSize().x, i * itemHeight, finalDC);

            if (items[i]->getOpeningManager())
            {
                if (items[i]->getOpeningManager()->needToShow)
                    app->ellipse(rect.getSize().x * 0.9 - activeItemCircleSize, ((double)i + 0.5) * itemHeight - activeItemCircleSize, rect.getSize().x * 0.9 + activeItemCircleSize, ((double)i + 0.5) * itemHeight + activeItemCircleSize, finalDC);
            }
        }

        if (isThisItemList[i] && !needToShow)
        {
            items[i]->getOpeningManager()->needToShow = false;
        }
    }

    if (!getMBCondition()) lastClickedItemNum = -1;
    setMbLastTime();
}

void List::onClick(Vector mp)
{
    int clikedButtonNum = app->windowsLibApi->standartManagerOnClick(this, mp);
    if (clikedButtonNum >= 0 && clikedButtonNum != lastClickedItemNum && !isClickedLastTime())
    {
        //printf ("last: %d, current: %d\n", lastClickedItemNum, clikedButtonNum);
        if (pointers[clikedButtonNum]->needToShow && mayFewWindowsBeOpenedAtTheSameTime)
        {
            clickButton(pointers[clikedButtonNum], this, mp);
            if (needToHideAfterClick) hide();
        }
        lastClickedItemNum = clikedButtonNum;
    }
}

