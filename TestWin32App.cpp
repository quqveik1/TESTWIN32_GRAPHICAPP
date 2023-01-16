// TestWin32App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "AppApi.cpp"
#include "resource.h"
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
#include <windowsx.h>

int initProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
int shutDownProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam);


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    WinMain(NULL, NULL, 0, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    appData = new PowerPoint(hInstance);

    MSG message = {};

    for (;;)                                                         
    {
        if (!GetMessage(&message, NULL, 0, 0)) break;
        else
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    return message.wParam;
}



int initProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{

    /*
    Handle* mainHandle = new Handle(appData);
    //appData->handle = mainHandle;
    

    MainManager* manager = new MainManager(appData, { .pos = {0, 0}, .finishPos = appData->systemSettings->FullSizeOfScreen }, 21, mainHandle);
    appData->mainManager = manager;

    
    


    CanvasManager* canvasManager = new CanvasManager(appData, { 0, 0 });
    appData->canvasManager = canvasManager;
    manager->addWindow(canvasManager);

    Option* optionCreate = new Option();
    optionCreate->name = "Создать";
    
    
    Option* optionSetCanvas = new Option();
    optionSetCanvas->name = "Создать холст";
    optionSetCanvas->reciever = canvasManager->getSetCanvasButton();
    optionCreate->addSubOption(optionSetCanvas);
    mainHandle->addOption(optionCreate);


    
    /*
    
    List* createList = mainHandle->createMenuOption("Создать", NULL, true);
    createList->addNewItem(canvasManager->getSetCanvasButton(), NULL, "Создать холст", NULL, 'N');

    ColorMenu* colorMenu = new ColorMenu(appData, {300, 200});
    manager->addWindow(colorMenu);

    
    ThicknessMenu* thickness = new ThicknessMenu(appData, { 100, 100 }, false);
    manager->addWindow(thickness);
    
    //ToolsPalette* toolsPallette = new ToolsPalette(appData, { 5, 100 }, appData->toolManager->currentLength);
    //manager->addWindow(toolsPallette);

    //LaysMenu* laysMenu = new LaysMenu(appData, { 5, 300 }, appData->canvasManager);
    //manager->addWindow(laysMenu);

    //ToolMenu* toolsMenu = new ToolMenu(appData, appData->canvasManager);
    //manager->addWindow(toolsMenu);
    

    List* openWindows = mainHandle->createMenuOption("Окна", NULL);
    openWindows->addNewItem(colorMenu, NULL, "Цвет", NULL, 'I');
    openWindows->addNewItem(thickness, NULL, "Толщина", NULL, 'W');
    //openWindows->addNewItem(toolsPallette, NULL, "Инструменты", NULL, 'T');
    //openWindows->addNewItem(laysMenu, NULL, "Слои", NULL, 'L');
    //openWindows->addNewItem(toolsMenu, NULL, "История/Порядок инструменто", NULL, 'T');
    
    //List* importList = mainHandle->createMenuOption("Импорт/Экспорт", NULL, true);
    //manager->addWindow(importList);
    
    */


    

    

    return 0;
}

int shutDownProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    delete appData;
    appData = NULL;

    return 0;
}
