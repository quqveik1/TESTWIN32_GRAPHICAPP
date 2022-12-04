#pragma once
#include "CLay.h"
#include "Canvas.h"
#include "ToolLay.cpp"
#include "ProgrammeDate.h"
#include "ToolManager.h"


CLay::CLay(AbstractAppData* _app, Canvas* _canvas, Vector _size /* = {}*/) : 
    Manager(_app, { .pos = {}, .finishPos = _size }, _app->systemSettings->ONELAYTOOLSLIMIT),
    canvas(_canvas)

{
    if (_size == _size.getNullVector())
    {
        _size = app->systemSettings->DCVECTORSIZE;
        resize({ .pos = {}, .finishPos = _size });
    }
    lay.setSize(_size, app);
    createToolLay();
}

void CLay::createLay(AbstractAppData* _app, Canvas* _canvas, Vector _size /* = {}*/)
{
    assert(_app);  
    //oneLayToolLimit = app->systemSettings->ONELAYTOOLSLIMIT;
    canvas = _canvas;
    assert(canvas);

    //toolLays = new ToolLay* [app->systemSettings->ONELAYTOOLSLIMIT];


    

    //lay.createLay(app, _size);
    //lay.setSize(_size, app);
    //createToolLay();
}

ToolLay* CLay::createToolLay()
{
    //if (toolLength >= oneLayToolLimit) return NULL;

    ToolLay* newToolLay = new ToolLay(app);
    addToolLay(newToolLay);

    return newToolLay;
}


void CLay::addToolLay(ToolLay* tool)
{
   // assert(toolLength < oneLayToolLimit);

    //toolLength++;
    //activeToolNum = toolLength - 1;
    //toolLays[activeToolNum] = tool;

    bool result = addWindow(tool);
    if (result)
    {
        int _cl = getCurLen();
        activeToolNum = getCurLen() - 1;
        tool->lay = this;
        tool->addTool(app->toolManager->getActiveTool());
    }
    else
    {
        massert("Нельзя добавить новый объект на слой", app);
    }
    
}

void CLay::setActiveLastToolLay()
{
    //activeToolNum = toolLength - 1;
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
    /*
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
    */

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
    int _num = getActiveToolLayNum();
    int _cl = getCurLen();
    if (-1 < _num && _num < _cl)
    {
        return (ToolLay*)pointers[_num];
    }
    return NULL;
   // if (activeToolNum < 0 || !toolLays) return NULL;
    //return toolLays[activeToolNum];
}

ToolLay* CLay::getToolLay(int num)
{
    if (0 <= num && num < getCurrentSize())
    {
        //return toolLays[num];
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
    return getCurLen();
    //return toolLength;
}

M_HDC* CLay::getOutputDC()
{
    return outputDC;
}


RGBQUAD* CLay::getOutputBuf()
{
    return NULL;
}

ToolLay** CLay::getToolLays()
{
    return NULL;
    //return &(toolLays[0]);
}

/*
Lay* CLay::getLay()
{
    return NULL;
}
*/

Vector CLay::getLaySize()
{
    return lay.getSize();

}


int CLay::mbDown(Vector pos, int button)
{
    ToolLay* _activeLay = getActiveToolLay();
    if (_activeLay)
    {
        _activeLay->mbDown(pos, button);
    }
    return 0;
}


void CLay::draw()
{
    int _len = getCurLen();
    for (int i = 0; i < _len; i++)
    {
        if (pointers[i])
        {
            //app->DEBUGsaveImage(lay);
            pointers[i]->draw();
            //app->DEBUGsaveImage(lay);
            printf("");
        }
    }
}

void CLay::print(M_HDC* _dc)
{
    app->setColor(app->systemSettings->BackgroundColor, lay);
    app->rectangle({}, {1000, 1000}, lay);
    outputDC = _dc;
    draw();
}

int CLay::mbUp(Vector pos, int button)
{
    ToolLay* _activeLay = getActiveToolLay();
    if (_activeLay)
    {
        _activeLay->mbUp(pos, button);
    }
    return 0;
}

int CLay::onMouseMove(Vector pos, Vector delta)
{
    ToolLay* _activeLay = getActiveToolLay();
    if (_activeLay)
    {
        _activeLay->onMouseMove(pos, delta);
    }
    return 0;
}

void CLay::redraw()
{
    /*
    lay.clean(lay.lay);
    lay.clean(lay.outputLay);

    for (int toollay = 0; toollay < toolLength; toollay++)
    {
        assert(toolLays[toollay]);

        HDC outDC = toolLays[toollay]->drawTool();
        if (outDC != lay.outputLay && outDC) app->transparentBlt(lay.outputLay, 0, 0, 0, 0, outDC);
    }
    */
}

M_HDC* CLay::getPermanentDC()
{
    return outputDC;
}

RGBQUAD* CLay::getPermanentBuf()
{
    return NULL;
}
