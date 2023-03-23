#pragma once
#include "ToolManager.h"
#include "AbstractApp.h"
#include "CanvasManager.h"
#include "AppApi.h"
#include "Tool2.h"

CToolManager::CToolManager(PowerPoint* _app) :
    app(_app)
{
}

CToolManager::~CToolManager()
{
    for (int i = 0; i < currentLength; i++)
    {
        delete tools[i];
    }

    delete[] tools;
}

int CToolManager::addTool(Tool2* tool, bool needToHide/* = false*/)
{
    assert(tool);

    if (needToHide)
    {
        if (currentHidenToolsLength < ToolsLength - 1)
        {
            hidenTools[currentHidenToolsLength] = tool;
            currentHidenToolsLength++;
            return currentHidenToolsLength - 1;
        }
    }
    if (currentLength < ToolsLength - 1)
    {
        tools[currentLength] = tool;
        currentLength++;
        return currentLength - 1;
    }
    return -1;
}

Tool2* CToolManager::getActiveTool()
{

    if (activeToolNum >= currentLength)
    {
        return hidenTools[activeToolNum - currentLength];
    }
    return tools[activeToolNum];
}


int CToolManager::getActiveToolNum()
{
    return activeToolNum;
}


int CToolManager::setActiveToolNum(int num)
{
    if (app->canvasManager->getActiveCanvas())
    {
        if (app->canvasManager->getActiveCanvas()->getEditingMode())
        {
            return 2;
        }
    }

    if (num < currentLength)
    {
        activeToolNum = num;
        return 0;
    }
    return 0;
}

int CToolManager::setActiveTool(Tool2* tool)
{
    for (int i = 0; i < currentLength; i++)
    {
        if (tools[i] == tool)
        {
            activeToolNum = i;
            return i;
        }
    }

    for (int i = 0; i < currentHidenToolsLength; i++)
    {
        if (hidenTools[i] == tool)
        {
            activeToolNum = i + currentLength;
            return i + currentLength;
        }
    }
    return -1;

}