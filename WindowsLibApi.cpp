#pragma once

#include "WindowsLibApi.h"
#include <algorithm>


void clickButton(Window* window, Manager* manager, Vector mp)
{
    window->onClick(mp - window->rect.pos);
}

void CWindowsLibApi::resize(Window* window, Rect newRect)
{
    gassert(window);
    if (window->app->systemSettings->debugMode >= 2) printf("newRect {%lf, %lf}; {%lf, %lf}\n", newRect.pos.x, newRect.pos.y, newRect.finishPos.x, newRect.finishPos.y);
    window->finalDCSize = { newRect.getSize().x, newRect.getSize().y };
    if (window->hasItsFinalDC && window->getOutputDC())
    {
        if (isBigger(newRect.getSize().x, 0) && isBigger(newRect.getSize().y, 0))
        {

            window->getOutputDC()->setSize(window->finalDCSize, window->app, &window->finalDCArr);
            window->inValidateViewState();

            //window->app->setColor(window->color, *window->getOutputDC());
            //window->app->rectangle(0, 0, newRect.getSize().x, newRect.getSize().y, *window->getOutputDC());

            if (window->app->systemSettings->debugMode == 5) window->app->drawOnScreen(*window->getOutputDC());
        }
    }
    window->rect = newRect;
}


void CWindowsLibApi::resize(Window* window, Vector newSize)
{
    resize(window, { .pos = window->rect.pos, .finishPos = window->rect.pos + newSize });
}

//#define NEEDTOCHECKPOINTERSDUBLICATE

bool CWindowsLibApi::addWindow(Manager* manager, Window* window)
{
    if (!window)
    {                                                    
        printf("Попытка добавить несуществующее окно\n");
        return 0;
    }


    int findedDublicatesElements = std::count(manager->pointers.begin(), manager->pointers.end(), window);

    if (findedDublicatesElements < 0)
    {
        printf("Попытка добавить уже добавленное в менеджер окно\n");
    }

    manager->pointers.push_back(window);
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
    gassert(window);
    $s;

    AbstractAppData* app = window->app;
    assert(app);
    M_HDC* outDC = window->getOutputDC();
    if (outDC)
    {

        if (window->needToShow)
        {

            if (*outDC) app->setColor(window->color, *outDC);
            if (*outDC) app->rectangle(0, 0, window->rect.getSize().x, window->rect.getSize().y, *outDC);

            if (window->text)
            {
                app->setColor(window->app->systemSettings->TextColor, *outDC);
                app->selectFont(window->fontName, window->font, *outDC);
                app->drawText(0, 0, window->rect.getSize().x, window->rect.getSize().y, window->text, *outDC, window->format);
            }

            if (window->dc)
            {
                app->bitBlt(*outDC, 0, 0, window->rect.getSize().x, window->rect.getSize().y, window->dc);
            }
        }
    }
    return 0;
}

int CWindowsLibApi::standartManagerDraw(Manager* manager, Vector deltaFromStart/* = {}*/)
{
    gassert(manager);

    manager->controlHandle();

    AbstractAppData* app = manager->app;
    assert(app);

    M_HDC* outDC = manager->getOutputDC();

    if (outDC)
    {

        if (manager->dc) app->bitBlt(*outDC, 0, 0, 0, 0, manager->dc);

        if (manager->needToShow)
        {
            if (deltaFromStart != 0) outDC->moveViewPort(deltaFromStart, manager->app);
            for (int i = 0; i < manager->getCurLen(); i++)
            {
                /*
                if (manager->pointers[i]->reDraw) manager->pointers[i]->draw();
                if (manager->pointers[i]->needToShow)
                {
                    /*
                    if (manager->pointers[i]->needTransparencyOutput) app->transparentBlt(manager->finalDC, manager->pointers[i]->rect.pos.x, manager->pointers[i]->rect.pos.y, manager->pointers[i]->rect.getSize().x, manager->pointers[i]->rect.getSize().y, manager->pointers[i]->finalDC);
                    else                                              app->bitBlt(manager->finalDC, manager->pointers[i]->rect.pos.x + deltaFromStart.x, manager->pointers[i]->rect.pos.y + deltaFromStart.y, manager->pointers[i]->rect.getSize().x, manager->pointers[i]->rect.getSize().y, manager->pointers[i]->finalDC);
                    *

                    if (manager->pointers[i]->needTransparencyOutput) app->transparentBlt(manager->finalDC, manager->pointers[i]->rect.pos + deltaFromStart, manager->pointers[i]->rect.finishPos + deltaFromStart, manager->pointers[i]->finalDC);
                    else                                              app->bitBlt(manager->finalDC, manager->pointers[i]->rect.pos.x + deltaFromStart.x, manager->pointers[i]->rect.pos.y + deltaFromStart.y, manager->pointers[i]->rect.getSize().x, manager->pointers[i]->rect.getSize().y, manager->pointers[i]->finalDC);


                }
                */

                if (manager->pointers[i]->reDraw)
                {
                    manager->pointers[i]->print(*outDC);
                }
            }
            if (deltaFromStart != 0) manager->finalDC.moveViewPort(-deltaFromStart, manager->app);
        }
    }
    return 0;
}


int CWindowsLibApi::standartManagerHitTest(struct Manager* manager, Vector mp)
{
    gassert(manager);
    if (!manager) return 0;

    if (manager->getShowStatus() == S_ACTIVE)
    {
        if ((manager->rect - manager->rect.pos).inRect(mp))
        {
            return 1;
        }
        for (int i = manager->getCurLen() - 1; i >= 0; i--)
        {
            if (manager->pointers[i])
            {
                int res = manager->pointers[i]->hitTest(mp - manager->pointers[i]->rect.pos);
                if (res)
                {
                    return 1;
                }

            }
        }

    }

    return 0;

}


int CWindowsLibApi::standartManagerOnClick(Manager* manager, Vector mp)
{
    gassert(manager);
    if (!manager) return -1;

    bool missClicked = true;

    int returnableVal = -1;

    //if (HideIfIsNotActive) unHide ();

    if (manager->getShowStatus() == S_ACTIVE)
    {
        manager->setActiveWindow(manager);
        for (int i = manager->getCurLen() - 1; i >= 0; i--)
        {
            if (manager->pointers[i])
            {
                if (manager->pointers[i]->hitTest(mp - manager->pointers[i]->rect.pos))
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
    }

    return returnableVal;
}


int CWindowsLibApi::standartManagerOnDoubleClick(struct Manager* manager, Vector mp, int button)
{
    if (manager)
    {
        if (manager->getShowStatus() == S_ACTIVE)
        {
            manager->setActiveWindow(manager);
            for (int i = manager->getCurLen() - 1; i >= 0; i--)
            {
                if (manager->pointers[i])
                {
                    if (manager->pointers[i]->hitTest(mp - manager->pointers[i]->rect.pos))
                    {
                        manager->pointers[i]->onDoubleClick(mp - manager->pointers[i]->rect.pos, button);

                        return i;
                        if (manager->pointers[i]->needToShow) break;
                    }
                }
            }
        }
    } 
    return 0;
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

int CWindowsLibApi::standartManagerOnSize(struct Manager* manager, Vector managerSize, Rect newRect/* = {}*/)
{
    if (manager)
    {
        for (int i = 0; i < manager->getCurLen(); i++)
        {
            Window* _wnd = manager->pointers[i];
           if(_wnd) _wnd->onSize(manager->getSize(), {});
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