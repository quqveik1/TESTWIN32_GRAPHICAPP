#pragma once
#include "CanvasManager.h"
#include "LoadLib.h"

struct SaveImages : Window
{
    CanvasManager* canvasManager = NULL;
    HMODULE saveDLL = NULL;
    int (*saveImage) (HDC dc, const char* path) = NULL;

    SaveImages(AbstractAppData* _app, CanvasManager* _canvasManager) :
        Window(_app, {}, _app->systemSettings->MenuColor, NULL, NULL, "", false),
        canvasManager(_canvasManager)
    {
        saveDLL = _app->loadLibManager->loadLib("SaveImage.dll");
        assert(saveDLL);

        saveImage = (int (*) (HDC dc, const char* path))GetProcAddress(saveDLL, "saveImage");
        hide();
    }

    virtual void draw() override;
};