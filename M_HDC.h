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

    virtual int selectObj(M_HGDIOBJ* _obj, HBITMAP map);
    virtual int selectObj(HBITMAP map);
    virtual int selectObj(M_HGDIOBJ* _obj, HPEN pen);
    virtual int selectObj(HPEN pen);
    virtual int selectObj(M_HGDIOBJ* _obj, HBRUSH brush);
    virtual int selectObj(HBRUSH brush);
    virtual int selectObj(M_HGDIOBJ* _obj, HFONT font);
    virtual int selectObj(HFONT font);
    
    virtual int setSize(Vector size, struct AbstractAppData* app, RGBQUAD** pixels = NULL);
    virtual Vector getSize();

    virtual int deleteObj() override;
};

