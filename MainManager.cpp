#pragma once
#include "MainManager.h"
#include "ZoneSizeControl.cpp"

void MainManager::controlWorkSpace()
{
    if (screenSizeLastTime != app->systemSettings->SizeOfScreen)
    {
        screenChanged();
    }
    screenSizeLastTime = app->systemSettings->SizeOfScreen;

    app->changeWindow(zone.finishPos - zone.pos, zone.pos);
}


void MainManager::screenChanged()
{
    
    
    /*/*
    for (int i = 0; i < getCurLen(); i++)
    {
        if (pointers[i]) pointers[i]->screenChanged();
    }
    */
}



void MainManager::draw()
{
    zone.pos = app->systemSettings->ScreenPos;
    zone.finishPos = app->systemSettings->ScreenPos + app->systemSettings->SizeOfScreen;
    needFrameToWork = !app->isFullScreen();
    //zoneSizeControl.controlFrame();
    app->setColor(RGB(255, 0, 0), finalDC);
    app->rectangle({}, {100, 100}, finalDC);

    controlWorkSpace();
    


    app->windowsLibApi->standartManagerDraw(this);

   // if (app->systemSettings->debugMode >= 1)printf("Active Window: %p\n", isActiveWindowBelow());

    //zoneSizeControl.drawFrame();

    app->bitBlt(finalDC, handle->rect.pos, handle->getSize(), handle->finalDC);

    

    setMbLastTime();
}

void MainManager::onClick(Vector mp)
{
    mousePos = mp;

    app->windowsLibApi->standartManagerOnClick(this, mp);
}

int MainManager::mbDown(Vector mp, int button)
{     
    clicked = button;
    mousePos = mp;
    return app->windowsLibApi->standartManagerMbDown(this, mp, button);
}
int MainManager::mbUp(Vector mp, int button)
{
    clicked = 0;
    mousePos = mp;
    return app->windowsLibApi->standartManagerMbUp(this, mp, button);
}

int MainManager::onSize(Vector managerSize)
{
    rect = { .pos = {}, .finishPos = managerSize };
    //zoneSizeControl.setFrameZones();
    return app->windowsLibApi->standartManagerOnSize(this, managerSize);
}
