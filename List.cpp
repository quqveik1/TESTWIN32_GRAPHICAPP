#pragma once
#include "List.h"


void List::addNewItem(Window* openButton, HDC dc/* = NULL*/, const char* text/* = NULL*/, int* option/*=NULL*/, int keybind/* = NULL*/)
{
    Rect newRect = { .pos = {0, (double)(currLen)*itemHeight}, .finishPos = {rect.getSize().x, (double)(currLen + 1) * itemHeight} };

    app->selectFont(fontName, font, finalDC);
    items.push_back(new OpenManager(app, oneItemSize));
    isThisItemList.push_back(false);
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


    addWindow(items[currLen], 1);
}


void List::addNewItem(Option* _option)
{
    addNewItem(_option->reciever, NULL, _option->name);
}


void List::controlRect()
{
    rect.finishPos = { rect.pos.x + oneItemSize.x, rect.pos.y + oneItemSize.y * currLen };
}


List* List::addSubList(const char* ListText, int newListLength/* = NULL*/)
{
    if (!newListLength) return NULL;
    List* subList = new List(app, getNewSubItemCoordinats(), oneItemSize, newListLength);

    isThisItemList.push_back(true);
    items.push_back(new OpenManager(app, oneItemSize));
    addNewItem(subList, NULL, ListText);

    return subList;
}

Vector List::getNewSubItemCoordinats()
{
    return Vector{ rect.finishPos.x, rect.pos.y + (double)(currLen)*itemHeight };
}


int List::mbDown(Vector mp, int button)
{
    Rect sizeRect = rect - rect.pos;
    if (sizeRect.inRect(mp))
    {
        isOnMeMbDown = true;
    }

    return 0;
}


int List::mbUp(Vector mp, int button)
{
    isOnMeMbDown = false;
    return 0;
}



void List::draw()                                                                                                                               
{

    controlRect();
    app->windowsLibApi->standartManagerDraw(this);
    Vector size = app->getHDCSize(finalDC);

    for (int i = 0; i < currLen; i++)
    {
        if (needToShow)
        {
            app->setColor(app->systemSettings->SecondMenuColor, finalDC, lround(app->systemSettings->SIDETHICKNESS));
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
            //clickButton(pointers[clikedButtonNum], this, mp);
            if (needToHideAfterClick) hide();
        }
        lastClickedItemNum = clikedButtonNum;
    }
}


int List::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    app->windowsLibApi->standartManagerOnSize(this, managerSize, _newRect);

    Rect newRect = rect;
    newRect.setSize({ oneItemSize.x, oneItemSize.y * getCurLen() });
    resize(newRect);
    return 0;
}

