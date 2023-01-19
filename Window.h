#pragma once

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
    M_HDC* pFinalDC = NULL;
    int hasItsFinalDC = 1;
    RGBQUAD* finalDCArr = NULL;
    Vector finalDCSize = {};
    struct Manager* manager = NULL;
    enum DrawStatus
    {
        DS_VISIBLE = 1,
        DS_INVISIBLE = 0
    };
    bool needToShow = true;
    bool reDraw = true;
    bool needTransparencyOutput = false;

    struct CLoadManager* loadManager = NULL;

    Vector mousePosLastTime = {};
    int mbLastTime = 0;

    int memType = 0;// 0 - dynamic; 1 - static

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
        fontName(_app->systemSettings->FONTNAME),
        sideThickness(std::lround(_app->systemSettings->SIDETHICKNESS)),
        format(_app->systemSettings->TEXTFORMAT),
        dc(_dc),
        pFinalDC(&finalDC),
        finalDC(app)
    {
        assert(_app);
        if (systemSettings->debugMode >= 0) printf("rect {%lf, %lf}; {%lf, %lf}\n", rect.pos.x, rect.pos.y, rect.finishPos.x, rect.finishPos.y);

        if (!color) color = systemSettings->MenuColor;
        onSize({}, rect);
        //resize(rect);

        if (!color) color = systemSettings->MenuColor;

        originalRect = rect;
    }

    virtual void defaultDestructor();

    virtual ~Window()
    {
        //defaultDestructor();
        assert(app);
        if (dc) app->deleteDC(dc);
        if (finalDC) finalDC.deleteObj();
    }


    Vector getAbsCoordinats(bool coordinatsWithHandle = false);
    Vector getRelativeMousePos(bool coordinatsWithHandle = false);
    Rect getAbsRect(bool coordinatsWithHandle = false);



    virtual void resize(Rect newSize);
    virtual void resize(Vector newSize);
    //void resize (Vector newSize, Vector oldSize);
    virtual void reInit();
    virtual void setStartRect(Vector pos, Vector finishPos);
    


    virtual Vector getSize();
    virtual Rect getRect() { return rect; };
    virtual Manager* getManager() { return manager; };
    virtual void needRedraw() {};
    virtual bool getRadrawStatus() { return redrawStatus; };
    virtual void noMoreRedraw() { redrawStatus = false; };

    virtual void MoveWindow(Vector delta);
    virtual void MoveWindowTo(Vector pos, bool needToCallOnSize = true);


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
    virtual int getShowStatus() { return needToShow; }

    virtual Vector getAbsMousePos() { return getMousePos() + rect.pos; };

    virtual void setMPLastTime() { mousePosLastTime = getMousePos(); };

    virtual int mayBeDeletedInDestructor() { if (memType == 0) { return 1; } return 0; };

    virtual void sendMessage(const char* name, void* data) { onMessageRecieve(name, data); };
    virtual void onMessageRecieve(const char* name, void* data) {};

    virtual M_HDC* getOutputDC() { return pFinalDC; };
    virtual M_HDC* setOutputDC(M_HDC* _newDC) { return pFinalDC = _newDC; }

    virtual int setFont(int newFont);
    virtual const char* setText(const char* newText);


    virtual void draw();
    virtual void print(M_HDC& finalDC);
    virtual int hitTest(Vector mp);//1 - hit; 0 - miss
    virtual void onClick(Vector mp) {};
    virtual int mbDown(Vector mp, int button) { if (rect.inRect(mp)) { app->declareReactionOnMSG(1); }; return 0; };
    virtual int mbUp(Vector mp, int button) { return 0; };
    virtual int onKeyboard(int key) { return 0; };
    virtual int onKeyboardChar(int key) { return 0; };
    virtual int onSize(Vector managerSize, Rect newRect = {});
    virtual int onMouseMove(Vector mp, Vector delta) { return 0; };
    virtual int onTimer(UINT_PTR timerName) { return 0; };
    virtual int onClose() { return 0; };// if you want to cancel closing you need to return non 0 value
    virtual int onDestroy() { return 0; };
    

    virtual void deleteButton() {};
};