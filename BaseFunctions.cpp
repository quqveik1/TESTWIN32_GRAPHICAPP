#pragma once
#include "BaseFunctions.h"
void drawCadre(Rect rect, HDC dc)
{
    printf("Rect: {%lf, %lf}\n", rect.pos.x, rect.pos.y);
    txLine(rect.pos.x,       rect.pos.y,       rect.pos.x,       rect.finishPos.y, dc);
    txLine(rect.pos.x,       rect.finishPos.y, rect.finishPos.x, rect.finishPos.y, dc);
    txLine(rect.finishPos.x, rect.pos.y,       rect.finishPos.x, rect.finishPos.y, dc);
    txLine(rect.pos.x,       rect.pos.y,       rect.finishPos.x, rect.pos.y,       dc);
}