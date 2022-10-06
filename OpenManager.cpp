#pragma once
#include "OpenManager.h"

void OpenManager::click()
{
    if (mode == 0)
    {
        assert(openingManager);
        if (getOpeningManager()->needToShow)
        {
            getOpeningManager()->hide();
        }
        else
        {
            getOpeningManager()->show();
        }
        getOpeningManager()->draw();
    }

    if (mode == 1)
    {
        if (*opening == 1) *opening = 0;
        if (*opening == 0) *opening = 1;
    }
}

void OpenManager::onClick(Vector mp)
{
    setActiveWindow(this);
    if (!isClickedLastTime())
    {
        click(); 
    }
    setMbLastTime();
}

void OpenManager::draw()
{
    app->windowsLibApi->standartWindowDraw(this);

    if (app->getAsyncKeyState(VK_CONTROL) && app->getAsyncKeyState(keyBind) && !wasListTimeKeyBoardClicked)
    {
        click();
        wasListTimeKeyBoardClicked = true;
    }

    if (wasListTimeKeyBoardClicked)
    {
        if (!app->getAsyncKeyState(keyBind))
        {
            wasListTimeKeyBoardClicked = false;
        }
    }

    showControl();
    
    app->setColor(app->systemSettings->TextColor, finalDC, app->systemSettings->MainFont);
    app->drawText(rect- rect.pos, text, finalDC);
    setMbLastTime();
}
