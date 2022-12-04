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
#include "ToolsMenu.cpp"
#include "Thickness.cpp"

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

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int timeWhenLastTimeRedrawed = 0;
    PAINTSTRUCT ps = {};

    if (message == WM_CREATE)
    {
        initProg(window, message, wParam, lParam);
    }

    if (appData)
    {
        appData->beforeMessage();
        if (message == WM_SETCURSOR)
        {
            if (appData->activeCursor)
            {
                SetClassLongPtr(window, GCLP_HCURSOR, (LONG_PTR)appData->activeCursor);
            }
        }

        if (message == WM_MOUSEMOVE)
        {
            if (appData->mainManager)
            {
                static Vector lastTimeMp = { (double)LOWORD(lParam), (double)HIWORD(lParam) };
                Vector mp = { (double)LOWORD(lParam), (double)HIWORD(lParam) };
                appData->mainManager->onMouseMove(mp, mp - lastTimeMp);
                lastTimeMp = mp;
            }
        }

        if (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN)
        {
            if (appData->mainManager)
            {
                int button = 0;
                if (message == WM_LBUTTONDOWN) button = 1;
                if (message == WM_RBUTTONDOWN) button = 2;
                printf("WM_MBDOWN_START\n");
                appData->mainManager->mbDown({ (double)LOWORD(lParam), (double)HIWORD(lParam) }, button);
                appData->captureMouse();
                printf("WM_MBDOWN_END\n");
            }
        }

        if (message == WM_LBUTTONUP || message == WM_RBUTTONUP)
        {
            if (appData->mainManager)
            {
                int button = 0;
                if (message == WM_LBUTTONUP) button = 1;
                if (message == WM_RBUTTONUP) button = 2;
                printf("WM_MBUP_START\n");
                appData->mainManager->mbUp({ (double)LOWORD(lParam), (double)HIWORD(lParam) }, button); 
                appData->mainManager->onClick({ (double)LOWORD(lParam), (double)HIWORD(lParam) });
                appData->releaseMouse();
                printf("WM_MBUP_END\n");
            }
        }

        if (message == WM_KEYDOWN)
        {
            if (appData->mainManager)
            {
                appData->mainManager->onKeyboard(wParam);
                //appData->captureMouse();
            }
        }

        if (message == WM_CHAR)
        {
            if (appData->mainManager)
            {
                appData->mainManager->onKeyboardChar(wParam);
             }
        }

        if (message == WM_TIMER)
        {
            if (appData->mainManager)
            {
                appData->mainManager->onTimer(wParam);
            }
        }

        if (message == WM_PAINT)
        {
            HDC finalDC = BeginPaint(appData->MAINWINDOW, &ps);
            
            if (appData->mainManager)
            {
                appData->bitBlt(finalDC, {}, {}, appData->mainManager->finalDC);
                appData->mainManager->print(finalDC);
            }
            EndPaint(appData->MAINWINDOW, &ps);
        }

        if (message == WM_SIZE)
        {
            if (appData->mainManager)
            {
                appData->systemSettings->SizeOfScreen = { (double)LOWORD(lParam), (double)HIWORD(lParam) };
                /*
                if (appData->systemSettings->SizeOfScreen.x < appData->systemSettings->MINSCREENSIZE.x)
                {
                    return 0;
                }
                if (appData->systemSettings->SizeOfScreen.y < appData->systemSettings->MINSCREENSIZE.y)
                {
                    return 0;
                } 
                */
                //int cxScreen = GetSystemMetrics(SM_CXSCREEN);
                //int cyScreen = GetSystemMetrics(SM_CYSCREEN);

                //MoveWindow(appData->MAINWINDOW, cxScreen, cyScreen, appData->systemSettings->SizeOfScreen.x, appData->systemSettings->SizeOfScreen.y, FALSE);
                appData->mainManager->onSize(appData->systemSettings->SizeOfScreen);
                
            }
        }

        if (message == WM_CLOSE)
        {
            bool canShutProg = true;
            if (appData->mainManager)
            {
                if (appData->mainManager->onClose())
                {
                    canShutProg = false;
                }
            }
            if (!canShutProg)
            {
                return 1;
            }
        }

        if (message == WM_DESTROY)
        {
            if (appData->mainManager)
            {
                appData->mainManager->onDestroy();
            }
            shutDownProg(window, message, wParam, lParam);
            PostQuitMessage(0);


        }
    }

    return DefWindowProc(window, message, wParam, lParam);
}


int initProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{

    Handle* mainHandle = new Handle(appData, { .pos = {0, 0}, .finishPos = {appData->systemSettings->FullSizeOfScreen.x, appData->systemSettings->HANDLEHEIGHT} });
    

    MainManager* manager = new MainManager(appData, { .pos = {0, 0}, .finishPos = appData->systemSettings->FullSizeOfScreen }, 21, mainHandle);
    appData->mainManager = manager;
    manager->addWindow(mainHandle);


    CanvasManager* canvasManager = new CanvasManager(appData, { 0, mainHandle->rect.finishPos.y });
    appData->canvasManager = canvasManager;
    manager->addWindow(canvasManager);

    
    List* createList = mainHandle->createMenuOption("Создать", NULL, true);
    createList->addNewItem(canvasManager->getSetCanvasButton(), NULL, "Создать холст", NULL, 'N');

    ColorMenu* colorMenu = new ColorMenu(appData, {300, 200});
    manager->addWindow(colorMenu);

    
    ThicknessMenu* thickness = new ThicknessMenu(appData, { 100, 100 }, true);
    manager->addWindow(thickness);
    

    ToolsPalette* toolsPallette = new ToolsPalette(appData, { 5, 100 }, appData->toolManager->currentLength);
    manager->addWindow(toolsPallette);
    

    List* openWindows = mainHandle->createMenuOption("Окна", NULL);
    openWindows->addNewItem(colorMenu, NULL, "Цвет", NULL, 'I');
    openWindows->addNewItem(thickness, NULL, "Толщина", NULL, 'W');
    openWindows->addNewItem(toolsPallette, NULL, "Инструменты", NULL, 'T');
    
    //List* importList = mainHandle->createMenuOption("Импорт/Экспорт", NULL, true);
    //manager->addWindow(importList);


    

    

    return 0;
}

int shutDownProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    delete appData;
    appData = NULL;

    return 0;
}
