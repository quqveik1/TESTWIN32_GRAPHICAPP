#pragma once

#include "AbstractApp.h"
#include "ProgrammeDate.h"
#include "Lay.h"
#include "CLay.h"
#include "MainTools.h"
//#include "DllSettings.h"

struct Tool;
struct ToolLay;


struct ToolData
{
    int byteLength = 0;
    bool isFinished = false;
    bool isStarted = false;

    virtual int getByteSize();
};

int ToolData::getByteSize()
{
    byteLength = sizeof(*this);
    return byteLength;
}

struct ToolZoneSave : ToolData
{
    Vector pos = {};
    Vector size = {};
};



struct ToolSave : ToolZoneSave
{
    COLORREF color = NULL;
    int thickness = NULL;
    const char* name = NULL;

    ToolSave(Vector _pos, Vector _size, COLORREF _color, int _thickness, const char* _name) :
        color(_color),
        thickness(_thickness),
        name(_name)
    {
        pos = _pos;
        size = _size;
    }

    ToolSave() :
        name(NULL)
    {}

};

struct Tool
{
    HDC iconDC = NULL; //ее изображение

    const char* name = NULL;

    Vector startPos = {};
    bool workedLastTime = false;
    const int ToolSaveLen = 0;

    ToolData* toolData = NULL;

    AbstractAppData* app = NULL;
    ToolLay* toolLay = NULL;
    ProgrammeDate* appData = NULL;

    Tool(AbstractAppData* _app, const char* _name, const int _ToolSaveLen, HDC _iconDC = NULL) :
        app(_app),
        name(_name),
        iconDC(_iconDC),
        ToolSaveLen(_ToolSaveLen)
    {}


    bool firstUse(ProgrammeDate* data, void* output, Vector currentPos);
    void finishUse();
    HDC getOutDC();

    virtual HDC getDC();
    virtual const char* getName();
    virtual bool isFinished(ToolLay* data);
    virtual bool isStarted(ToolLay* data) { return ((ToolData*)data->getToolsData())->isStarted; };

    virtual bool use(ProgrammeDate* data, ToolLay* lay, void* output) { return false; };
    virtual HDC load(ToolLay* toollay, HDC dc = NULL) { return NULL; };
    virtual bool edit(ToolLay* toollay, HDC dc = NULL) { return 1; };
};



