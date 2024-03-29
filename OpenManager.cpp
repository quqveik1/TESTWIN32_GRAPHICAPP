#pragma once
#include "OpenManager.h"

void OpenManager::click()
{
    if (mode == 0)
    {
        if(!getOpeningManager())
        {
            dcout << "getOpeningManager() == 0\n";
            return;
        }

        if (getOpeningManager()->needToShow)
        {
            getOpeningManager()->hide();
            app->updateScreen(this);
        }
        else
        {
            getOpeningManager()->show();
            app->updateScreen(this);
        }
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

    click();
    setMbLastTime();
}


int OpenManager::onMouseMove(Vector mp, Vector delta)
{
    return 0;
}

int OpenManager::onKeyboard(int key)
{
    if (app->getKeyState(VK_CONTROL) && app->getKeyState(keyBind) && !wasListTimeKeyBoardClicked)
    {
        click();
        wasListTimeKeyBoardClicked = true;
    }

    if (wasListTimeKeyBoardClicked)
    {
        if (!app->getKeyState(keyBind))
        {
            wasListTimeKeyBoardClicked = false;
        }
    }
    return 0;
}

void OpenManager::draw()
{
    Vector dcREct = getOutputDC()->getSize();
    app->windowsLibApi->standartWindowDraw(this);
    

    

    showControl();
    
    //app->setColor(app->systemSettings->TextColor, finalDC, app->systemSettings->MainFont);
    //app->drawText(rect- rect.pos, text, finalDC);
    setMbLastTime();
}
