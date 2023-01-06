#pragma once
#include "ThreeUpWindows.h"


void CloseButton::draw()
{
    $s;

    app->setColor(color, finalDC);
    app->rectangle(rect - rect.pos, finalDC);
    app->transparentBlt(finalDC, 0, 0, 0, 0, dc);
    
}

void CloseButton::onClick(Vector mp)
{
    assert(app);
    PostMessage(app->MAINWINDOW, WM_DESTROY, NULL, NULL);
}


int CloseButton::onMouseMove(Vector mp, Vector delta)
{
    if ((rect - rect.pos).inRect(mp))
    {
        SetCapture(app->MAINWINDOW);
        if (color != trueRed)
        {
            RECT _rect = (RECT)getAbsRect();
            InvalidateRect(app->MAINWINDOW, &_rect, FALSE);
        }
        color = trueRed;
        
    }
    else
    {
        if (color == trueRed)
        {
            color = app->systemSettings->MenuColor;
            RECT _rect = (RECT)getAbsRect();
            InvalidateRect(app->MAINWINDOW, &_rect, FALSE);
            ReleaseCapture();
        }
    }
    return 0;
}

void MinimizeWindow::draw()
{
    app->setColor(color, finalDC);
    app->rectangle(rect - rect.pos, finalDC);
    app->transparentBlt(finalDC, 0, 0, 0, 0, dc);
}

int MinimizeWindow::onMouseMove(Vector mp, Vector delta)
{
    if ((rect - rect.pos).inRect(mp))
    {
        SetCapture(app->MAINWINDOW);
        if (color != onMouseColor)
        {
            RECT _rect = (RECT)getAbsRect();
            InvalidateRect(app->MAINWINDOW, &_rect, FALSE);
        }
        color = onMouseColor;
    }
    else
    {
        if (color == onMouseColor)
        {
            color = app->systemSettings->MenuColor;
            RECT _rect = (RECT)getAbsRect();
            InvalidateRect(app->MAINWINDOW, &_rect, FALSE);
            ReleaseCapture();
        }
    }
    return 0;
}


void MinimizeWindow::onClick(Vector mp)
{
    assert(app);
    assert(app->systemSettings);
    assert(app->MAINWINDOW);

    app->isShowing = false;
    ShowWindow(app->MAINWINDOW, SW_SHOWMINIMIZED);
    color = app->systemSettings->MenuColor;
    app->updateScreen(this);
}





void ResizeButton::onClick(Vector mp)
{
    PowerPoint* fullapp = (PowerPoint*)app;

    assert (app);
    massert(app->MAINWINDOW, app);

    RECT _rect = {};
    GetWindowRect(app->MAINWINDOW, &_rect);
    Vector fullScreenSize = {};
    RECT fullScreenRect = {};

    SystemParametersInfo(SPI_GETWORKAREA, NULL, &fullScreenRect, NULL);

    fullScreenSize.x = GetSystemMetrics(SM_CXSCREEN);
    fullScreenSize.y = GetSystemMetrics(SM_CYSCREEN);

    if (_rect.bottom >= fullScreenRect.bottom && _rect.top <= fullScreenRect.top && _rect.left <= fullScreenRect.left && _rect.right >= fullScreenRect.right)
    {
        ShowWindow(app->MAINWINDOW, SW_RESTORE);
    }
    else
    {
        ShowWindow(app->MAINWINDOW, SW_MAXIMIZE);
    }

    /*
    if (!isClickedLastTime())
    {
        Vector saveSize = app->systemSettings->SizeOfScreen;
        if (app->isFullScreen())
        {

            if (app->systemSettings->FullSizeOfScreen == app->systemSettings->lastTimeSizeOfScreen || app->systemSettings->lastTimeSizeOfScreen == app->systemSettings->lastTimeSizeOfScreen.getNullVector())
            {
                Vector newSize = app->systemSettings->FullSizeOfScreen / 1.5;
                fullapp->changeWindow(newSize);
            }
            else
            {
                fullapp->changeWindow(app->systemSettings->lastTimeSizeOfScreen);
            }

        }
        else
        {
            fullapp->changeWindow(app->systemSettings->FullSizeOfScreen);
        }
        app->setResized();
        app->systemSettings->lastTimeSizeOfScreen = saveSize;
    }
    */
}

void ResizeButton::draw()
{
    setMbLastTime();
    if (app->isFullScreen()) dc = nowIsFullScreen;
    else                     dc = nowIsNotFullScreen;



    app->setColor(color, finalDC);
    app->rectangle(rect - rect.pos, finalDC);
    app->transparentBlt(finalDC, 0, 0, 0, 0, dc);
}

int ResizeButton::onMouseMove(Vector mp, Vector delta)
{
    if ((rect - rect.pos).inRect(mp))
    {
        SetCapture(app->MAINWINDOW);
        if (color != onMouseColor)
        {
            RECT _rect = (RECT)getAbsRect();
            InvalidateRect(app->MAINWINDOW, &_rect, FALSE);
            
        }
        color = onMouseColor;
    }
    else
    {
        if (color == onMouseColor)
        {
            color = app->systemSettings->MenuColor;
            RECT _rect = (RECT)getAbsRect();
            InvalidateRect(app->MAINWINDOW, &_rect, FALSE);
            ReleaseCapture();
        }
    }
    return 0;
}

