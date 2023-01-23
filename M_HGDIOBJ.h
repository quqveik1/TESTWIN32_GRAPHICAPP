#pragma once
#include "Windows.h"

enum HGDIMANAGERBINDSTATUS
{
    BS_BINDED = 1,
    BS_UNBINDED = 0
};

struct M_HGDIOBJ
{
    HGDIOBJ obj = NULL;
    struct HGDIManager* gdiManager = NULL;
    struct AbstractAppData* app = NULL;
    int pNumber = -1;
    struct M_HDC* motherHDC = NULL;
    int status = 0; //1 - active  // 2+ selected
    const char* name = NULL;
    HGDIMANAGERBINDSTATUS bindStatus = BS_UNBINDED;

    M_HGDIOBJ(struct AbstractAppData* _app) :
        app(_app)
    {
        setApp(app);
    }

    M_HGDIOBJ()
    {

    }

    virtual int deleteObj();
    virtual HGDIOBJ setObj(HGDIOBJ  _obj);
    virtual int setApp(struct AbstractAppData* _app);
    virtual int unBind();
};