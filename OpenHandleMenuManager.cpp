#pragma once
#include "OpenHandleMenuManager.h"


void OpenHandleMenuManager::showControl()
{       
    if (app->systemSettings->debugMode >= 5)printf("openManager->isActiveWindowBelow(): %p\n", openingManager->isActiveWindowBelow());
    if (getActiveWindow() != openingManager->isActiveWindowBelow() && getActiveWindow() != this)
    {
        openingManager->needToShow = false;
    }
}