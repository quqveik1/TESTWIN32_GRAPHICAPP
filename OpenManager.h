#pragma once
#include "DrawBibliothek.h"


struct OpenManager : Window
{
    Manager* openingManager;
    bool isOpeningAnotherList = false;
    int mode = 0;
    int* opening = NULL;
    int keyBind = NULL; //ctrl + keybind
    bool wasListTimeKeyBoardClicked = 0;

    OpenManager(AbstractAppData* _app, Rect _rect, COLORREF _color, Manager* _manager, HDC _dc = NULL, const char* _text = "") :
        Window(_app, _rect, _color, _dc, NULL, _text),
        openingManager(_manager)
    {
        format = DT_LEFT | DT_VCENTER;
    }

    OpenManager(AbstractAppData* _app) :
        Window(_app),
        openingManager(NULL)
    {
        format = DT_LEFT | DT_VCENTER;
    }

    void click();

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual void showControl() {};

    virtual Manager*& getOpeningManager() { return openingManager; };
    virtual void setOpeningManager(Manager* _manager) { openingManager = _manager; };
};
