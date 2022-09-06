#pragma once
#include "Lay.h"


Lay::~Lay()
{
    lay.deleteObj();
    outputLay.deleteObj();
}


void Lay::createLay(AbstractAppData* _app, Vector _laySize/* = {}*/)
{
    gassert(_app);
    app = _app;

    laySize = _laySize;
    Vector nullVector = { 0, 0 };

    if (laySize == nullVector) laySize = app->systemSettings->DCVECTORSIZE;
    lay.setSize(laySize, &layBuf);
    clean(lay);
    outputLay.setSize(laySize, &outputBuf);
    clean(outputLay);
}


int Lay::getDownUpCoordinats(int x, int y)
{
    return (int)(x + (laySize.y - y) * laySize.x);
}

void Lay::clean(M_HDC dc)
{
    app->setColor(app->systemSettings->TRANSPARENTCOLOR, dc);
    app->rectangle(0, 0, laySize.x, laySize.y, dc);
}
