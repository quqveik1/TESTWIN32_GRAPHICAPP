#pragma once
#include "LinearLayout.h"
#include "Layout.cpp"
#include "WindowsLibApi.h"

int LinearLayout::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    setOnSizeActive(true);
    Layout::onSize(managerSize, _newRect);
    Vector nextStartPos = {};
    for (size_t i = 0; i < pointers.size(); i++)
    {
        Window* _wnd = pointers[i];
        if (_wnd)
        {
            LinearLayoutInfo* _layoutInfo = (LinearLayoutInfo*)_wnd->getLayoutInfo();
            if (_layoutInfo)
            {
                nextStartPos += _layoutInfo->margin.pos;
            }

            _wnd->MoveWindowTo(nextStartPos);

            if (flags == FLAG_VERTICAL)
            {
                nextStartPos.y = _wnd->rect.finishPos.y + deltaBetweenButtons;
            }
            if (flags == FLAG_HORIZONTAL)
            {
                nextStartPos.x = _wnd->rect.finishPos.x + deltaBetweenButtons;
            }

            if (_layoutInfo)
            {
                nextStartPos += _layoutInfo->margin.finishPos;
            }
        }
    }

    if (pointers.size() > 0)
    {
        Rect newRect = calcRect();

        if (newRect != rect)
        {
            resize(newRect);
        }
    }

    setOnSizeActive(false);
    return 0;
}


void LinearLayout::onSizeChildCall(Window* _chld)
{
    if (!getOnSizeActive())
    {
        //onSize({}, {});
    }
}

bool LinearLayout::getOnSizeActive() 
{ 
    isOnSizeActiveMutex.lock(); 
    bool ans = isOnSizeActive; 
    isOnSizeActiveMutex.unlock();
    return ans; 
}


void LinearLayout::setOnSizeActive(bool newState)
{ 
    isOnSizeActiveMutex.lock(); 
    isOnSizeActive = newState;
    isOnSizeActiveMutex.unlock(); 
}


void LinearLayout::onClick(Vector mp)
{
    app->windowsLibApi->standartManagerOnClick(this, mp);
}




Rect LinearLayout::calcRect()
{
    //Rect newRect = { .pos = {DBL_MAX, DBL_MAX}, .finishPos = {DBL_MIN, DBL_MIN} };
    Rect newRect = rect;
    for (size_t i = 0; i < pointers.size(); i++)
    {
        Window* _wnd = pointers[i];
        if (_wnd)
        {
            /*
            if (pointers[i]->rect.pos.x < newRect.pos.x)
            {
                newRect.pos.x = pointers[i]->rect.pos.x;
            }

            if (pointers[i]->rect.pos.y < newRect.pos.y)
            {
                newRect.pos.y = pointers[i]->rect.pos.y;
            }
            */
            if (_wnd->rect.getSize().x > newRect.getSize().x && !matchParentX)
            {
                newRect.finishPos.x = pointers[i]->rect.finishPos.x + newRect.pos.x;
            }

            if (_wnd->rect.getSize().y > newRect.getSize().y && !matchParentY)
            {
                newRect.finishPos.y = pointers[i]->rect.finishPos.y + newRect.pos.y;
            }

        }
    }

    return newRect;

}