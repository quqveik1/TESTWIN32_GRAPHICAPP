#pragma once
#include "MainManager.h"
#include "ZoneSizeControl.cpp"
#include "ManagerHandle.cpp"

void MainManager::controlWorkSpace()
{
    if (screenSizeLastTime != app->systemSettings->SizeOfScreen)
    {
        screenChanged();
    }
    screenSizeLastTime = app->systemSettings->SizeOfScreen;

    app->changeWindow(zone.finishPos - zone.pos, zone.pos);
}


void MainManager::draw()
{
    zone.pos = app->systemSettings->ScreenPos;
    zone.finishPos = app->systemSettings->ScreenPos + app->systemSettings->SizeOfScreen;
    needFrameToWork = !app->isFullScreen();
    //zoneSizeControl.controlFrame();

    //controlWorkSpace();
    app->setColor(C_RED, *getOutputDC());
    app->rectangle({}, { 1000, 1000 }, *getOutputDC());
   

    ManagerHandle::draw();

    
    


    //app->windowsLibApi->standartManagerDraw(this);

   // if (app->systemSettings->debugMode >= 1)printf("Active Window: %p\n", isActiveWindowBelow());

    //zoneSizeControl.drawFrame();

   //app->bitBlt(finalDC, handle->rect.pos, handle->getSize(), handle->finalDC);

    

   // setMbLastTime();
}

void MainManager::onClick(Vector mp)
{
    mousePos = mp;

    //if (handle.rect)
    ManagerHandle::onClick(mp);
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

int MainManager::onSize(Vector managerSize, Rect newRect)
{
    rect = { .pos = {}, .finishPos = managerSize };
    //zoneSizeControl.setFrameZones();
    return ManagerHandle::onSize(managerSize, newRect);
}
