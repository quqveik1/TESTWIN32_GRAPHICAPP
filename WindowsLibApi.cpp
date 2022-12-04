#include "WindowsLibApi.h"
#include "DrawBibliothek.cpp"

void CWindowsLibApi::resize(Window* window, Rect newRect)
{
    if (window->systemSettings->debugMode >= 2) printf("newRect {%lf, %lf}; {%lf, %lf}\n", newRect.pos.x, newRect.pos.y, newRect.finishPos.x, newRect.finishPos.y);
    window->finalDCSize = { newRect.getSize().x, newRect.getSize().y };
    if (isBigger (newRect.getSize().x, 0) && isBigger (newRect.getSize().y, 0))
    {

        window->finalDC.setSize(window->finalDCSize, window->app, &window->finalDCArr);

        //window->app->setColor(window->color, window->finalDC);
        //window->app->rectangle(0, 0, newRect.getSize().x, newRect.getSize().y, window->finalDC);

        if (window->systemSettings->debugMode == 5) window->app->drawOnScreen(window->finalDC);
    }
    else
    {
        window->finalDC.setSize(window->finalDCSize, window->app, &window->finalDCArr);
    }
    window->rect = newRect;
}


void CWindowsLibApi::resize(Window* window, Vector newSize)
{
    resize(window, { .pos = window->rect.pos, .finishPos = window->rect.pos + newSize });
}



bool CWindowsLibApi::addWindow(Manager* manager, Window* window)
{
    if (!window)
    {
        printf("Попытка добавить несуществующее окно\n");
        return 0;
    }
    if (manager->currLen >= manager->length)
    {
        printf("!!!Unable to add new Window!!!\n");
        return 0;
    }

    manager->pointers[manager->currLen] = window;
    manager->currLen++;

    window->manager = manager;

    return 1;
}


int CWindowsLibApi::separateWindow(Manager* manager, int pos)
{
    massert(manager, manager->app)
    if (pos < 0 || pos >= manager->getCurLen())
    {
        massert(!"Попытка отделить от менеджера окно с несущуствующим позицией", manager->app);
        return -1;
    }

    Window* sepMan = manager->pointers[pos];
    if (sepMan)
    {
        sepMan->manager = NULL;
        for (int i = pos; i < manager->getCurLen() - 1; i++)
        {
            manager->pointers[i] = manager->pointers[i + 1];
        }
        manager->currLen--;
        return manager->currLen;
    }

    return -1;
}


int CWindowsLibApi::clickHandle(Manager* manager)
{
    if (manager->handle.rect.inRect(manager->getMousePos()) && manager->getMBCondition() == 1)
    {
        manager->startCursorPos.x = manager->getAbsMousePos().x;
        manager->startCursorPos.y = manager->getAbsMousePos().y;
        manager->handle.setMbLastTime();
        return true;
    }
    return 0;
}


Vector CWindowsLibApi::getAbsCoordinats(Window* window, bool coordinatsWithHandle /*=false*/)
{

    Vector coordinats = {};

    Manager* copyOfManager = window->manager;

    coordinats += window->rect.pos;

    for (;;)
    {
        if (!copyOfManager) break;

        coordinats = coordinats + copyOfManager->rect.pos;
        if (copyOfManager->coordinatSysFromHandle && !coordinatsWithHandle) coordinats.y += copyOfManager->handle.rect.finishPos.y;
        copyOfManager = copyOfManager->manager;

    }


    return coordinats;
}


Window* CWindowsLibApi::isActiveWindowBelow(Manager* manager)
{
    if (manager->getActiveWindow() == manager) return manager;
    for (int i = 0; i < manager->getCurLen(); i++)
    {
        Window* activeWindowBelow = NULL;
        if (manager->pointers[i]) activeWindowBelow = manager->pointers[i]->isActiveWindowBelow();
        if (activeWindowBelow) return activeWindowBelow;
    }
    return NULL;
}


void CWindowsLibApi::controlHandle(Manager* manager)
{
    gassert(manager);
    if (manager)
    {
        bool isClickedAgo = manager->handle.isClickedLastTime();
        if (manager->app->systemSettings->debugMode == 5) printf("isClickedLastTime: %d\n", isClickedAgo);

        Vector absMP = manager->getAbsMousePos();

        if (manager->app->systemSettings->debugMode == 5) printf("absMP: {%lf, %lf}\n", absMP.x, absMP.y);

        if (isClickedAgo && manager)
        {
            manager->rect.pos.x += absMP.x - manager->startCursorPos.x;
            manager->rect.pos.y += absMP.y - manager->startCursorPos.y;
            manager->rect.finishPos.x += absMP.x - manager->startCursorPos.x;
            manager->rect.finishPos.y += absMP.y - manager->startCursorPos.y;
            manager->startCursorPos.x = absMP.x;
            manager->startCursorPos.y = absMP.y;
        }
        if (manager->getMBCondition() == 0) manager->handle.setMbLastTime();
    }
}


