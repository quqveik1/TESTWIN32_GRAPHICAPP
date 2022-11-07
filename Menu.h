#pragma once

#include "DrawBibliothek.h"


struct Menu : Manager
{
    int lastSelected = 0;
    int currentSize = 0;
    Menu(AbstractAppData* _app, Rect _rect, Rect _handle, int _length = 10, bool _isDefaultActive = false) :
        Manager(_app, _rect, _length, _isDefaultActive, NULL, _handle, _app->systemSettings->MenuColor, true)
    {}

    virtual void drawOneLine(int lineNum) = NULL;
    virtual int onClickLine(Vector mp) = NULL;
    virtual void onUpdate() {};

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;


};