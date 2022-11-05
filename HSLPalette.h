#pragma once

#include "WindowsLib.cpp"

struct HSLPalette : Window
{
    Vector size = {};
    int lightness = 100;
    M_HDC palette;
    COLORREF colorLastTime = 0;
    Vector crossPos = {};
    const Vector crossLineSize = {2, 25};
    int isMovingCross = 0;
    bool* confirmedColor = NULL;

    HSLPalette(AbstractAppData* _app, Vector _pos, bool* _confirmedColor) :
        size({ 256, 256 }),
        Window(_app, { .pos = _pos, .finishPos = {256 + _pos.x, 256 + _pos.y} }),
        confirmedColor(_confirmedColor)
    {
        initPalette();
    }

    void initPalette();

    virtual void draw() override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;

};