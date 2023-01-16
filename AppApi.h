#pragma once
#include "EngineAppApi.h"
#include "FileSavings.h"
#include "LoadLib.h"
#include "HGDIManager.h"

struct PowerPoint* appData = NULL;

struct PowerPoint : EngineAppApi
{
    PowerPoint(HINSTANCE hInstance);
    ~PowerPoint();
};
