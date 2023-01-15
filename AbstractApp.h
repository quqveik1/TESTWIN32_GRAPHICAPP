#pragma once
#include "App.h"
using namespace std;


struct AbstractAppData : App
{

    bool filesCompability = true;

    
    struct CToolManager* toolManager = NULL;
    struct CFileSavings* fileSavings = NULL;
    struct CanvasManager* canvasManager = NULL;
    struct ConsoleOutput* consoleOutput = NULL;

    
};