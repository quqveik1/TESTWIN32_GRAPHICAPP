#pragma once
#include "AbstractApp.h"



struct Lay
{
    struct AbstractAppData* app = NULL;

    HDC lay = NULL;
    Vector layCoordinats = {};
    Vector laySize = {};
    RGBQUAD* layBuf = {};
    HDC outputLay = NULL;
    RGBQUAD* outputBuf = {};
    bool isClicked = false;

    void createLay(AbstractAppData* _app, Vector size = {});
    int getDownUpCoordinats(int x, int y);
    virtual void clean(HDC dc = NULL);
    
    ~Lay();
};