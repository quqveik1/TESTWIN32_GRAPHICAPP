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
    return 0;
}

int shutDownProg(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    delete appData;
    appData = NULL;

    return 0;
}
