#pragma once

#include "Manager.h"

bool Manager::addWindow(Window* window, MEM_TYPE _memtype/* = 0*/)
{
    window->memType = _memtype;
    return app->windowsLibApi->addWindow(this, window);
}

bool Manager::addWindow(Window& window, MEM_TYPE _memtype/* = 1*/)
{
    window.memType = _memtype;
    return app->windowsLibApi->addWindow(this, &window);
}


int Manager::separateWindow(int pos)
{
    return app->windowsLibApi->separateWindow(this, pos);
}

Window* Manager::getChildWindowPointer(int i)
{
    return pointers[i];
}

std::vector<Window*>& Manager::getPointers()
{
    return pointers;
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
    handle.setMbLastTime(0);
    return true;
}

int Manager::moveHandle(Vector delta)
{
    if (handle.mbLastTime == 1)
    {
        rect = rect + delta;
        if (needToShow)
        {
            app->updateScreen(this);
        }
    }

    return 1;
}

void Manager::controlHandle()
{
    //handle.print(finalDC);
    //app->windowsLibApi->controlHandle(this);
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

int Manager::onClick(Vector mp, int button)
{
    bool missClicked = true;

    int returnableVal = -1;

    //if (HideIfIsNotActive) unHide ();

    if (getShowStatus() == S_ACTIVE)
    {
        setActiveWindow(this);
        for (int i = getCurLen() - 1; i >= 0; i--)
        {
            if (pointers[i])
            {
                Vector relativeMP = mp - pointers[i]->rect.pos;
                if (pointers[i]->hitTest(relativeMP))
                {
                    pointers[i]->onClick(relativeMP, button);

                    missClicked = false;
                    returnableVal = i;
                    if (manager->pointers[i]->needToShow) break;
                }
                else
                {
                    missClicked = true;
                }
            }
        }
    }

    return returnableVal;
    
}


int Manager::hitTest(Vector mp)
{
    return app->windowsLibApi->standartManagerHitTest(this, mp);
}

int Manager::mbDown(Vector mp, int button)
{
    return app->windowsLibApi->standartManagerMbDown(this, mp, button);
}

int Manager::mbUp(Vector mp, int button)
{
    return app->windowsLibApi->standartManagerMbUp(this, mp, button);
}

int Manager::onDoubleClick(Vector mp, int button)
{
    return app->windowsLibApi->standartManagerOnDoubleClick(this, mp, button);
}

int Manager::onMouseMove(Vector mp, Vector delta)
{
    return app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);
}


int Manager::onTimer(UINT_PTR timerName)
{
    return app->windowsLibApi->standartManagerOnTimer(this, timerName);
}

int Manager::onClose()
{
    return app->windowsLibApi->standartManagerOnClose(this);
}

int Manager::onDestroy()
{
    return app->windowsLibApi->standartManagerOnDestroy(this);
}

int Manager::onEnterWindowSizeMove()
{
    int len = getCurLen();

    int res = 0;

    for (int i = 0; i < len; i++)
    {
        Window* _wnd = pointers[i];
        if (_wnd)
        {
            res += _wnd->onEnterWindowSizeMove();
        }
    }
    return res;
}

int Manager::onExitWindowSizeMove()
{
    int len = getCurLen();

    int res = 0;

    for (int i = 0; i < len; i++)
    {
        Window* _wnd = pointers[i];
        if (_wnd)
        {
            res += _wnd->onExitWindowSizeMove();
        }
    }
    return res;
}


int Manager::onDrawEnd()
{
    int len = getCurLen();

    int res = 1;

    for (int i = 0; i < len; i++)
    {
        Window* _wnd = getChildWindowPointer(i);
        if (_wnd)
        {
            _wnd->onDrawEnd();
        }
    }
    return res;
}


int Manager::onSize(Vector managerSize, Rect newRect)
{
    Window::onSize(managerSize, newRect);
    return app->windowsLibApi->standartManagerOnSize(this, managerSize, newRect);
}

int Manager::onKeyboard(int key)
{
    return app->windowsLibApi->standartManagerOnKeyboard(this, key);
}

int Manager::onKeyboardChar(int key)
{
    return app->windowsLibApi->standartManagerOnKeyboardChar(this, key);
}




void Manager::defaultDestructor()
{
    assert(app);
    //if (dc) app->deleteDC(dc);
    //if (finalDC) app->deleteDC(finalDC);
    int _l = getCurLen();
    for (int i = 0; i < _l; i++)
    {
        if (pointers[i])
        {
            int _may = pointers[i]->mayBeDeletedInDestructor();
            if (_may)
            {
                delete pointers[i];
            }

        }
    }
};



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