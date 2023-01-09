#pragma once
#include "Window.h" 

void Window::defaultDestructor()
{

}

void Window::print(M_HDC& DC)
{
    assert(DC);
    draw();
    if(getShowStatus() == DS_VISIBLE) app->bitBlt(DC, rect.pos.x, rect.pos.y, rect.getSize().x, rect.getSize().y, finalDC);
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
    if (getManager())onSize(getManager()->getSize(), {});
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

    struct Manager* copyOfManager = manager;

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