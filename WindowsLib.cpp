#pragma once
#include "WindowsLib.h"
#include "WindowsLibApi.h"


bool Manager::addWindow(Window* window)
{
    return app->windowsLibApi->addWindow(this, window);
}


void Window::print(HDC DC)
{
    assert(DC);
    draw();
    app->bitBlt(DC, rect.pos.x, rect.pos.y, rect.getSize().x, rect.getSize().y, finalDC);
}

Vector Window::getSize()
{
    return this->rect.finishPos - this->rect.pos;
}

void Window::MoveWindowTo(Vector pos)
{
    Vector size = getSize();

    rect.pos = pos;
    rect.finishPos = rect.pos + size;
}

void Window::MoveWindow(Vector delta)
{
    rect = rect + delta;
}

void Window::draw()
{
    app->windowsLibApi->standartWindowDraw(this);
}

void Window::resize(Rect newRect)
{
    app->windowsLibApi->resize(this, newRect);
}

void Window::resize(Vector newSize)
{
    app->windowsLibApi->resize(this, newSize);
}

void Window::reInit()
{
    /*
    if (rect.getSize().x > 0 && rect.getSize().y > 0)
    {
        finalDCSize = { rect.getSize().x, rect.getSize().y };
        finalDC = app->createDIBSection(finalDCSize.x, finalDCSize.y, &finalDCArr);
        app->setColor(color, finalDC);
        app->rectangle(0, 0, rect.getSize().x, rect.getSize().y, finalDC);
        if (systemSettings->debugMode == 5) app->drawOnScreen(finalDC);
    }

    originalRect = rect;
    */
}

void Window::setStartRect(Vector pos, Vector finishPos)
{
    assert(pos > 0 && finishPos > 0);
    rect = { pos, finishPos };
    originalRect = rect;
}
Vector Window::getRelativeMousePos(bool coordinatsWithHandle)
{
    //POINT mousePos = {(double)txMouseX() - getAbsCoordinats(coordinatsWithHandle).x, (double) txMouseY () - getAbsCoordinats(coordinatsWithHandle).y};
    //ScreenToClient (systemSettings->MAINWINDOW, &mousePos);
    //return {(double)mousePos.x, (double)mousePos.y};
    return { 0, 0 };
}

Vector Window::getAbsCoordinats(bool coordinatsWithHandle /*=false*/)
{
    return app->windowsLibApi->getAbsCoordinats(this, coordinatsWithHandle);
}

Rect Window::getAbsRect(bool coordinatsWithHandle /*=false*/)
{
    Rect coordinats = {};

    Manager* copyOfManager = manager;

    coordinats.pos += rect.pos;

    for (;;)
    {
        if (!copyOfManager) break;

        coordinats.pos += copyOfManager->rect.pos;
        if (copyOfManager->coordinatSysFromHandle && !coordinatsWithHandle)
        {
            coordinats.pos.y += copyOfManager->handle.rect.finishPos.y;
        }
        copyOfManager = copyOfManager->manager;
    }

    coordinats.finishPos = rect.finishPos + (coordinats.pos - rect.pos);


    return coordinats;
}



Window* Manager::isActiveWindowBelow()
{
    return app->windowsLibApi->isActiveWindowBelow(this);
}


void Manager::draw()
{
    app->windowsLibApi->standartManagerDraw(this);
}

int Manager::clickHandle()
{
    return app->windowsLibApi->clickHandle(this);
}      
int Manager::mbUpHandle()
{
    manager->handle.setMbLastTime();
    return true;
}

int Manager::moveHandle(Vector delta)
{
    if (handle.mbLastTime == 1)
    {
        rect = rect + delta;
        app->updateScreen();
    }
    
    return 1;
}

void Manager::controlHandle()
{
    app->windowsLibApi->controlHandle(this);
}



void Manager::replaceWindow(int numOfWindow)
{
    Window* copyOfStartWindow = pointers[numOfWindow];
    Window* copyOfWindow = pointers[currLen - 1];


    for (int i = currLen - 1; i > numOfWindow; i--)
    {
        Window* preCopyOfWindow = pointers[i - 1];
        pointers[i - 1] = copyOfWindow;
        copyOfWindow = preCopyOfWindow;
    }

    if (numOfWindow < currLen - 1)
    {
        pointers[currLen - 1] = copyOfStartWindow;
    }


}

void Manager::onClick(Vector mp)
{
    app->windowsLibApi->standartManagerOnClick(this, mp);
}

int Manager::mbDown(Vector mp, int button)
{
    return app->windowsLibApi->standartManagerMbDown(this, mp, button);
}

int Manager::mbUp(Vector mp, int button)
{
    return app->windowsLibApi->standartManagerMbUp(this, mp, button);
}

int Manager::onMouseMove(Vector mp, Vector delta)
{
    app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);
    return 0;
}

int Manager::onSize(Vector managerSize)
{    
    return app->windowsLibApi->standartManagerOnSize(this, managerSize);
}

int Manager::onKeyboard(int key)
{
    return app->windowsLibApi->standartManagerOnKeyboard(this, key);
}




void Manager::defaultDestructor()
{
    assert(app);
    if (dc) app->deleteDC(dc);
    if (finalDC) app->deleteDC(finalDC);
    for (int i = 0; i < getCurLen(); i++)
    {
        //if (pointers[i]) delete pointers[i];
    }
};

void Window::defaultDestructor()
{
    assert(app);
    if (dc) app->deleteDC(dc);
    if (finalDC) app->deleteDC(dc);
}

void Manager::hide()
{
    needToShow = false;
    for (int i = 0; i < getCurLen(); i++)
    {
        pointers[i]->hide();
    }
}

void Manager::show()
{
    needToShow = true;
    for (int i = 0; i < getCurLen(); i++)
    {
        pointers[i]->show();
    }
}

void Manager::screenChanged()
{
    app->windowsLibApi->screenChanged(this);
}