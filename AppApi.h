#pragma once
#include "AbstractApp.h"
#include "FileSavings.h"
#include "LoadLib.h"
#include "HGDIManager.h"

struct PowerPoint* appData = NULL;

struct PowerPoint : AbstractAppData
{
    PowerPoint(HINSTANCE hInstance);
    ~PowerPoint();
};
