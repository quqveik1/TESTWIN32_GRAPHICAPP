#pragma once
#include "M_HDC.h"
#include "M_HGDIOBJ.cpp"

M_HDC::M_HDC()
{
    obj = CreateCompatibleDC(NULL);
    defObjs[0] = GetCurrentObject((HDC)obj, OBJ_BITMAP);
    defObjs[1] = GetCurrentObject((HDC)obj, OBJ_PEN);
    defObjs[2] = GetCurrentObject((HDC)obj, OBJ_BRUSH);
    defObjs[3] = GetCurrentObject((HDC)obj, OBJ_FONT);
}

int M_HDC::selectObj(M_HGDIOBJ* _obj, HBITMAP map)
{
    if (_obj->status >= 1)
    {
        int wasntDelete = selectedObj[0]->deleteObj();
        selectedObj[0] = _obj;
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(M_HGDIOBJ* _obj, HPEN pen)
{
    if (_obj->status >= 1)
    {
        int wasntDelete = selectedObj[1]->deleteObj();
        selectedObj[1] = _obj;
        return !wasntDelete;
    }
    return -1;
} 

int M_HDC::selectObj(M_HGDIOBJ* _obj, HBRUSH brush)
{
    if (_obj->status >= 1)
    {
        int wasntDelete = selectedObj[2]->deleteObj();
        selectedObj[2] = _obj;
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(M_HGDIOBJ* _obj, HFONT font)
{
    if (_obj->status >= 1)
    {
        int wasntDelete = selectedObj[3]->deleteObj();
        selectedObj[3] = _obj;
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::setSize(Vector size, RGBQUAD** pixels/* = NULL*/)
{
    BITMAPINFO info = { { sizeof(info), size.x, size.y, 1, WORD(sizeof(RGBQUAD) * 8), BI_RGB } };
    HBITMAP bmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void**)pixels, NULL, 0);
    if (!bmap)
    {
        printf("bitmap с размером %s не создалась(\n", size.getStr());
        return 0;
    }
    SelectObject((HDC)obj, bmap);
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