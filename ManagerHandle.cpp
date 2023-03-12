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

int ManagerHandle::hitTest(Vector mp)
{
    if (handle->hitTest(mp - handle->rect.pos))
    {
        return 1;
    }

    Vector delta = mp;
    delta.y -= handle->rect.finishPos.y;

    return app->windowsLibApi->standartManagerHitTest(this, mp);


}

void ManagerHandle::onClick(Vector mp)
{
    if (handle->hitTest(mp - handle->rect.pos))
    {
        handle->onClick(mp - handle->rect.pos);
    }

    mp.y -= handle->rect.finishPos.y;

    app->windowsLibApi->standartManagerOnClick(this, mp);
}



int ManagerHandle::onMouseMove(Vector mp, Vector delta)
{
    handle->onMouseMove(mp, delta);

    mp.y -= handle->rect.finishPos.y;

    return app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);
}


int ManagerHandle::mbDown(Vector mp, int button)
{
    handle->mbDown(mp, button);

    mp.y -= handle->rect.finishPos.y;
    return app->windowsLibApi->standartManagerMbDown(this, mp, button);
} 


int ManagerHandle::mbUp(Vector mp, int button)
{
    handle->mbUp(mp, button);

    mp.y -= handle->rect.finishPos.y;
    return app->windowsLibApi->standartManagerMbUp(this, mp, button);
}


int ManagerHandle::onSize(Vector managerSize, Rect newRect/* = {}*/)
{
    handle->onSize(managerSize, {});
    return app->windowsLibApi->standartManagerOnSize(this, managerSize, {});
}



void ManagerHandle::draw()
{
    massert(handle, app);
    

    Vector delta = { 0, handle->getSize().y };
    app->windowsLibApi->standartManagerDraw(this, delta);
    handle->print(*getOutputDC());

}