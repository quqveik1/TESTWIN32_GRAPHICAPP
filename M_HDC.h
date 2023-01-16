#pragma once
#include "M_HGDIOBJ.h"
#include "Q_Vector.h"


struct M_HDC : M_HGDIOBJ
{
    M_HGDIOBJ* selectedObj[10] = {};
    HGDIOBJ defObjs[10] = {};
    int currLen = 0;

    M_HDC(struct AbstractAppData* _app);
    M_HDC(struct AbstractAppData* _app, HDC _dc);
    M_HDC();
    operator HDC() const;

    M_HDC& operator = (HDC _dc);
    int saveDefObjs();

    virtual int selectObj(M_HGDIOBJ* _obj, HBITMAP map);
    virtual int selectObj(HBITMAP map);
    virtual int selectObj(M_HGDIOBJ* _obj, HPEN pen);
    virtual int selectObj(HPEN pen);
    virtual int selectObj(M_HGDIOBJ* _obj, HBRUSH brush);
    virtual int selectObj(HBRUSH brush);
    virtual int selectObj(M_HGDIOBJ* _obj, HFONT font);
    virtual int selectObj(HFONT font);
    
    virtual int setSize(Vector size, struct AbstractAppData* _app, RGBQUAD** pixels = NULL);
    virtual int loadImage(struct AbstractAppData* _app, const char* _path, Vector _size = {});
    virtual int copyFrom(struct AbstractAppData* _app, HDC _dc);
    virtual Vector getSize();

    virtual Vector getViewPort(struct AbstractAppData* _app = NULL);
    virtual int setViewPort(Vector pos, struct AbstractAppData* _app = NULL);
    virtual int moveViewPort(Vector delta, struct AbstractAppData* _app = NULL);

    virtual int deleteObj() override;
    int clear();
};

