#pragma once

#include "Window.h"

struct Manager : Window
{
    int length;
    std::vector <Window*> pointers;
    int currLen;
    Window handle;
    int needToControlHandleInDefaultFuncs = 0;
    Vector startCursorPos;
    bool coordinatSysFromHandle;
    bool HideIfIsNotActive;


    Manager(AbstractAppData* _app, Rect _rect = {}, int _length = 0, bool _needToShow = true, HDC _dc = NULL, Rect _handle = {}, COLORREF _color = NULL, bool _coordinatSysFromHandle = false, bool _HideIfIsNotActive = false) :
        Window(_app, _rect, _color, _dc, NULL, NULL, _needToShow),
        handle(_app, _handle),
        length(_length),
        currLen(0),
        startCursorPos({}),
        coordinatSysFromHandle(_coordinatSysFromHandle),
        HideIfIsNotActive(_HideIfIsNotActive)
    {
        assert(app->windowsLibApi);
        handle.manager = this;
        //handle.rect.finishPos.x = getSize().x;
        if (app)
        {
            handle.color = app->systemSettings->MenuColor;
        }
    }


    virtual void defaultDestructor() override;

    virtual ~Manager()
    {
        defaultDestructor();
    }


    virtual bool addWindow(Window* window, MEM_TYPE _memtype = MT_DYNAMIC);//1 - if window was sucsessfully added, otherwise - 0
    virtual bool addWindow(Window& window, MEM_TYPE _memtype = MT_STATIC); //1 - if window was sucsessfully added, otherwise - 0
    virtual int separateWindow(int pos);

    virtual void controlHandle();
    virtual int clickHandle();
    virtual int mbUpHandle();
    virtual int moveHandle(Vector delta);
    virtual void replaceWindow(int numOfWindow);
    virtual void hide() override;
    virtual void show() override;
    virtual int& getCurLen() { return currLen; };
    virtual Window* getChildWindowPointer(int i);
    virtual std::vector<Window*>& getPointers();

    virtual Window* isActiveWindowBelow() override;
    virtual void screenChanged() override;

    virtual void redraw() { redrawStatus = true; };

    virtual void draw                 ()                                      override;
    virtual int  hitTest              (Vector mp)                             override;
    virtual void onClick              (Vector mp)                             override;
    virtual int  onClick              (Vector mp, int button)                 override;
    virtual int  mbDown               (Vector mp, int button)                 override;
    virtual int  mbUp                 (Vector mp, int button)                 override;
    virtual int  onDoubleClick        (Vector mp, int button)                 override;
    virtual int  onSize               (Vector managerSize, Rect newRect = {}) override;
    virtual int  onKeyboard           (int key)                               override;
    virtual int  onKeyboardChar       (int key)                               override;
    virtual int  onMouseMove          (Vector mp, Vector delta)               override;
    virtual int  onTimer              (UINT_PTR timerName)                    override;
    virtual int  onClose              ()                                      override;
    virtual int  onDestroy            ()                                      override;
    virtual int  onEnterWindowSizeMove()                                      override;
    virtual int  onExitWindowSizeMove ()                                      override;
    virtual int  onDrawEnd            ()                                      override;
};