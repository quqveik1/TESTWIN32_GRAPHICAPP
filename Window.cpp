#pragma once
#include "Window.h" 

void Window::defaultDestructor()
{

}

void Window::print(M_HDC& DC)
{
    assert(DC);
    draw();
    if (getShowStatus() == DS_VISIBLE)
    {
        if (needTransparencyOutput)
        {
            Vector finalDCSize = finalDC.getSize();
            app->transparentBlt(DC, rect.pos.x, rect.pos.y, rect.getSize().x, rect.getSize().y, finalDC);
            app->DEBUGsaveImage(finalDC, "needTransparencyOutputfinalDC");
            app->DEBUGsaveImage(DC, "needTransparencyOutputDC");
        }
        else
        {
            app->bitBlt(DC, rect.pos.x, rect.pos.y, rect.getSize().x, rect.getSize().y, finalDC);
        }
    }
}

int Window::hitTest(Vector mp)
{
    if ((rect - rect.pos).inRect(mp))
    {
        return 1;
    }
    return 0;
}


int Window::onSize(Vector managerSize, Rect newRect/* = {}*/)
{
    onSizeManagerNotify();
    if (newRect != 0)
    {
        resize(newRect);
        return 1;
    }
    Manager* _manager = getManager();
    if (_manager)
    {
        if (managerSize == 0) managerSize = _manager->getSize();
    } 
    if (managerSize != 0)
    {
        Vector newSize = getSize();
        if (matchParentX)
        {
            newSize.x = managerSize.x;
        }
        if (matchParentY)
        {
            newSize.y = managerSize.y;
        }
        if (newSize != getNullVector())
        {
            resize(newSize);
        }
    }
    return 0;
}

Vector Window::getSize()
{
    return this->rect.finishPos - this->rect.pos;
}

void Window::MoveWindowTo(Vector pos, bool needToCallOnSize/* = true*/)
{
    Vector size = getSize();

    rect.pos = pos;
    rect.finishPos = rect.pos + size;
    if (getManager() && needToCallOnSize)onSize(getManager()->getSize(), {});
}

void Window::MoveWindow(Vector delta)
{
    rect = rect + delta;
}

int Window::mayBeDeletedInDestructor()
{
    if (memType == MT_DYNAMIC)
    {
        return 1; 
    } 
    return 0;
}

int Window::setTrancparencyOutput(int need)
{
    int old = needTransparencyOutput;
    needTransparencyOutput = need;
    if (old != need)
    {
        invalidateButton();
    }
    return old;
}

void Window::invalidateButton()
{
    app->updateScreen(this);
    needRedraw();
    inValidateViewState();
}


int Window::setMatchParentX(bool status)
{
    int old = matchParentX;
    matchParentX = status;
    if (old != matchParentX)
    {
        onSize({}, {});
    }
    return old;
}

int Window::setMatchParentY(bool status)
{
    int old = matchParentY;
    matchParentY = status;
    if (old != matchParentY)
    {
        onSize({}, {});
    }
    return old;
}

int Window::setMatchParent(bool status)
{
     setMatchParentX(status);
     return setMatchParentY(status);
}

COLORREF Window::setColor(COLORREF newColor)
{

    COLORREF oldcolor = color;
    color = newColor;
    if (oldcolor != newColor)
    {
        invalidateButton();
    }
    return oldcolor;

}

int Window::setFont(int newFont)
{
    int oldFont = font;
    font = newFont;
    if (oldFont != newFont)
    {
        invalidateButton();
    }
    return oldFont;
}


int Window::setFormat(int newFormat)
{
    int oldFormat = format;
    format = newFormat;
    if (oldFormat != format)
    {
        invalidateButton();
    }
    return oldFormat;
}


const char* Window::setText(const char* newText)
{
    const char* oldText = text;
    
    if (newText)
    {
        text = newText;
        if (!oldText)
        {
            //int newLength = strlen(newText);
            //char* _text = new char[newLength] {};
            //strcpy(_text, newText);
            //text = _text;
            invalidateButton();
        }
        if (oldText && newText)
        {
            if (strcmp(oldText, newText) != 0)
            {
                //int newLength = strlen(newText);
                //char* _text = new char[newLength] {};
                //strcpy(_text, newText);
                //delete text;
                //text = _text;
                invalidateButton();
            }
        }
    }
    return oldText;
}


void Window::onSizeManagerNotify() 
{ 
    Manager* _man = getManager(); 
    if (_man) _man->onSizeChildCall(this);
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