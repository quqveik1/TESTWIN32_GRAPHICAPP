#pragma once
#include "M_HDC.h"
#include "M_HGDIOBJ.h"
#include "HGDIManager.h"
#include "AbstractApp.h"
#include "AppApi.h"

M_HDC::M_HDC() :
    app(NULL)
{
    obj = CreateCompatibleDC(NULL);
    SetBkMode((HDC)obj, TRANSPARENT);
    defObjs[0] = GetCurrentObject((HDC)obj, OBJ_BITMAP);
    defObjs[1] = GetCurrentObject((HDC)obj, OBJ_PEN);
    defObjs[2] = GetCurrentObject((HDC)obj, OBJ_BRUSH);
    defObjs[3] = GetCurrentObject((HDC)obj, OBJ_FONT);
}

M_HDC::operator HDC() const
{
    return (HDC)obj;
}

int M_HDC::selectObj(M_HGDIOBJ* _obj, HBITMAP map)
{
    if (_obj->status >= 1)
    {
        int wasntDelete = NULL;
        if (selectedObj[0]) wasntDelete = selectedObj[0]->deleteObj();
        selectedObj[0] = _obj;
        SelectObject((HDC)obj, map);
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(M_HGDIOBJ* _obj, HPEN pen)
{
    if (_obj->status >= 1)
    {
        int wasntDelete = NULL;
        if (selectedObj[1]) wasntDelete = selectedObj[1]->deleteObj();
        selectedObj[1] = _obj;
        SelectObject((HDC)obj, pen);
        return !wasntDelete;
    }
    return -1;
} 

int M_HDC::selectObj(M_HGDIOBJ* _obj, HBRUSH brush)
{
    if (_obj->status >= 1)
    {
        int wasntDelete = NULL;
        if (selectedObj[2]) wasntDelete = selectedObj[2]->deleteObj();
        selectedObj[2] = _obj;
        SelectObject((HDC)obj, brush);
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(M_HGDIOBJ* _obj, HFONT font)
{
    if (_obj->status >= 1)
    {
        int wasntDelete = NULL;
        if (selectedObj[3]) wasntDelete = selectedObj[3]->deleteObj();
        selectedObj[3] = _obj;
        SelectObject((HDC)obj, font);
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::setSize(Vector size, struct AbstractAppData* _app, RGBQUAD** pixels/* = NULL*/)
{
    BITMAPINFO info = { { sizeof(info), size.x, size.y, 1, WORD(sizeof(RGBQUAD) * 8), BI_RGB } };
    HBITMAP bmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void**)pixels, NULL, 0);
    if (!bmap)
    {
        printf("bitmap � �������� %s �� ���������(\n", size.getStr());
        return 0;
    }
    app = _app;
    assert(app);
    M_HGDIOBJ* objs = app->getHGDIOBJ();
    objs->setObj(bmap);
    selectObj(objs, bmap);
    return (int)bmap;
}

int M_HDC::deleteObj()
{
    int numOfDeletedObjs = 0;
    for (int i = 0; i < 4; i++)
    {
        SelectObject((HDC)obj, defObjs[i]);
        int wasnotDeleted = selectedObj[i]->deleteObj();
        if (!wasnotDeleted) numOfDeletedObjs++;
    }
    return numOfDeletedObjs;
}