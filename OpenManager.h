#pragma once
#include "WindowsLib.h"


struct OpenManager : Window
{
    Manager* openingManager;
    bool isOpeningAnotherList = false;
    int mode = 0;
    int* opening = NULL;
    int keyBind = NULL; //ctrl + keybind
    bool wasListTimeKeyBoardClicked = 0;

    OpenManager(AbstractAppData* _app, Rect _rect, COLORREF _color, Manager* _manager, HDC _dc = NULL, const char* _text = "") :
        Window(_app, _rect, _color, _dc, NULL, _text, DS_INVISIBLE),
        openingManager(_manager)
    {
        format = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
    }

    OpenManager(AbstractAppData* _app, Vector _size) :
        Window(_app, { .pos = {}, .finishPos = _size }),
        openingManager(NULL)
    {
        format = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
    }

    void click();

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int onKeyboard(int key) override;
    virtual void showControl() {};
    virtual int onMouseMove(Vector mp, Vector delta)  override;

    virtual Manager*& getOpeningManager() { return openingManager; };
    virtual void setOpeningManager(Manager* _manager) { openingManager = _manager; };
};
