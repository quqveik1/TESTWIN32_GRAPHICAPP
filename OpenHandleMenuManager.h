#pragma once
#include "OpenManager.cpp"

struct OpenHandleMenuManager : OpenManager
{
    OpenHandleMenuManager(AbstractAppData* _app, const char* _name) :
        OpenManager(_app, {}, _app->systemSettings->MenuColor, NULL, NULL, _name)
    {
    }

    virtual void showControl() override;

};