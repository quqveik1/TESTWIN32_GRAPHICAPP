#pragma once
#include "CLay.h"
#include "Canvas.h"
#include "ToolLay.cpp"
#include "ProgrammeDate.h"
#include "ToolManager.h"

CLay::~CLay()
{
    if (toolLays) delete[] toolLays;
}

void CLay::createLay(AbstractAppData* _app, Canvas* _canvas, Vector _size /* = {}*/)
{
    assert(_app);
    app = _app;   
    oneLayToolLimit = app->systemSettings->ONELAYTOOLSLIMIT;
    canvas = _canvas;
    assert(canvas);

    toolLays = new ToolLay* [app->systemSettings->ONELAYTOOLSLIMIT];


    if (_size == _size.getNullVector()) _size = app->systemSettings->DCVECTORSIZE;

    lay.createLay(app, _size);
    createToolLay();
}

ToolLay* CLay::createToolLay()
{
    if (toolLength >= oneLayToolLimit) return NULL;

    ToolLay* newToolLay = new ToolLay();
    addToolLay(newToolLay);

    return newToolLay;
}


void CLay::addToolLay(ToolLay* tool)
{
    assert(toolLength < oneLayToolLimit);

    toolLength++;
    activeToolNum = toolLength - 1;
    toolLays[activeToolNum] = tool;
    tool->lay = this;
    tool->addTool(app->toolManager->getActiveTool());
}

void CLay::setActiveLastToolLay()
{
    activeToolNum = toolLength - 1;
}

void CLay::needRedraw()
{
    needToRedraw = true;
} 

void CLay::editTool(ProgrammeDate* _data)
{
    if (getActiveToolLay() && getActiveToolLay()->getTool())
    {
        getActiveToolLay()->editTool(_data);
    }
}

void CLay::controlTool(ProgrammeDate* _data)
{
    ToolLay* activeToolLay = getActiveToolLay();

    int isFinished = activeToolLay->isFinished();

    if (!isFinished)
    {
        int drawingMode = app->toolManager->getActiveToolNum();
        if (DrawingModeLastTime != drawingMode)
        {
            activeToolLay->addTool(app->toolManager->getActiveTool());
        }

        int needToFinish = activeToolLay->useTool(_data);
        if (needToFinish)
        {
            createToolLay();
        }
    }
    DrawingModeLastTime = app->toolManager->getActiveToolNum();

}


void CLay::noMoreRedraw()
{
    needToRedraw = false;
}  

bool CLay::redrawStatus()
{
    if  (needToRedraw) return true;
    else               return false;
}


ToolLay* CLay::getActiveToolLay()
{
    if (activeToolNum < 0 || !toolLays) return NULL;
    return toolLays[activeToolNum];
}

ToolLay* CLay::getToolLay(int num)
{
    if (0 <= num && num < getCurrentSize())
    {
        return toolLays[num];
    }
    return NULL;
}

int CLay::getActiveToolLayNum()                                                                                                                             
{
    return activeToolNum;
}

void CLay::setActiveToolLayNum(int num)
{
    activeToolNum = num;
    needRedraw();
}

int CLay::getCurrentSize()
{
    return toolLength;
}

M_HDC CLay::getOutputDC()
{
    return lay.outputLay;
}


RGBQUAD* CLay::getOutputBuf()
{
    return lay.outputBuf;
}

ToolLay** CLay::getToolLays()
{
    return &(toolLays[0]);
}

Lay* CLay::getLay()
{
    return &lay;
}

Vector CLay::getLaySize()
{
    return lay.laySize;
}

void CLay::redraw()
{
    lay.clean(lay.lay);
    lay.clean(lay.outputLay);

    for (int toollay = 0; toollay < toolLength; toollay++)
    {
        assert(toolLays[toollay]);

        HDC outDC = toolLays[toollay]->drawTool();
        if (outDC != lay.outputLay && outDC) app->transparentBlt(lay.outputLay, 0, 0, 0, 0, outDC);
    }
}

M_HDC CLay::getPermanentDC()
{
    return lay.lay;
}

RGBQUAD* CLay::getPermanentBuf()
{
    return lay.layBuf;
}
