#pragma once
#include "ToolsMenus.h"
#include "ToolManager.h"

void ToolsPalette::drawOneLine(int lineNum)
{
    pointers[lineNum]->draw();
    //app->drawOnScreen (pointers[lineNum]->dc);
    if (pointers[lineNum]->needToShow) app->bitBlt(finalDC, pointers[lineNum]->rect.pos.x, pointers[lineNum]->rect.pos.y + handle.rect.finishPos.y, pointers[lineNum]->rect.finishPos.x, pointers[lineNum]->rect.finishPos.y, pointers[lineNum]->finalDC);

    app->setColor(TX_BLACK, finalDC);
    app->line(0, pointers[lineNum]->rect.pos.y + handle.rect.getSize().y, rect.getSize().x, pointers[lineNum]->rect.pos.y + handle.rect.getSize().y, finalDC);

    if (app->toolManager->getActiveToolNum() == lineNum)
    {
        Rect trueRect = pointers[lineNum]->rect + Vector({0, handle.rect.finishPos.y});
        app->drawCadre(trueRect, finalDC, TX_WHITE, 2);
    }
}

int ToolsPalette::onClickLine(Vector mp)
{
    for (int lineNum = currentSize - 1; lineNum >= 0; lineNum--)
    {

        bool missClicked = false;
        if (pointers[lineNum]->rect.inRect(mp.x, mp.y))
        {
            setActiveWindow(pointers[lineNum]);
            clickButton(pointers[lineNum], this, mp);

            app->toolManager->setActiveToolNum(lineNum);

            lastSelected = lineNum;

            missClicked = false;

            if (pointers[lineNum]->needToShow) return missClicked + 2;
        }
        else
        {
            missClicked = true;
        }


    }
    return  1;
}

void ToolMenu::onUpdate()
{
    Canvas* activeCanvas = canvasManager->getActiveCanvas();

    if (activeCanvas && activeCanvas->getActiveLay()) currentSize = activeCanvas->getCurrentToolLengthOnActiveLay() + 1;
    else                                              currentSize = 0;

    rect.finishPos.y = currentSize * app->systemSettings->BUTTONHEIGHT + handle.rect.finishPos.y + rect.pos.y;
}

Rect ToolMenu::getLineRect(int numberOfLine)
{
    int linePosY = lround(app->systemSettings->BUTTONHEIGHT * numberOfLine + handle.rect.finishPos.y);
    int lineFinishPosY = lround(app->systemSettings->BUTTONHEIGHT * (numberOfLine + 1) + handle.rect.finishPos.y);
    Rect lineRect = { .pos = {0, (double)linePosY}, .finishPos = {getSize().x, (double)lineFinishPosY} };
    return lineRect;
}

Rect ToolMenu::getEyeRect(Rect lineRect)
{
    double eyeCentrizedPosInSectionX = app->getCentrizedPos(realEyeSize, eyeSize).x + lineRect.finishPos.x - eyeSize.x;
    double eyeCentrizedPosInSectionY = app->getCentrizedPos(realEyeSize, lineRect.getSize()).y + lineRect.pos.y;
    
    Vector eyeCentrizedPosInSection = { eyeCentrizedPosInSectionX, eyeCentrizedPosInSectionY };

    Rect result = { .pos = eyeCentrizedPosInSection, .finishPos = {eyeCentrizedPosInSection + realEyeSize } };

    return result;
}



void ToolMenu::drawOneLine(int lineNum)
{
    if (!canvasManager->getActiveCanvas()) return;

    const char* nameOfTool = NULL;
    HDC toolDC = NULL;
    CLay* lay = canvasManager->getActiveCanvas()->getActiveLay();
    if (!lay) return;

    bool needToDrawEye = true;

    int notStartedNum = canvasManager->getActiveCanvas()->getLastNotStartedToolNum();
    if (lineNum == notStartedNum)
    {
        nameOfTool = "Новый инструмент";
        toolDC = emptyToolDC;
        needToDrawEye = false;
    }
    else
    {
        Tool2* tool = lay->getToolLays()[lineNum]->getTool();

        assert(tool);

        //toolDC = tool->getIconDC();
        //nameOfTool = tool->getName();
    }

    lastSelected = lay->getActiveToolLayNum();


    char outputText[MAX_PATH] = {};
    sprintf(outputText, "%d - %s", lineNum + 1, nameOfTool);

    
    Rect lineRect = getLineRect(lineNum);
    int linePosY = std::lround (lineRect.pos.y);
    int lineFinishPosY = std::lround(lineRect.finishPos.y);

    app->bitBlt(finalDC, 0, linePosY, app->systemSettings->BUTTONWIDTH, linePosY + app->systemSettings->BUTTONHEIGHT, toolDC);
    app->setColor(app->systemSettings->MenuColor, finalDC);
    app->rectangle(app->systemSettings->BUTTONWIDTH, linePosY, rect.getSize().x, linePosY + app->systemSettings->BUTTONHEIGHT, finalDC);

    app->setColor(app->systemSettings->TextColor, finalDC);
    app->drawText(app->systemSettings->BUTTONWIDTH, linePosY, rect.getSize().x - eyeSize.x, linePosY + app->systemSettings->BUTTONHEIGHT, outputText, finalDC, app->systemSettings->TEXTFORMAT);

    Rect eyeRect = getEyeRect(lineRect);
    if (needToDrawEye)
    {
        ToolLay* toollay = lay->getToolLay(lineNum);
        if (toollay)
        {
            app->transparentBlt(finalDC, eyeRect.pos, {}, eye);
            if (!toollay->needToShow)
            {
                app->setColor(hideColor, finalDC, 4);
                app->line(eyeRect.pos, eyeRect.finishPos, finalDC);
                app->line(eyeRect.pos.x, eyeRect.finishPos.y, eyeRect.finishPos.x, eyeRect.pos.y, finalDC);
            }
        }
        
    }

    app->setColor(TX_BLACK, finalDC);
    app->line(0, linePosY, rect.getSize().x, linePosY, finalDC);

    if (lastSelected == lineNum)
    {
        app->drawCadre(lineRect, finalDC, TX_WHITE, 2);
    }
    setMbLastTime();
}


int ToolMenu::onClickLine(Vector mp)
{
    double my = mp.y;
    //int my = mp.y;

    int buttonNum = floor(my / app->systemSettings->BUTTONHEIGHT);


    if (!(buttonNum >= 0 && buttonNum <= currentSize))  return 0;

    Rect eyeRect = getEyeRect(getLineRect(buttonNum));

    if (canvasManager->getActiveCanvas())
    {
        Vector absPos = { mp.x, mp.y + handle.rect.finishPos.y };
        if (eyeRect.inRect(absPos) && buttonNum != currentSize - 1)
        {
            if (canvasManager->getActiveCanvas()->getActiveLay())
            {
                ToolLay* toolLay = canvasManager->getActiveCanvas()->getActiveLay()->getToolLay(buttonNum);
                if (toolLay && !isClickedLastTime())
                {                        
                    int newMode = toolLay->needToShow;
                    toolLay->setShowMode(!newMode);
                    canvasManager->getActiveCanvas()->getActiveLay()->needRedraw();
                }
                return 1;
            }
        }

        canvasManager->getActiveCanvas()->setActiveToolLayNum(buttonNum);
    }

    return 1;
}

