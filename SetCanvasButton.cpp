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
    app->updateScreen(this);
}

void SetCanvasButton::cancelEnter()
{
    enterStatus = -1;
    hide();
    app->updateScreen(this);
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
    app->updateScreen(this);
}

int SetCanvasButton::onKeyboard(int key)
{
    app->windowsLibApi->standartManagerOnKeyboard(this, key);
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


        sizeX = (int)defaultCanvasSize.x;
        sizeY = (int)defaultCanvasSize.y;
        app->windowsLibApi->standartManagerDraw(this);
        defaultCanvasSize.x = sizeX;
        defaultCanvasSize.y = sizeY;

        app->setColor(app->systemSettings->TextColor, finalDC);
        app->selectFont(app->systemSettings->FONTNAME, (int)oneLineSize.y, finalDC);
        app->drawText(sizeXText, "Ширина:", finalDC, format);
        app->drawText(sizeYText, "Длина:", finalDC, format);

        inputName.print(finalDC);
        app->drawText(nameTextRect, "Имя:", finalDC, format);

        app->setColor(TX_WHITE, finalDC);
        app->rectangle(confirmButton, finalDC);
        app->rectangle(cancelButton, finalDC);
        app->setColor(TX_BLACK, finalDC);
        app->selectFont(app->systemSettings->FONTNAME, (int)buttonSize.y - 5, finalDC);
        app->drawText(confirmButton, "Ок", finalDC);
        app->drawText(cancelButton, "Отмена", finalDC); 
    }




}

void SetCanvasButton::print(M_HDC& dc)
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
    
    int _val = app->windowsLibApi->standartManagerMbDown(this, mp, button);
    clickHandle();
    return _val;
}

int SetCanvasButton::mbUp(Vector mp, int button)
{
    app->windowsLibApi->standartManagerMbUp(this, mp, button);
    if (button == 1) mbUpHandle();
    return 0;
}

int SetCanvasButton::onMouseMove(Vector mp, Vector delta)
{
    app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);
    moveHandle(delta);
    return 0;
}