#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "TXLib.cpp" 
#include "SystemSettings.cpp"
#include "DrawBibliothek.cpp"
#include "WindowsLib.cpp"
#include "Q_Buttons.h"
#include <cmath>
#include "StandartFunctions.h"
#include "Canvas.cpp"
#include "DLLFiltersManager.cpp"
#include "Tool.h"
#include "DLLToolsManager.cpp"
#include "CLay.cpp"
#include "CanvasManager.cpp"
#include "ProgressBar.h"
#include "LoadManager.cpp"
#include "Lay.cpp"
#include "AppApi.cpp"
#include "ToolsMenu.cpp"
#include "OpenManager.cpp"
#include "List.cpp"
#include "ThreeUpWindows.cpp"
#include "LaysMenu.cpp" 
#include "TouchButton.cpp"
#include "SetCanvasButton.cpp"
#include "Handle.cpp"
#include "MainManager.cpp"
#include "SaveImages.cpp"
#include "ColorComponentChanger.cpp"
#include "ColorMenu.cpp"
#include "FileSavings.cpp"
#include "LaysMenu.cpp"
#include "Thickness.cpp"
#include "OpenHandleMenuManager.cpp"
#include "winuser.h"
#include "WindowsLibApi.cpp"  
#include "ImportImage.cpp"
#include "OpenImage.cpp"




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    appData = new PowerPoint (hInstance);
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


/*
int main (int argc, int *argv[])
{
    appData = new PowerPoint;

    Handle* mainhandle = new Handle(appData, { .pos = {0, 0}, .finishPos = {appData->systemSettings->FullSizeOfScreen.x, appData->systemSettings->HANDLEHEIGHT} });

    MainManager* manager = new MainManager(appData, { .pos = {0, 0}, .finishPos = appData->systemSettings->FullSizeOfScreen }, 21, mainhandle);
    appData->mainManager = manager;

    manager->addWindow(mainhandle);

    CanvasManager* canvasManager = new CanvasManager(appData, {0, mainhandle->rect.finishPos.y});
    appData->canvasManager = canvasManager;
	manager->addWindow (canvasManager);


    if (appData->systemSettings->debugMode >= 0) printf("Инструменты начали загружаться\n");
    DLLToolsManager* dllToolsManager = new DLLToolsManager(appData, "Settings\\DLLPathList.txt");
    dllToolsManager->loadLibs();
    dllToolsManager->addToManager(appData->toolManager);
    if (appData->systemSettings->debugMode >= 0) printf("Инструменты загрузились\n");
    

	ToolsPalette *toolsPallette = new ToolsPalette(appData, {.pos = {5, 100}, .finishPos = {appData->systemSettings->BUTTONWIDTH + 5, (double)appData->toolManager->currentLength * 50 + appData->systemSettings->HANDLEHEIGHT + 100}}, appData->toolManager->currentLength);
    manager->addWindow(toolsPallette);

    ToolMenu* toolMenu = new ToolMenu(appData, canvasManager);
    manager->addWindow(toolMenu);   

    LaysMenu* laysMenu = new LaysMenu(appData, { .pos = {5, 600}, .finishPos = {appData->systemSettings->BUTTONWIDTH * 2, 800} }, canvasManager);
    manager->addWindow(laysMenu);

	ColorMenu* menu = new ColorMenu(appData, {appData->systemSettings->SizeOfScreen.x - 712, 300}, "Settings\\ColorHistory.history", true);
    menu->devName = "ColorMenu";
	manager->addWindow (menu);

    ThicknessMenu* thicknessButton = new ThicknessMenu(appData, { 300, 300 }, false);
    manager->addWindow(thicknessButton);

    /*
    DLLFiltersManager* dllManager = new DLLFiltersManager(appData, "Settings\\DLLPathList.txt");
    dllManager->loadLibs ();
    dllManager->addToManager(manager);
    if (appData->systemSettings->debugMode >= 0) printf("Фильтры загрузились\n");
    


    mainhandle;

		CloseButton* closeButton = new CloseButton(appData);
		mainhandle->addWindowToBack(closeButton);

        ResizeButton* resizeButton = new ResizeButton(appData);
        mainhandle->addWindowToBack(resizeButton);

        MinimizeWindow* minimizeButton = new MinimizeWindow(appData);
        mainhandle->addWindowToBack(minimizeButton);

        List* createList = mainhandle->createMenuOption("Создать", NULL, true);
    
        SetCanvasButton setCanvasButton(appData, canvasManager);
        createList->addNewItem(&setCanvasButton, NULL, "Создать холст", NULL, 'N');
        createList->addNewItem(NULL, NULL, "Создать слой", &(laysMenu->needToCreateLay), 'Q');
        manager->addWindow(&setCanvasButton);
    manager->addWindow(createList);

        List* openWindows = mainhandle->createMenuOption("Окна", NULL);;
    
            openWindows->addNewItem (menu, NULL, "Цвета");
            openWindows->addNewItem(thicknessButton, NULL, "Толщина");
            openWindows->addNewItem (toolsPallette, NULL, "Инструменты");
            openWindows->addNewItem (laysMenu, NULL, "Слои");
            openWindows->addNewItem (toolMenu, NULL, "Инструменты на слое");
        manager->addWindow(openWindows);
            /*
            List* filters = openWindows->addSubList("Фильтры", dllManager->currLoadWindowNum);
        manager->addWindow (filters);
                for (int i = 0; i < dllManager->currLoadWindowNum; i++)
                {
                    filters->addNewItem(dllManager->dllWindows[i], NULL, dllManager->dllWindows[i]->name);
                }
                

        List* importList = mainhandle->createMenuOption("Импорт/Экспорт", NULL, true);
            SaveImages saveImages(appData, canvasManager);
            importList->addNewItem(&saveImages, NULL, "Сохранить изображение", NULL, 'S');
            ImportImage importImage(appData);
            importList->addNewItem(&importImage, NULL, "Загрузить изображение", NULL, 'I');
            OpenImage openImage(appData);
            importList->addNewItem(&openImage, NULL, "Открыть изображение", NULL, 'O');
        manager->addWindow(importList);

	txBegin ();
	//Engine (manager);

    appData->IsRunning = true;
    while (appData->IsRunning)
    {
        txSleep(0);
    };

    menu->saveMenu();
    delete manager;
    delete appData;
	txEnd ();
    txDisableAutoPause();
    
	return 0;
}
*/









