#pragma once
#include "ManagerHandle.h"
#include "WindowHandle.h"

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

void ManagerHandle::onClick(Vector mp)
{
    if (handle->rect.inRect(mp))
    {
        handle->onClick(mp);
    }

    app->windowsLibApi->standartManagerOnClick(this, mp);
}



int ManagerHandle::onMouseMove(Vector mp, Vector delta)
{
    handle->onMouseMove(mp, delta);

    return app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);
}


int ManagerHandle::mbDown(Vector mp, int button)
{
    handle->mbDown(mp, button);
    return app->windowsLibApi->standartManagerMbDown(this, mp, button);
} 


int ManagerHandle::mbUp(Vector mp, int button)
{
    handle->mbUp(mp, button);
    return app->windowsLibApi->standartManagerMbUp(this, mp, button);
}



void ManagerHandle::draw()
{
    massert(handle, app);
    handle->print(*getOutputDC());

    Vector delta = { 0, handle->getSize().y };
    app->windowsLibApi->standartManagerDraw(this, delta);
}