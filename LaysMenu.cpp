#pragma once
#include "LaysMenu.h"


void LaysMenu::onClick(Vector mp)
{
    if (needToShow)
    {
        if (needToShow && !isClickedLastTime())
        {
            clickHandle();

            if (canvasManager->getActiveCanvas() != NULL)
            {
                for (int i = 0; i < (canvasManager->getActiveCanvas())->currentLayersLength; i++)
                {
                    Rect button = { .pos = {(double)i, handle.rect.getSize().y + i * sectionHeight}, .finishPos = {rect.getSize().x, handle.rect.getSize().y + (i + 1) * sectionHeight} };
                    if (button.inRect(mp))
                    {
                        canvasManager->getActiveCanvas()->activeLayNum = i;
                    }
                }

                Rect addLayButton = { .pos = {0, rect.getSize().y - buttonSize.y}, .finishPos = {rect.getSize().x,  rect.getSize().y} };
                if (addLayButton.inRect(mp) && canvasManager->getActiveCanvas())
                {
                    needToCreateLay = true;
                }
            }
        }
    }
}

void LaysMenu::draw()
{
    app->setColor(color, finalDC);
    app->rectangle(0, 0, app->systemSettings->DCMAXSIZE, app->systemSettings->DCMAXSIZE, finalDC);
    char text[30] = {};

    handle.print(finalDC);
    controlHandle();

    if (needToCreateLay)
    {
        assert(canvasManager);
        if (canvasManager->getActiveCanvas())
        {
            canvasManager->getActiveCanvas()->createLay();
        }
        else
        {
            txMessageBox("Нет активного холста, на который можно добавить слой", "Ошибка", MB_OK);
        }
        needToCreateLay = false;
    }

    rect.finishPos.y = handle.rect.getSize().y + rect.pos.y;
    if (canvasManager->getActiveCanvas())
    {
        rect.finishPos.y = handle.rect.getSize().y + rect.pos.y + sectionHeight * canvasManager->getActiveCanvas()->currentLayersLength + buttonSize.y;

        for (int i = 0; i < (canvasManager->getActiveCanvas())->currentLayersLength; i++)
        {

            sprintf(text, "Слой %d", i + 1);

            app->setAlign(TA_CENTER, finalDC);
            app->setColor(app->systemSettings->TextColor, finalDC);
            app->selectFont(app->systemSettings->FONTNAME, sectionFont, finalDC);

            app->drawText(sideThickness, sideThickness + handle.rect.getSize().y + sectionHeight * i, rect.getSize().x, handle.rect.getSize().y + sectionHeight * (i + 1), text, finalDC);
            app->setColor(app->systemSettings->BackgroundColor, finalDC);
            app->line(0, handle.rect.getSize().y + sectionHeight * (i), rect.getSize().x, handle.rect.getSize().y + sectionHeight * (i), finalDC);
            if (canvasManager->getActiveCanvas()->getActiveLayNum() == i)
            {
                app->drawCadre({ .pos = {0, handle.rect.getSize().y + sectionHeight * (i)}, .finishPos = {rect.getSize().x, handle.rect.getSize().y + sectionHeight * (i + 1)} }, finalDC, TX_WHITE, 2);
            }
        }    
        Vector centrizedAddButtonPos = app->getCentrizedPos(buttonSize, rect.getSize());
        app->bitBlt(finalDC, centrizedAddButtonPos.x, rect.getSize().y - buttonSize.y, 0, 0, addNewLayButton);
        app->setColor(app->systemSettings->BackgroundColor, finalDC);
        app->line(0, rect.getSize().y - buttonSize.y, rect.getSize().x, rect.getSize().y - buttonSize.y, finalDC);
    }
    setMbLastTime();
}
