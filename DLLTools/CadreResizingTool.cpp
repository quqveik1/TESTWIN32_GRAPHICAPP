#pragma once
#include "CadreResizingTool.h"


bool CadreResizingTool::edit(ToolLay* toollay, HDC dc/* = NULL*/)
{
    assert(toollay);
    if (app->systemSettings->debugMode >= 5) printf("Tool getMBCondition(): %d\n", appData->clickedMB);
    if (app->systemSettings->debugMode >= 5) printf("Toolzone pos: {%lf, %lf}\n", toolLay->toolZone.pos.x, toolLay->toolZone.pos.y);
    toolLay = toollay;
    ToolZoneSave* toolDate = (ToolZoneSave*)toolLay->getToolsData();
    countDeltaForControlButtons();
    countToolZone();
    setControlSquares();
    controlMoving();

    app->drawCadre(toolLay->toolZone, dc, cadreColor, 2);
    
    app->setColor(cadreColor, dc);
    for (int i = 0; i < controlSquareLength; i++)
    {
        Rect drawRect = controlSquare[i] + toollay->toolZone.pos;
        app->rectangle(drawRect, dc);
    }

    return false;
}


void CadreResizingTool::countDeltaForControlButtons()
{
    int isSizePositivX = (toolLay->toolZone.getSize().x > 0);
    int isSizePositivY = (toolLay->toolZone.getSize().y > 0);
    deltaForControlButtons = { (!isSizePositivX) * ((-controlSquareSize.x) * 2) + controlSquareSize.x, (!isSizePositivY) * ((-controlSquareSize.y) * 2) + controlSquareSize.y };
}

void CadreResizingTool::countToolZone()
{
    ToolSave* toolDate = (ToolSave*)toolLay->getToolsData();
    toolLay->toolZone.pos = toolDate->pos - deltaForControlButtons;
    Vector finishPos = toolDate->size + toolDate->pos;
    toolLay->toolZone.finishPos = finishPos + deltaForControlButtons;
}


void CadreResizingTool::drawControlButtons(HDC outDC)
{
    for (int i = 0; i < controlSquareLength; i++)
    {
        Rect drawRect = controlSquare[i] + toolLay->toolZone.pos;
        app->rectangle(drawRect, outDC);
    }
}


void CadreResizingTool::setControlSquares()
{
    Vector size = toolLay->toolZone.getSize();
    controlSquare[0] = { .pos = {0, 0}, .finishPos = deltaForControlButtons };
    controlSquare[1] = { .pos = {toolLay->toolZone.getSize().x - deltaForControlButtons.x, 0}, .finishPos = {toolLay->toolZone.getSize().x, deltaForControlButtons.y} };
    controlSquare[2] = { .pos = toolLay->toolZone.getSize() - deltaForControlButtons, .finishPos = toolLay->toolZone.getSize() };
    controlSquare[3] = { .pos = {0, toolLay->toolZone.getSize().y - deltaForControlButtons.y}, .finishPos = {deltaForControlButtons.x, toolLay->toolZone.getSize().y} };
}



void CadreResizingTool::controlMoving()
{
    controlLeftButton();
    controlRightButton();

    lastTimeMP = appData->getMousePos();
}


void CadreResizingTool::controlLeftButton()
{
    ToolZoneSave* toolDate = (ToolZoneSave*)toolLay->getToolsData();

    if (appData->clickedMB == 1 && activeControlSquareNum < 0)
    {
        Vector mp = appData->getMousePos() - toolLay->toolZone.pos;
        for (int i = 0; i < controlSquareLength; i++)
        {
            if (controlSquare[i].inRect(mp))
            {
                activeControlSquareNum = i;
            }
        }
    }

    if (activeControlSquareNum >= 0)
    {
        toolLay->needRedraw();
        Vector deltaMP = appData->getMousePos() - lastTimeMP;
        if (activeControlSquareNum == 0)
        {
            toolLay->toolZone.pos += deltaMP;
            toolLay->toolZone.finishPos -= deltaMP;
            toolDate->pos += deltaMP;
            toolDate->size -= deltaMP;
        }

        if (activeControlSquareNum == 1)
        {
            toolLay->toolZone.pos.y += deltaMP.y;
            toolDate->pos.y += deltaMP.y;
            toolDate->size.y -= deltaMP.y;
            toolLay->toolZone.finishPos.x += deltaMP.x;
            toolDate->size.x += deltaMP.x;
        }

        if (activeControlSquareNum == 2)
        {
            toolLay->toolZone.finishPos += deltaMP;
            toolDate->size += deltaMP;
        }

        if (activeControlSquareNum == 3)
        {
            toolLay->toolZone.pos.x += deltaMP.x;
            toolDate->pos.x += deltaMP.x;
            toolDate->size.x -= deltaMP.x;
            toolLay->toolZone.finishPos.y += deltaMP.y;
            toolDate->size.y += deltaMP.y;
        }

    }

    if (appData->clickedMB != 1 && activeControlSquareNum >= 0)
    {
        activeControlSquareNum = -1;
        toolLay->needRedraw();
    }

}


void CadreResizingTool::controlRightButton()
{
    ToolZoneSave* toolDate = (ToolZoneSave*)toolLay->getToolsData();
    assert(appData);
    if (appData->clickedMB == 2)
    {
        draggedLastTime = true;
        toolLay->needRedraw();
    }

    if (draggedLastTime)
    {
        toolLay->toolZone.pos += appData->getMousePos() - lastTimeMP;

        toolDate->pos += appData->getMousePos() - lastTimeMP;

        if (app->systemSettings->debugMode > 0) printf("toolZone: {%lf, %lf}\n", toolLay->toolZone.pos.x, toolLay->toolZone.pos.y);
    }

    if (appData->clickedMB != 2 && draggedLastTime)
    {
        draggedLastTime = false;
        toolLay->needRedraw();
    }

}