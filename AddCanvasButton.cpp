#pragma once
#include "AddCanvasButton.h"
#include "WindowsLibApi.h"

SetCanvasButton* AddCanvasButton::getSetCanvasButton()
{
    return &setCanvasButton;
}

void AddCanvasButton::draw()
{
    app->windowsLibApi->standartWindowDraw(this);
    if (isEnterActive)
    {
        int currentEnterStatus = setCanvasButton.isResultEntered();
        if (currentEnterStatus)
        {
            isEnterActive = false;
            if (currentEnterStatus == 1)
            {
                char* newName = setCanvasButton.getNewCanvasName();
                if (newName[0]) canvasManager->addCanvas(newName, newCanvasSize);
                else            canvasManager->addCanvas("TestName", newCanvasSize);
            }
        }
    }

    if (!isEnterActive && app->getAsyncKeyState(VK_CONTROL) && app->getAsyncKeyState('N'))
    {
        isEnterActive = true;
        setCanvasButton.show();
    }
    setMbLastTime();
}

void AddCanvasButton::onClick(Vector mp)
{
    if (!isClickedLastTime())
    {
        isEnterActive = true;
        setCanvasButton.show();
        strcpy(setCanvasButton.getNewCanvasName(), defaultCanvasName);
    }
    setMbLastTime();
}