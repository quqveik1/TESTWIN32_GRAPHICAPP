#pragma once
#include "AbstractApp.h"



struct Lay
{
    struct AbstractAppData* app = NULL;

    M_HDC lay;
    Vector layCoordinats = {};
    Vector laySize = {};
    RGBQUAD* layBuf = {};
    M_HDC outputLay;
    RGBQUAD* outputBuf = {};
    bool isClicked = false;

    void createLay(AbstractAppData* _app, Vector size = {});
    int getDownUpCoordinats(int x, int y);
    virtual void clean(M_HDC dc);
    
    ~Lay();
};