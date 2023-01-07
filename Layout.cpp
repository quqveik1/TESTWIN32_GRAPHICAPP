#pragma once

#include "Layout.h"


void Layout::print(M_HDC& _finalDC)
{
    setOutputDC(&_finalDC);
    draw();
    //setOutputDC(NULL);
}