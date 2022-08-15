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
    zoneSizeControl.controlFrame();

    controlWorkSpace();
    


    app->windowsLibApi->standartManagerDraw(this);

    if (app->systemSettings->debugMode >= 1)printf("Active Window: %p\n", isActiveWindowBelow());

    //zoneSizeControl.drawFrame();

    app->bitBlt(finalDC, handle->rect.pos, handle->getSize(), handle->finalDC);

    

    setMbLastTime();
}

void MainManager::onClick(Vector mp)
{

    if (zoneSizeControl.clickFrame()) return;

    app->windowsLibApi->standartManagerOnClick(this, mp);
}

int MainManager::onSize(Vector managerSize)
{
    rect = { .pos = {}, .finishPos = managerSize };
    //zoneSizeControl.setFrameZones();
    return app->windowsLibApi->standartManagerOnSize(this, managerSize);
}
