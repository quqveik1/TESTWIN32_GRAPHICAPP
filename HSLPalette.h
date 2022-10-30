#pragma once

#include "WindowsLib.cpp"

struct HSLPalette : Window
{
    Vector size = {};
    int lightness = 100;
    M_HDC palette;

    HSLPalette(AbstractAppData* _app, Vector _pos) :
        size({ 256, 256 }),
        Window(_app, { .pos = _pos, .finishPos = {256 + _pos.x, 256 + _pos.y} })
    {
        initPalette();
    }

    void initPalette();

    //virtual void draw() override;
    //virtual int mbDown(Vector mp, int button) override;
   // virtual int mbUp(Vector mp, int button) override;
    //virtual int onMouseMove(Vector mp, Vector delta) override;

};