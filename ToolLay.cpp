#pragma once
#include "ToolLay.h"

ToolLay::~ToolLay()
{
    delete toolsData;
}

void ToolLay::needRedraw()
{
    lay->needRedraw();
}

Tool* ToolLay::getTool()
{
    return tool;
}

bool ToolLay::isFinished()
{
    if (!getTool()) return false;
    return getTool()->handler(T_ISFINISHED, this);
}

bool ToolLay::isStarted()
{
    if (!getTool()) return false;
    return getTool()->handler(T_ISSTARTED, this);
}

bool ToolLay::useTool(ProgrammeDate* _data)
{
    if (!getTool()) return false;
    data = _data;
    assert(data);
    return getTool()->handler(T_USE, this);
}

HDC ToolLay::drawTool(HDC dc /*= NULL*/)
{
    if (getTool() && isStarted() && needToShow) return (HDC)getTool()->handler(T_LOAD, this);
    return NULL;
}

void ToolLay::editTool(ProgrammeDate* _data)
{
    if (!getTool()) return;
    data = _data;
    assert(data);

    if (needToShow)isEditing = !getTool()->handler(T_EDIT, this);
}


bool ToolLay::isInToolZone(ProgrammeDate* data, Vector mp)
{
    if (toolZone.inRect(mp))
    {
        HDC outDC = lay->lay.outputLay;
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

M_HDC ToolLay::getOutputDC()
{
    if (lay) return lay->getOutputDC();
    else     return {};
}

void ToolLay::setShowMode(int mode)
{
    needToShow = mode;
}


void ToolLay::addTool(Tool* _tool)
{
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
    return;
}
