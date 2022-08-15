#pragma once
#include "SetCanvasButton.h"



int SetCanvasButton::isResultEntered()
{
    if (enterStatus)
    {
        int saveEnterStatus = enterStatus;
        enterStatus = 0;
        return saveEnterStatus;
    }
    return enterStatus;
}

char* SetCanvasButton::getNewCanvasName()
{
    return canvasName;
}

void SetCanvasButton::confirmEnter()
{
    enterStatus = 1;
    canvasManager->addCanvas(getNewCanvasName(), defaultCanvasSize);
    hide();
}

void SetCanvasButton::cancelEnter()
{
    enterStatus = -1;
    hide();
}


void SetCanvasButton::show()
{
    needToShow = true;
    for (int i = 0; i < getCurLen(); i++)
    {
        pointers[i]->show();
    }
    canvasName[0] = {};
    newCanvasSize = defaultCanvasSize;
    strcpy(canvasName, defaultCanvasName);
    MoveWindowTo(app->getCentrizedPos(getSize(), app->systemSettings->SizeOfScreen));
}

void SetCanvasButton::draw()
{
    if (needToShow)
    {
        controlHandle();
        app->setColor(color, finalDC);
        app->rectangle(rect - rect.pos, finalDC);

        handle.print(finalDC);
        app->setColor(TX_BLACK, finalDC);
        app->line({ 0, handle.rect.finishPos.y }, { getSize().x, handle.rect.finishPos.y }, finalDC);
        app->line({ 0, downSectionPosY }, { getSize().x, downSectionPosY }, finalDC);


        sizeX = defaultCanvasSize.x;
        sizeY = defaultCanvasSize.y;
        app->windowsLibApi->standartManagerDraw(this);
        defaultCanvasSize.x = sizeX;
        defaultCanvasSize.y = sizeY;

        app->setColor(app->systemSettings->TextColor, finalDC);
        app->selectFont(app->systemSettings->FONTNAME, oneLineSize.y, finalDC);
        app->drawText(sizeXText, "Ширина:", finalDC, format);
        app->drawText(sizeYText, "Длина:", finalDC, format);

        inputName.print(finalDC);
        app->drawText(nameTextRect, "Имя:", finalDC, format);

        app->setColor(TX_WHITE, finalDC);
        app->rectangle(confirmButton, finalDC);
        app->rectangle(cancelButton, finalDC);
        app->setColor(TX_BLACK, finalDC);
        app->selectFont(app->systemSettings->FONTNAME, buttonSize.y - 5, finalDC);
        app->drawText(confirmButton, "Ок", finalDC);
        app->drawText(cancelButton, "Отмена", finalDC);


        if (app->getAsyncKeyState(VK_RETURN))
        {
            confirmEnter();
        } 
        
        if (app->getAsyncKeyState(VK_ESCAPE))
        {
            cancelEnter();
        }
    }




}

void SetCanvasButton::onClick(Vector mp)
{
    mp = getMousePos();
    if (needToShow)
    {
        int result = -1;
        result = clickHandle();
        if (result < 0) result = app->windowsLibApi->standartManagerOnClick(this, mp);
        if (result < 0)
        {
            if (confirmButton.inRect(mp))
            {
                confirmEnter();
            }   
            
            if (cancelButton.inRect(mp))
            {
                cancelEnter();
            }
        }
    }
}