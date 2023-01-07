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
    massert(handle, app);
    handle->print(finalDC);

    Vector delta = { 0, handle->getSize().y };
    app->windowsLibApi->standartManagerDraw(this, delta);
}