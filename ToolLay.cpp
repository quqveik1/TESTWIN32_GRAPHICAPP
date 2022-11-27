#pragma once
#include "ToolLay.h"
#include "Clay.h"
#include "WindowsLib.cpp"

ToolLay::~ToolLay()
{
    delete toolsData;
}


ToolLay::ToolLay(AbstractAppData* _app) :
    Manager(_app, {}, 1)
{
}

void ToolLay::needRedraw()
{
    lay->needRedraw();
}

Tool2* ToolLay::getTool()
{
    return tool;
}


int ToolLay::finishThisTool()
{
    if (lay)
    {
        lay->createToolLay();
        return 1;
    }
    return 0;
}

bool ToolLay::isFinished()
{
    return NULL;
    //if (!getTool()) return false;
    //return getTool()->handler(T_ISFINISHED, this);
}

bool ToolLay::isStarted()
{
    return NULL;
    //if (!getTool()) return false;
    //return getTool()->handler(T_ISSTARTED, this);
}

bool ToolLay::useTool(ProgrammeDate* _data)
{
    return NULL;
    /*
    if (!getTool()) return false;
    data = _data;
    assert(data);
    return getTool()->handler(T_USE, this);
    */
}

HDC ToolLay::drawTool(HDC dc /*= NULL*/)
{
    return NULL;
    /*
    if (getTool() && isStarted() && needToShow) return (HDC)getTool()->handler(T_LOAD, this);
    return NULL;
    */
}

void ToolLay::editTool(ProgrammeDate* _data)
{
    return;

    /*
    if (!getTool()) return;
    data = _data;
    assert(data);

    if (needToShow)isEditing = !getTool()->handler(T_EDIT, this);
    */
}

void ToolLay::draw()
{
    Tool2* _tool = getTool();
    if (_tool)
    {
        ToolLay* _prevLay = _tool->selectToolLay(this);
        _tool->draw();
    }
}



int ToolLay::mbDown(Vector pos, int button)
{
    Tool2* _tool = getTool();
    if (_tool)
    {
        ToolLay* _prevLay = _tool->selectToolLay(this);
        _tool->mbDown(pos, button);
    }
    return 0;
}

int ToolLay::mbUp(Vector pos, int button)
{
    Tool2* _tool = getTool();
    if (_tool)
    {
        ToolLay* _prevLay = _tool->selectToolLay(this);
        _tool->mbUp(pos, button);
    }
    return 0;
}

int ToolLay::onMouseMove(Vector pos, Vector delta)
{

    Tool2* _tool = getTool();
    if (_tool)
    {
        ToolLay* _prevLay = _tool->selectToolLay(this);
        _tool->onMouseMove(pos, delta);
    }
    return 0;
}

bool ToolLay::isInToolZone(ProgrammeDate* data, Vector mp)
{
    if (toolZone.inRect(mp))
    {
        //HDC outDC = lay->lay.outputLay;
        if (!getTool()) return false;
        //getTool()->setMBCondition(mbCondition);
        //isEditing = !tool->edit(this, outDC);
        return true;
    }
    return false;
}

ProgrammeDate* ToolLay::getProgDate()
{
    return data;
}

int ToolLay::setProgDate(ProgrammeDate* _data)
{
    data = _data;
    return NULL;
}


char*& ToolLay::getToolsData()
{
    return toolsData;
}

M_HDC ToolLay::getPermanentDC()
{
    if (lay) return lay->getPermanentDC();
    else     return {};
} 

M_HDC* ToolLay::getOutputDC()
{
    if (lay) return lay->getOutputDC();
    else     return NULL;
}

void ToolLay::setShowMode(int mode)
{
    needToShow = mode;
}


void ToolLay::addTool(Tool2* _tool)
{
    if (_tool)
    {
        tool = _tool;
        tool->createNewToolCopy(this);
    }
    /*
    if (tool != _tool)
    {
        if (tool)
        {
            tool->handler (T_DESTROY, this);
        }
    }
    tool = _tool;
    if (tool)
    {
        tool->handler(T_CREATE, this);
    }
    */
    return;
}
