// TestWin32App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include "AppApi.cpp"

int initProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
int shutDownProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam);


int main()
{
    PowerPoint app(nullptr);
    app.startApp();
}


int initProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{


    
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
