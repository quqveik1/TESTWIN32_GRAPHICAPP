#pragma once
#include "AbstractApp.h"
#include "M_HGDIOBJ.h"
#include "M_HDC.h"
#include "AbstractApp.h"

enum Status_M_HGDI
{
    S_DIDNTCREATED = -1,
    S_ACTIVE = 1,
    S_DELETED = 0
};


struct HGDIManager
{
    AbstractAppData* app = NULL;

    int currlen = 0;
    static const int maxLen = 100000;
    //M_HGDIOBJ* objs[maxLen] = {};
    vector <M_HGDIOBJ*> objs{};

    HGDIManager(AbstractAppData* _app) :
        app (_app)
    {
    }
    ~HGDIManager();

    virtual M_HDC* getHDC();
    virtual int bind(M_HGDIOBJ* obj);
    virtual int unBind(M_HGDIOBJ* obj);
    virtual M_HGDIOBJ* getHGDIOBJ();
}; ;