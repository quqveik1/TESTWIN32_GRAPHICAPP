#pragma once
#include "ManagerHandle.h"

void ManagerHandle::setHandleHeight(int height)
{
    if (!handle)
    {
        createHandle();
    }
    Rect newRect = handle->rect;
    newRect.setHeight(height);
    handle->resize(newRect);
}


void ManagerHandle::createHandle()
{
}




void ManagerHandle::draw()
{
    handle->print(finalDC);

    app->windowsLibApi->standartManagerDraw(this);
}