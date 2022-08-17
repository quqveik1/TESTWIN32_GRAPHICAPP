#pragma once
#include "M_HGDIOBJ.h"
#include "Q_Vector.h"


struct M_HDC : M_HGDIOBJ
{
    M_HGDIOBJ* selectedObj[10] = {};
    HGDIOBJ defObjs[10] = {};
    int currLen = 0;

    M_HDC();

    virtual int selectObj(M_HGDIOBJ  _obj);
    virtual int setSize(Vector size, RGBQUAD** pixels = NULL);

    virtual int deleteObj() override;
    //virtual HGDIOBJ setObj(HGDIOBJ  _obj) override;
};