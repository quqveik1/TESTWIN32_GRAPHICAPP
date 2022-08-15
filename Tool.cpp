#pragma once
#include "Tool.h"




long Tool::handler(TOOLMESSAGE message, ToolLay* lay)
{
    return defaultHandler(message, lay);
}

long Tool::defaultHandler(TOOLMESSAGE message, ToolLay* lay)
{
    //Пример обработчика сигналов. Ответ на эти сообщения ОБЯЗАТЕЛЬНЫЙ. Иначе будет происходить кринж с программой.
    if (message == T_USE)
    {
        return use(lay);
    }
    if (message == T_LOAD)
    {
        return (long)load(lay);
    }
    if (message == T_EDIT)
    {
        return edit(lay);
    }


    if (message == T_ISFINISHED)
    {
        return isFinished(lay);
    }

    if (message == T_ISSTARTED)
    {
        return isStarted(lay);
    }



    if (message == T_GETNAME)
    {
        return (int)getName();
    }
    if (message == T_GETICONDC)
    {
        return (int)getIconDC();
    }


    if (message == T_CREATE)
    {
        return defaultCreate(lay);
    }

    if (message == T_DESTROY)
    {
        return destroy(lay);
    }

    return NOTHINGHAPPENEDAFTERMESSAGE;


}

long Tool::defaultCreate(ToolLay* lay)
{
    char*& data = lay->getToolsData();

    data = new char[ToolSaveLen] {};

    return (long)data;
}


bool Tool::firstUse(ProgrammeDate* data, void* output, Vector currentPos)
{
    assert(data && output);
    if (!workedLastTime)
    {
        workedLastTime = true;
        startPos = currentPos;
        return true;
    }
    return false;
}

void Tool::finishUse()
{
    workedLastTime = false;
}

HDC Tool::getOutDC()
{
        if (isFinished(toolLay)) return toolLay->lay->getPermanentDC();
        else                     return toolLay->lay->getOutputDC();
}


bool Tool::isFinished(ToolLay* data) 
{ 
    return ((ToolData*)data->getToolsData())->isFinished;
};

long Tool::destroy(ToolLay* toollay)
{
    toolLay = toollay;
    if (toolLay)
    {
        void* data = toolLay->getToolsData();
        if (data)
        {
            delete[] data;
            return 0;
        }
    }

    return (int)"ERROR";
}

HDC Tool::getIconDC()
{
    return iconDC;
}


const char* Tool::getName()
{
    return name;
}



