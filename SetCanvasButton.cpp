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
    app->updateScreen();
}

void SetCanvasButton::cancelEnter()
{
    enterStatus = -1;
    hide();
    app->updateScreen();
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
    app->updateScreen();
}

int SetCanvasButton::onKeyboard(int key)
{
    if (needToShow)
    {
        if (app->getKeyState(VK_RETURN))
        {
            confirmEnter();
        }

        if (app->getKeyState(VK_ESCAPE))
        {
            cancelEnter();
        }
    }
    return 0;
}

void SetCanvasButton::draw()
{
    if (needToShow)
    {
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
    }




}

void SetCanvasButton::print(HDC dc)
{
    if (needToShow)
    {
        assert(dc);
        draw();
        app->bitBlt(dc, rect.pos.x, rect.pos.y, rect.getSize().x, rect.getSize().y, finalDC);
    }
}

void SetCanvasButton::onClick(Vector mp)
{
    mp = getMousePos();
    if (needToShow)
    {
        int result = -1;
        result = app->windowsLibApi->standartManagerOnClick(this, mp);
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

int SetCanvasButton::mbDown(Vector mp, int button)
{
    app->windowsLibApi->standartManagerMbDown(this, mp, button);
    return clickHandle();
}

int SetCanvasButton::mbUp(Vector mp, int button)
{
    app->windowsLibApi->standartManagerMbUp(this, mp, button);
    return mbUpHandle();
}

int SetCanvasButton::onMouseMove(Vector mp, Vector delta)
{
    app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);
    moveHandle(delta);
    return 0;
}