#pragma once

#include "Layout.h"


void Layout::print(M_HDC& _finalDC)
{
    setOutputDC(&_finalDC);
    Vector startViewPort = getOutputDC()->getViewPort(app);
    getOutputDC()->moveViewPort(rect.pos, app);
    Vector viewAfter = getOutputDC()->getViewPort(app);
    draw();
    getOutputDC()->moveViewPort(-rect.pos, app);
    //setOutputDC(NULL);
}