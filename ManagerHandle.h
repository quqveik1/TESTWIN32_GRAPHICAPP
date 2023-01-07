#pragma once

#include "WindowsLibApi.cpp"

struct ManagerHandle : Manager
{
    WindowHandle* handle;

    ManagerHandle(AbstractAppData* _app, WindowHandle* _handle = NULL) :
        Manager(_app, {}, 0),
        handle(_handle)
    {
    }

    virtual void setHandle(WindowHandle* _handle) { handle = _handle; };
    virtual void setHandleHeight(int height);
    virtual void createHandle();

    virtual void draw() override;
};