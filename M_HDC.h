#pragma once
#include "M_HGDIOBJ.h"
#include "Q_Vector.h"


struct M_HDC : M_HGDIOBJ
{
    M_HGDIOBJ* selectedObj[10] = {};
    HGDIOBJ defObjs[10] = {};
    int currLen = 0;
    struct AbstractAppData* app = NULL;

    M_HDC();
    operator HDC() const;

    virtual int selectObj(M_HGDIOBJ* _obj, HBITMAP brush);
    virtual int selectObj(M_HGDIOBJ* _obj, HPEN pen);
    virtual int selectObj(M_HGDIOBJ* _obj, HBRUSH brush);
    virtual int selectObj(M_HGDIOBJ* _obj, HFONT brush);
    
    virtual int setSize(Vector size, struct AbstractAppData* app, RGBQUAD** pixels = NULL);

    virtual int deleteObj() override;
};

