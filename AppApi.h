#pragma once
#include "AbstractApp.h"
#include "FileSavings.h"
#include "LoadLib.h"
#include "HGDIManager.h"

struct PowerPoint : AbstractAppData
{
    
    struct Manager* handle = NULL;
    struct CToolManager* toolManager = NULL;
    struct CanvasManager* canvasManager = NULL;
    struct ConsoleOutput* consoleOutput = NULL;

    Vector sizeHistory[2] = {};

    int lastTimeLButtonClicked = 0;
    bool wasLastTimeLButtonClicked = 0;

    PowerPoint(HINSTANCE hInstance);
    virtual ~PowerPoint();

    void setCanvasManager(CanvasManager* _canvasManager) { canvasManager = _canvasManager; };

    virtual void onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;

};
