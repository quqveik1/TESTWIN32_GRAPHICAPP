#pragma once
#include "M_HDC.h"
#include "M_HGDIOBJ.h"
#include "HGDIManager.h"
#include "AbstractApp.h"
#include "AppApi.h"
#include "LoadManager.h"

M_HDC::M_HDC(struct AbstractAppData* _app) : 
    app(_app)
{
    obj = CreateCompatibleDC(NULL);
    SetBkMode((HDC)obj, TRANSPARENT);
    saveDefObjs();
}

M_HDC::M_HDC(struct AbstractAppData* _app, HDC _dc) : 
    app(_app)
{
    *this = _dc;
}



M_HDC::M_HDC() :
    app(NULL)
{
    obj = CreateCompatibleDC(NULL);
    SetBkMode((HDC)obj, TRANSPARENT);
    saveDefObjs();
}

M_HDC::operator HDC() const
{
    return (HDC)obj;
}

M_HDC& M_HDC::operator = (HDC _dc)
{
    deleteObj();
    setObj(_dc);
    saveDefObjs();
    return *this;
}


int M_HDC::saveDefObjs()
{
    defObjs[0] = GetCurrentObject((HDC)obj, OBJ_BITMAP);
    defObjs[1] = GetCurrentObject((HDC)obj, OBJ_PEN);
    defObjs[2] = GetCurrentObject((HDC)obj, OBJ_BRUSH);
    defObjs[3] = GetCurrentObject((HDC)obj, OBJ_FONT);
    return 1;
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

int M_HDC::selectObj(HBITMAP map)
{
    if (map)
    {
        int wasntDelete = NULL;
        if (selectedObj[0]) wasntDelete = selectedObj[0]->deleteObj();
        if (!wasntDelete && selectedObj[0])
        {
            selectedObj[0]->setObj(map);
        }
        else
        {
            M_HGDIOBJ* newObj = app->getHGDIOBJ();
            newObj->setObj(map);
            selectedObj[0] = newObj;
        }
        HGDIOBJ res = SelectObject((HDC)obj, map);
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

int M_HDC::selectObj(HPEN pen)
{
    if (pen)
    {
        int wasntDelete = NULL;
        if (selectedObj[1]) wasntDelete = selectedObj[1]->deleteObj();
        if (!wasntDelete && selectedObj[1])
        {
            selectedObj[1]->setObj(pen);
        }
        else
        {
            M_HGDIOBJ* newObj = app->getHGDIOBJ();
            newObj->setObj(pen);
            selectedObj[1] = newObj;
        }
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

int M_HDC::selectObj(HBRUSH brush)
{
    if (brush)
    {
        int wasntDelete = NULL;
        if (selectedObj[2]) wasntDelete = selectedObj[2]->deleteObj();
        if (!wasntDelete && selectedObj[2])
        {
            selectedObj[2]->setObj(brush);
        }
        else
        {
            gassert(app);
            if (app)
            {
                M_HGDIOBJ* newObj = app->getHGDIOBJ();
                newObj->setObj(brush);
                selectedObj[2] = newObj;
            }
        }
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

int M_HDC::selectObj(HFONT font)
{
    if (font)
    {
        int wasntDelete = NULL;
        if (selectedObj[3]) wasntDelete = selectedObj[3]->deleteObj();
        if (!wasntDelete && selectedObj[3])
        {
            selectedObj[3]->setObj(font);
        }
        else
        {
            gassert(app);
            if (app)
            {
                M_HGDIOBJ* newObj = app->getHGDIOBJ();
                newObj->setObj(font);
                selectedObj[3] = newObj;
            }
        }
        SelectObject((HDC)obj, font);
        return !wasntDelete;
    }
    return -1;
}  


Vector M_HDC::getSize()
{
    HBITMAP _bitmap = (HBITMAP)GetCurrentObject((HDC)obj, OBJ_BITMAP);
    BITMAP bm = {};
    GetObject(_bitmap, sizeof(bm), (LPVOID)&bm);
    Vector answer = {};
    answer.x = bm.bmWidth;
    answer.y = bm.bmHeight;

    return answer;
}


int M_HDC::setApp(struct AbstractAppData* _app)
{
    app = _app;
    return (int)(long)app;
}


int M_HDC::setSize(Vector size, struct AbstractAppData* _app, RGBQUAD** pixels/* = NULL*/)
{
    if (size != getSize())
    {
        BITMAPINFO info = { { sizeof(info), std::lround (size.x), std::lround (size.y), 1, WORD(sizeof(RGBQUAD) * 8), BI_RGB } };
        HBITMAP bmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void**)pixels, NULL, 0);
        if (!bmap)
        {
            printf("bitmap с размером %s не создалась(\n", size.getStr());
            return 0;
        }
        setApp(_app);
        assert(app);
        selectObj(bmap);
        return (int)bmap;
    }

    return NULL;
    
}


int M_HDC::loadImage(struct AbstractAppData* _app, const char* _path, Vector _size /*={}*/)
{
    app = _app;
    if (app)
    {
        HDC _loadIMG = app->loadManager->loadImage(_path, _size);
        int res = copyFrom(app, _loadIMG);
        app->deleteDC(_loadIMG);
        return res;
    }
    return 0;

}

int M_HDC::copyFrom(struct AbstractAppData* _app, HDC _dc)
{
    app = _app;
    if (app)
    {
        Vector _dcsize = app->getHDCSize(_dc);
        setSize(_dcsize, app);
        app->bitBlt(*this, {}, {}, _dc);      
        return 1;
    }
    return 0;
}

int M_HDC::deleteObj()
{
    int numOfDeletedObjs = 0;
    for (int i = 0; i < 4; i++)
    {
        SelectObject((HDC)obj, defObjs[i]);
        if (selectedObj[i])
        {
            int wasnotDeleted = selectedObj[i]->deleteObj();
            if (!wasnotDeleted) numOfDeletedObjs++;
        }
    }
    return numOfDeletedObjs;
}