void CWindowsLibApi::screenChanged(Manager* manager)
{
    for (int i = 0; i < manager->getCurLen(); i++)
    {
        if (manager->pointers[i]) manager->pointers[i]->screenChanged();
    }
}

int CWindowsLibApi::standartManagerShow(struct Manager* manager)
{
    manager->needToShow = true;
    for (int i = 0; i < manager->getCurLen(); i++)
    {
        manager->pointers[i]->show();
    }
    return 0;
} 

int CWindowsLibApi::standartManagerHide(struct Manager* manager)
{
    manager->needToShow = false;
    for (int i = 0; i < manager->getCurLen(); i++)
    {
        manager->pointers[i]->hide();
    }
    return 0;
}

int CWindowsLibApi::standartWindowDraw(struct Window* window)
{
    standartDraw$(window);
    return 0;
}

int CWindowsLibApi::standartManagerDraw(Manager* manager)
{
    standartManagerDraw$(manager);
    return 0;
}


int CWindowsLibApi::standartManagerOnClick(Manager* manager, Vector mp)
{
    gassert(manager);

    bool missClicked = true;

    int returnableVal = -1;

    //if (HideIfIsNotActive) unHide ();

    if (manager->needToShow)
    {
        manager->setActiveWindow(manager);
        //manager->clickHandle();
        for (int i = manager->currLen - 1; i >= 0; i--)
        {
            if (manager->pointers[i]->rect.inRect(mp))
            {
                clickButton(manager->pointers[i], manager, mp);

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

    return returnableVal;
}

int CWindowsLibApi::standartManagerMbDown(struct Manager* manager, Vector mp, int button)
{
    if (manager)
    {
        if (manager->needToControlHandleInDefaultFuncs)
        {
            manager->clickHandle();
        }
        for (int i = manager->getCurLen() - 1; i >= 0; i--)
        {
            if (manager->pointers[i])
            {
                int _val = manager->pointers[i]->mbDown(mp - manager->pointers[i]->rect.pos, button);
                if (_val > 0)
                {
                    return 1;
                }
            }
        }
        int _visible = manager->isVisible();
        if ((manager->rect - manager->rect.pos).inRect(mp) && _visible)
        {
            manager->app->declareReactionOnMSG(1);
        }
    }
    return 0;
}

int CWindowsLibApi::standartManagerMbUp(struct Manager* manager, Vector mp, int button)
{
    if (manager)
    {
        if (manager->needToControlHandleInDefaultFuncs)
        {
            manager->mbUpHandle();
        }
        for (int i = manager->getCurLen() - 1; i >= 0; i--)
        {
            if (manager->pointers[i])
            {
                manager->pointers[i]->mbUp(mp - manager->pointers[i]->rect.pos, button);
            }
        }
    }
    return 0;
}

int CWindowsLibApi::standartManagerOnMouseMove(struct Manager* manager, Vector mp, Vector delta)
{
    if (manager)
    {
        if (manager->needToControlHandleInDefaultFuncs)
        {
            manager->moveHandle(delta);
        }
        for (int i = 0; i < manager->getCurLen(); i++)
        {
           if (manager->pointers[i]) manager->pointers[i]->onMouseMove(mp - manager->pointers[i]->rect.pos, delta);
        }
    }
    return 0;
}

int CWindowsLibApi::standartManagerOnTimer(struct Manager* manager, UINT_PTR timerName)
{
    if (manager)
    {
        for (int i = 0; i < manager->getCurLen(); i++)
        {
            if (manager->pointers[i]) manager->pointers[i]->onTimer(timerName);
        }
    }
    return 0;
}

int CWindowsLibApi::standartManagerOnSize(struct Manager* manager, Vector managerSize)
{
    if (manager)
    {
        for (int i = 0; i < manager->getCurLen(); i++)
        {
            manager->pointers[i]->onSize(managerSize);
        }
        return manager->getCurLen();
    }
    return 0;
}

int CWindowsLibApi::standartManagerOnKeyboard(struct Manager* manager, int key)
{
    if (manager)
    {
        for (int i = 0; i < manager->getCurLen(); i++)
        {
            manager->pointers[i]->onKeyboard(key);
        }
        return manager->getCurLen();
    }
    return 0;
}

int CWindowsLibApi::standartManagerOnKeyboardChar(struct Manager* manager, int key)
{
    if (manager)
    {
        for (int i = 0; i < manager->getCurLen(); i++)
        {
            manager->pointers[i]->onKeyboardChar(key);
        }
        return manager->getCurLen();
    }
    return 0;
}


int CWindowsLibApi::standartManagerOnClose(struct Manager* manager)
{
    if (manager)
    {
        for (int i = 0; i < manager->getCurLen(); i++)
        {
            int retVal = manager->pointers[i]->onClose();
            if (retVal != 0) return retVal;
        }
    }
    return 0;
}


int CWindowsLibApi::standartManagerOnDestroy(struct Manager* manager)
{
    if (manager)
    {
        for (int i = 0; i < manager->getCurLen(); i++)
        {
            (void)manager->pointers[i]->onDestroy();
        }
    }
    return 0;
}