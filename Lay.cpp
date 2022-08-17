#pragma once
#include "Lay.h"


Lay::~Lay()
{
    if (lay && app)app->deleteDC(lay);
    if (outputLay && app)app->deleteDC(outputLay);
}


void Lay::createLay(AbstractAppData* _app, Vector _laySize/* = {}*/)
{
    gassert(_app);
    app = _app;

    laySize = _laySize;
    Vector nullVector = { 0, 0 };

    if (laySize == nullVector) laySize = app->systemSettings->DCVECTORSIZE;
    lay = app->createDIBSection(laySize.x, laySize.y, &layBuf);
    clean();
    outputLay = app->createDIBSection(laySize.x, laySize.y, &outputBuf);
    clean(outputLay);
}


int Lay::getDownUpCoordinats(int x, int y)
{
    return (int)(x + (laySize.y - y) * laySize.x);
}

void Lay::clean(HDC dc/* = NULL*/)
{
    if (!dc) dc = lay;
    app->setColor(app->systemSettings->TRANSPARENTCOLOR, dc);
    app->rectangle(0, 0, laySize.x, laySize.y, dc);
}
