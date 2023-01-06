#pragma once

#include "WindowsLibApi.cpp"

struct ManagerHandle : Manager
{
    Window* handle;

    ManagerHandle(AbstractAppData* _app, Window* _handle = NULL) :
        Manager(_app, {}, 0),
        handle(_handle)
    {
    }

    virtual void setHandle(Window* _handle) { handle = _handle };
    virtual void setHandleHeight(int height);
    virtual void createHandle();

    virtual void draw() override;
};