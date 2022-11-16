#pragma once
#include "ImportTool.h"
/*

long ImportTool::use(ToolLay* lay)
{
    appData = lay->getProgDate();
    toolLay = lay;
    assert(appData && lay);
    toolData = (ToolData*)toolLay->getToolsData();
    SaveCopyDC* saveCopyDC = (SaveCopyDC*)toolData;
    assert(toolData);

    Canvas* canvas = app->canvasManager->getActiveCanvas();
    if (!canvas) return 0;
    HDC importDC = canvas->getCurrentlyImportingImage();
    
    assert(importDC);
    Vector size = app->getHDCSize(importDC);

    saveCopyDC->dc = app->createDIBSection(size);

    app->bitBlt(saveCopyDC->dc, {}, {}, importDC);

    saveCopyDC->isStarted = true;
    saveCopyDC->isFinished = true;
    saveCopyDC->pos = {};
    saveCopyDC->size = app->getHDCSize(saveCopyDC->dc);
    saveCopyDC->startSize = saveCopyDC->size;
    saveCopyDC->selectedZone = false;
    toolLay->needRedraw();
    countToolZone();
    return 1;
}
*/