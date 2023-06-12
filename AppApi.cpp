#pragma once

#include "AppApi.h"

#include <windowsx.h>
#include <Windows.h>

#include "AbstractApp.cpp"
#include "IMREDresource.h"
#include "MainManager.cpp"
#include "Handle.cpp"
#include "OpenManager.cpp"
#include "List.cpp"
#include "ConsoleOutput.cpp"
#include "CanvasManager.cpp"
#include "SetCanvasButton.cpp"
#include "ColorMenu.cpp"
//#include "ToolsMenu.cpp"
#include "Thickness.cpp"
//#include "LaysMenu.cpp"



bool checkVersionCompability(PowerPoint* app);
void writeVersion(PowerPoint* app);
bool swapDC(HDC dest, int xDest, int yDest, int wDest, int hDest,
    HDC src, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rOp);


PowerPoint::PowerPoint(HINSTANCE hInstance):
    AbstractAppData(hInstance)
{
    appVersion = "v0.2.4.0";
    massert (!makeDir("Settings"), this);

    HMODULE _saveImagesLib = loadLibManager->loadLib("SaveImage.dll");
    dllsaveImage = (int (*) (HDC dc, const char* path))GetProcAddress(_saveImagesLib, "saveImage");
    dllloadImage = (HDC(*) (const char* path, Vector & _size, AbstractAppData * _app))GetProcAddress(_saveImagesLib, "loadImage");

    toolManager = new CToolManager(this);
    DLLToolsManager dlltoolsmanager(this, "Settings\\DLLToolsPathList.txt");
    dlltoolsmanager.loadLibs();
    dlltoolsmanager.addToManager(toolManager);
}

PowerPoint::~PowerPoint()
{
    writeVersion(this);

}


void PowerPoint::onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    AbstractAppData::onCreate(window, message, wParam, lParam);
    Handle* mainHandle = new Handle(this);
    MainManager* manager = new MainManager(this, { .pos = {0, 0}, .finishPos = systemSettings->FullSizeOfScreen }, 21, mainHandle);
    setMainManager(manager);


    Option* optionCreate = new Option();
    optionCreate->name = "Создать";


    Option* optionSetCanvas = new Option();
    optionSetCanvas->name = "Создать холст";
    //optionSetCanvas->reciever = canvasManager->getSetCanvasButton();
    optionCreate->addSubOption(optionSetCanvas);
    mainHandle->addOption(optionCreate);

}

void writeVersion(PowerPoint* app)
{
    assert(app);
    FILE* versionFile = fopen("Settings\\Version.txt", "w");

    if (versionFile)
    {
        if (fprintf(versionFile, "%s", app->appVersion) == 0) massert(!"Версия приложения не записалась.", app);
    }
    if (versionFile)fclose(versionFile);
}


bool swapDC(HDC dest, int xDest, int yDest, int wDest, int hDest,
    HDC src, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rOp)
{
    return NULL;
}



bool checkVersionCompability(PowerPoint* app)
{
    assert(app);
    bool needLoadSaves = false;
    FILE* versionFile = fopen("Settings\\Version.txt", "r");

    if (versionFile)
    {
        char versionName[MAX_PATH] = {};
        (void)fscanf(versionFile, "%s", versionName);
        if (app->appVersion)
        {
            int result = strcmp(app->appVersion, versionName);
            if (result == 0) needLoadSaves = true;
        }
    }

    if (app->getAsyncKeyState(VK_CONTROL))
    {
        needLoadSaves = false;
    }

    if (versionFile) fclose(versionFile);
    return needLoadSaves;
}


