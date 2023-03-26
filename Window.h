#pragma once

#include "AbstractApp.h"
#include "M_HDC.cpp"
#include "HGDIManager.h" 
#include "LayoutInfo.h"
#include "MEM_TYPE.h"
#include <memory>
#include "remember_mem_type.cpp"
#include "WindowMessage.h"



struct Window : remember_mem_type
{
    const char* devName = NULL;

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

    HDC dc;

    M_HDC finalDC;
    M_HDC* pFinalDC = NULL;
    int hasItsFinalDC = 1;
    RGBQUAD* finalDCArr = NULL;
    Vector finalDCSize = {};
    struct Manager* manager = NULL;
    //std::shared_ptr<LayoutInfo> layoutInfo; //might be NULL if window is not in Layout, control it
    struct LayoutInfo* layoutInfo = NULL; //might be NULL if window is not in Layout, control it

    enum DrawStatus
    {
        DS_VISIBLE = 1,
        DS_INVISIBLE = 0
    };
    bool needToShow = true;
    //DON't USE IT
    bool reDraw = true; //????
    bool needTransparencyOutput = false;
    bool redrawStatus = false;
    bool validViewState = false;

    bool matchParentX = false;
    bool matchParentY = false;


    Vector mousePosLastTime = {};
    int mbLastTime = 0;


    Window(AbstractAppData* _app, Rect _rect = {}, COLORREF _color = NULL, HDC _dc = NULL, Manager* _manager = NULL, const char* _text = NULL, bool _needToShow = true) :
        app(_app),
        rect(_rect),
        manager(_manager),
        needToShow(_needToShow),
        reDraw(true),
        dc(_dc),
        pFinalDC(&finalDC),
        finalDC(app)
    {
        setApp(_app);
        assert(_app);
        

        if (_app)
        {
            if (!color) color = _app->systemSettings->MenuColor;
            onSize({}, rect);
            //resize(rect);

            setText(_text);
            setFont(_app->systemSettings->MainFont);
            setColor(_color);

            if (!color) color = _app->systemSettings->MenuColor;

            originalRect = rect;
            fontName = _app->systemSettings->FONTNAME;
            sideThickness = std::lround(_app->systemSettings->SIDETHICKNESS);
            format = _app->systemSettings->TEXTFORMAT;
        }
    }

    virtual void defaultDestructor();

    virtual ~Window()
    {
        assert(app);
        if (dc) app->deleteDC(dc);
        if (finalDC) finalDC.deleteObj();
        LayoutInfo* _layoutInfo = getLayoutInfo();
        if (_layoutInfo)
        {
            if (_layoutInfo->memType == MT_DYNAMIC)
            {
                delete _layoutInfo;
            }
        }
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
    virtual void needRedraw() { redrawStatus = true; };
    virtual bool getRadrawStatus() { return redrawStatus; };
    virtual void setRadrawStatus(bool status) { redrawStatus = status; };
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
        if (appData) return appData->getMouseButton();
        else         return -1;
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

    virtual void screenChanged() {}; //???
    virtual void invalidateButton();
    virtual bool isValidViewState() { return validViewState; };
    virtual void inValidateViewState() { validViewState = false; };
    virtual void validateViewState() { validViewState = true; };
    virtual void setValidViewState(bool newState) { if (newState == true) { validateViewState(); } else { inValidateViewState(); } };

    virtual void hide() { needToShow = false; };
    virtual void show() { needToShow = true; };
    virtual int getShowStatus() { return needToShow; }
    

    virtual Vector getAbsMousePos() { return getMousePos() + rect.pos; };

    virtual void setMPLastTime() { mousePosLastTime = getMousePos(); };

    virtual int mayBeDeletedInDestructor();

    virtual void onMessageRecieve(const char* name, void* data) {};
    virtual void sendMessage(const char* name, void* data) { onMessageRecieve(name, data); };
    virtual void onMessageRecieve(WindowMessage* msg) {};
    virtual void sendMessage(WindowMessage* msg) { onMessageRecieve(msg); };
    

    virtual M_HDC* getOutputDC() { return pFinalDC; };
    virtual M_HDC& getFinalDC() { return finalDC; };
    virtual M_HDC* setOutputDC(M_HDC* _newDC) { return pFinalDC = _newDC; }

    virtual int setTrancparencyOutput(int need);
    virtual int setMatchParentX(bool status);
    virtual int setMatchParentY(bool status);
    virtual int setMatchParent(bool status);
    virtual void setApp(AbstractAppData* newApp) { app = newApp; };
    virtual COLORREF setColor(COLORREF newColor);
    virtual int setFont(int newFont);
    virtual int setFormat(int newFormat);
    virtual const char* setText(const char* newText);
    virtual void setLayoutInfo(LayoutInfo* _layoutInfo, MEM_TYPE mt = MT_DYNAMIC) { layoutInfo = _layoutInfo; if (_layoutInfo) { _layoutInfo->memType = mt; }  invalidateButton(); };
    virtual void setLayoutInfo(LayoutInfo& _layoutInfo, MEM_TYPE mt = MT_STATIC) { layoutInfo = &_layoutInfo;                    _layoutInfo.memType = mt;     invalidateButton(); };
    virtual LayoutInfo* getLayoutInfo() { return layoutInfo; };

    virtual void onSizeChildCall(Window* _wnd) {};
    virtual void onSizeManagerNotify();


    virtual void draw();
    virtual void print(M_HDC& finalDC);
    virtual int hitTest(Vector mp);//1 - hit; 0 - miss
    virtual void onClick(Vector mp) {};
    virtual int mbDown(Vector mp, int button) { if (rect.inRect(mp)) { app->declareReactionOnMSG(1); }; return 0; };
    virtual int mbUp(Vector mp, int button) { return 0; };
    virtual int onDoubleClick(Vector mp, int button) { return 0; };
    virtual int onKeyboard(int key) { return 0; };
    virtual int onKeyboardChar(int key) { return 0; };
    virtual int onSize(Vector managerSize, Rect newRect = {}); // return 0 if size didn't changed
    virtual int onMouseMove(Vector mp, Vector delta) { return 0; };
    virtual int onTimer(UINT_PTR timerName) { return 0; };
    virtual int onClose() { return 0; };// if you want to cancel closing you need to return non 0 value
    virtual int onDestroy() { return 0; };
    virtual int onEnterWindowSizeMove() { return 0; };
    virtual int onExitWindowSizeMove() { return 0; };
    virtual int onDrawEnd() { validateViewState(); return 1; };//0 if you ignore this message
    

    virtual void deleteButton() {};
};