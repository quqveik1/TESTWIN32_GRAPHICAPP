#pragma once
#include "WindowsLib.cpp"


struct ImportImage : Window
{
    HMODULE importDLL = NULL;
    HDC (*importImage)(const char* path, Vector& size, AbstractAppData* _app) = NULL;

    ImportImage(AbstractAppData* _app) :
        Window(_app)
    {
        importDLL = _app->loadLibManager->loadLib("SaveImage.dll");
        assert(importDLL);

        importImage = (HDC (*)(const char* path, Vector & size, AbstractAppData * _app)) GetProcAddress(importDLL, "loadImage");
        hide();
    }

    virtual void draw() override;

};