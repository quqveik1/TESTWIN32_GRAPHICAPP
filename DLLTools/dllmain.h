#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "DLLSettings.h"
#include "..\AbstractApp.h"
#include "ToolExportData.cpp"
#include "..\M_HGDIOBJ.cpp"
//#include "CadreResizingTool.h"
#include "..\Tool2.h"

extern "C" __declspec (dllexport) DLLToolExportData* initDLL(struct AbstractAppData* data);

//struct AbstractAppData* appData = NULL;
ÑDllSettings DllSettings;

struct Line : Tool2
{
    Line(AbstractAppData* _data, ÑDllSettings* _dllSettings, const char* _name, const int _ToolSaveLen, HDC _dc) :
        Tool2 (_data, _name)
    {}




};

/*
struct Tool4Squares : CadreResizingTool
{
    ToolSave* saveTool = NULL;



    Tool4Squares(ÑDllSettings* _dllSettings, const char* _name, const int _ToolSaveLen, HDC _dc, AbstractAppData* _data) :
        CadreResizingTool(_dllSettings, _name, _ToolSaveLen, _dc, _data)
    {
    }

    virtual void outputFunc(HDC outdc) = NULL;


    virtual ToolSave* getToolData() { return (ToolSave*)toolLay->getToolsData(); };

    virtual bool use(ProgrammeDate* data, ToolLay* lay, void* output) override;
    virtual HDC load(ToolLay* toollay, HDC dc = NULL) override;
};


struct Line : Tool4Squares
{

    const int controlSquareLength = 4;
    Rect* controlSquare = new Rect[controlSquareLength]{};
    Vector controlSquareSize = { 10, 10 };
    Vector deltaForButtons = {};
    int activeControlSquareNum = -1;
    bool draggedLastTime = false;
    Vector lastTimeMP = {};

    Line(ÑDllSettings* _dllSettings, const char* _name, const int _ToolSaveLen, HDC _dc, AbstractAppData* _data) :
        Tool4Squares(_dllSettings, _name, _ToolSaveLen, _dc, _data)
    {
    }


    virtual void outputFunc(HDC outdc);

    ToolSave* getToolData() { return (ToolSave*)toolLay->getToolsData(); };

};
*/