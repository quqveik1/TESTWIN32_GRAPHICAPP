#pragma once
#include "MainWindow.h"

int MainWindow::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    resize(managerSize);
    return app->windowsLibApi->standartManagerOnSize(this, getSize());
}