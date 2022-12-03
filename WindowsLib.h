#pragma once
#include "TXLib.cpp"
#include "AbstractApp.h"
#include "M_HDC.cpp"
#include "HGDIManager.h" 



struct Window
{
    const char* devName = NULL;

    CSystemSettings* systemSettings = NULL;
    struct AbstractAppData* app = NULL;

    HWND hwnd = NULL;

    Rect rect = {};
    Rect originalRect = {};
    COLORREF color = 0;

    const char* text = NULL;

    int format = 0;
    int font = 0;
    const char* fontName = "";
    int sideThickness = 0;

    bool redrawStatus = false;

    HDC dc;

    M_HDC finalDC;
    RGBQUAD* finalDCArr = NULL;
    Vector finalDCSize = {};
    struct Manager* manager = NULL;
    bool needToShow = true;
    bool reDraw = true;
    bool needTransparencyOutput = false;

    struct CLoadManager* loadManager = NULL;

    Vector mousePosLastTime = {};
    int mbLastTime = 0;

    Window(AbstractAppData* _app, Rect _rect = {}, COLORREF _color = NULL, HDC _dc = NULL, Manager* _manager = NULL, const char* _text = NULL, bool _needToShow = true) :
        app(_app),
        systemSettings(_app->systemSettings),
        rect(_rect),
        color(_color),
        manager(_manager),
        text(_text),
        needToShow(_needToShow),
        reDraw(true),
        loadManager(_app->loadManager),
        font(_app->systemSettings->MainFont),
        fontName (_app->systemSettings->FONTNAME),
        sideThickness(std::lround (_app->systemSettings->SIDETHICKNESS)),
        format(_app->systemSettings->TEXTFORMAT),
        dc (_dc)
    {
        assert(_app);
        if (systemSettings->debugMode >= 0) printf("rect {%lf, %lf}; {%lf, %lf}\n", rect.pos.x, rect.pos.y, rect.finishPos.x, rect.finishPos.y);

        if (!color) color = systemSettings->MenuColor;
        resize(rect);

        if (!color) color = systemSettings->MenuColor;

        originalRect = rect;
    }

    virtual void defaultDestructor();

    virtual ~Window()
    {
        defaultDestructor();
    }


    Vector getAbsCoordinats(bool coordinatsWithHandle = false);
    Vector getRelativeMousePos(bool coordinatsWithHandle = false);
    Rect getAbsRect(bool coordinatsWithHandle = false);



    virtual void resize(Rect newSize);
    virtual void resize(Vector newSize);
    //void resize (Vector newSize, Vector oldSize);
    virtual void reInit();
    virtual void setStartRect(Vector pos, Vector finishPos);
    virtual void print(HDC finalDC);


    virtual Vector getSize();
    virtual Manager* getManager() { return manager; };
    virtual void needRedraw() {};
    virtual bool getRadrawStatus() { return redrawStatus; };
    virtual void noMoreRedraw() { redrawStatus = false; };

    virtual void MoveWindow(Vector pos);
    virtual void MoveWindowTo(Vector delta);


    virtual int isVisible()
    {
        if (getManager())
        {
            if (needToShow) return ((Window*)getManager())->isVisible();
            else return false;
        }
        else
        {
            return needToShow;
        }
    };

    virtual int getMBCondition() {
        if (getManager()) return ((Window*)getManager())->getMBCondition();
        else              return 0;
    };
    virtual bool isClickedLastTime() {
        if (mbLastTime == 0) return false;
        else                 return mbLastTime == getMBCondition();
    };

    virtual void setMbLastTime(int pos = -1)
    {
        if (pos == -1)
        {
            mbLastTime = getMBCondition();
        }
        else
        {
            mbLastTime = pos;
        }
    };

    virtual Vector getMousePos() {
        if (getManager()) return ((Window*)getManager())->getMousePos() - rect.pos;
        else              return {};
    };

    virtual Window* getActiveWindow() {
        if (getManager()) return ((Window*)getManager())->getActiveWindow();
        else              return 0;
    };
    virtual void setActiveWindow(Window* window) {
        if (getManager()) return ((Window*)getManager())->setActiveWindow(window);
    };

    virtual Window* isActiveWindowBelow()
    {
        if (getActiveWindow() == this) return this;
        else return NULL;
    };

    virtual void screenChanged() {};

    virtual void hide() { needToShow = false; };
    virtual void show() { needToShow = true; };

    virtual Vector getAbsMousePos() { return getMousePos() + rect.pos; };

    virtual void setMPLastTime() { mousePosLastTime = getMousePos(); }


    virtual void draw();
    virtual void onClick(Vector mp) {};
    virtual int mbDown(Vector mp, int button) { if (rect.inRect(mp)) { app->declareReactionOnMSG(1); return 0; } };
    virtual int mbUp(Vector mp, int button) { return 0; };
    virtual int onKeyboard(int key) { return 0; };
    virtual int onKeyboardChar(int key) { return 0; };
    virtual int onSize(Vector managerSize) { return 0; };
    virtual int onMouseMove(Vector mp, Vector delta) { return 0; };
    virtual int onTimer(UINT_PTR timerName) { return 0; };
    virtual int onClose() { return 0; };// if you want to cancel closing you need to return non 0 value
    virtual int onDestroy() { return 0; };

    virtual void deleteButton() {};
};

struct Manager : Window
{
    int length;
    Window** pointers = NULL;
    int currLen;
    Window handle;
    Vector startCursorPos;
    bool coordinatSysFromHandle;
    bool HideIfIsNotActive;

    Manager(AbstractAppData* _app, Rect _rect, int _length, bool _needToShow = true, HDC _dc = NULL, Rect _handle = {}, COLORREF _color = NULL, bool _coordinatSysFromHandle = false, bool _HideIfIsNotActive = false) :
        Window(_app, _rect, _color, _dc, NULL, NULL, _needToShow),
        handle(_app, _handle),
        length(_length),
        pointers(new Window* [_length] {}),
        currLen(0),
        startCursorPos({}),
        coordinatSysFromHandle(_coordinatSysFromHandle),
        HideIfIsNotActive(_HideIfIsNotActive)
    {
        assert(app->windowsLibApi);
        handle.manager = this;
        //handle.rect.finishPos.x = getSize().x;
        handle.color = systemSettings->MenuColor;
    }


    virtual void defaultDestructor() override;

    virtual ~Manager()
    {
        defaultDestructor();
    }


    virtual bool addWindow(Window* window);
    virtual int separateWindow(int pos);


    virtual void controlHandle();
    virtual int clickHandle();
    virtual int mbUpHandle();
    virtual int moveHandle(Vector delta);
    virtual void replaceWindow(int numOfWindow);
    virtual void hide() override;
    virtual void show() override;
    virtual int& getCurLen() { return currLen; };

    virtual Window* isActiveWindowBelow() override;
    virtual void screenChanged() override;


    virtual void redraw() { redrawStatus = true; };

    virtual void draw()             override;
    virtual void onClick(Vector mp) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onSize(Vector managerSize) override;
    virtual int onKeyboard(int key) override;
    virtual int onKeyboardChar(int key) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
    virtual int onTimer(UINT_PTR timerName) override;
    virtual int onClose() override;
    virtual int onDestroy() override;

};
