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
    bool filesCompability = true;

    PowerPoint(HINSTANCE hInstance);
    ~PowerPoint();


    int needToLoadOldFiles();

};
