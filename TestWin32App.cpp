﻿// TestWin32App.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
                appData->mainManager->onMouseMove({ (double)LOWORD(lParam), (double)HIWORD(lParam) }, {});
            }
        }

        if (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN)
        {
            if (appData->mainManager)
            {
                appData->mainManager->onClick({ (double)LOWORD(lParam), (double)HIWORD(lParam) });
                return 0;
            }
        }

        if (message == WM_KEYDOWN)
        {
            if (appData->mainManager)
            {
                appData->mainManager->onKeyboard(wParam);
            }
        }

        if (message == WM_PAINT)
        {
            HDC finalDC = BeginPaint(appData->MAINWINDOW, &ps);
            if (appData->mainManager)
            {
                appData->mainManager->print(finalDC);
            }
            EndPaint(appData->MAINWINDOW, &ps);
        }

        if (message == WM_SIZE)
        {
            if (appData->mainManager)
            {
                appData->systemSettings->SizeOfScreen = { (double)LOWORD(lParam), (double)HIWORD(lParam) };
                appData->mainManager->onSize(appData->systemSettings->SizeOfScreen);
            }
        }

        if (message == WM_DESTROY)
        {
            shutDownProg(window, message, wParam, lParam);
            PostQuitMessage(0);
            return 1;
        }
    }

    return DefWindowProc(window, message, wParam, lParam);
}


int initProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    Handle* mainHandle = new Handle(appData, { .pos = {0, 0}, .finishPos = {appData->systemSettings->FullSizeOfScreen.x, appData->systemSettings->HANDLEHEIGHT} });
    List* createList = mainHandle->createMenuOption("Создать", NULL, true);
    List* openWindows = mainHandle->createMenuOption("Окна", NULL);
    List* importList = mainHandle->createMenuOption("Импорт/Экспорт", NULL, true);

    MainManager* manager = new MainManager(appData, { .pos = {0, 0}, .finishPos = appData->systemSettings->FullSizeOfScreen }, 21, mainHandle);
    appData->mainManager = manager;
    manager->addWindow(mainHandle);


    CanvasManager* canvasManager = new CanvasManager(appData, { 0, mainHandle->rect.finishPos.y });
    manager->addWindow(canvasManager);

    SetCanvasButton* setCanvasButton = new SetCanvasButton(appData, canvasManager);    
    createList->addNewItem(setCanvasButton, NULL, "Создать холст", NULL, 'N');

    return 0;
}

int shutDownProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    delete appData;

    return 0;
}