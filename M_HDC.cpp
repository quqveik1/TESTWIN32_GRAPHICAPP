#pragma once
#include "M_HDC.h"
#include "M_HGDIOBJ.h"
#include "HGDIManager.h"
#include "AbstractApp.h"
#include "AppApi.h"
#include "LoadManager.h"

M_HDC::M_HDC(struct AbstractAppData* _app) : 
    M_HGDIOBJ(_app)
{
    obj = CreateCompatibleDC(NULL);
    SetBkMode((HDC)obj, TRANSPARENT);
    saveDefObjs();
}

M_HDC::M_HDC(struct AbstractAppData* _app, HDC _dc) : 
    M_HGDIOBJ(_app)
{
    obj = _dc;
}



M_HDC::M_HDC() :
    M_HGDIOBJ(NULL)
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
    if (_dc != obj)
    {
        deleteObj();
        setApp(app);
        setObj(_dc);
        saveDefObjs();
    }
    return *this;
}

M_HDC::~M_HDC()
{
    deleteObj();
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
    if (!app)
    {
        printf("ѕопытка графический действий на M_HDC без доступа к приложению[%p]", this);
        return-1;
    }

    if (_obj->status >= 1)
    {
        int wasntDelete = NULL;
        if (selectedObj[0]) wasntDelete = selectedObj[0]->deleteObj();
        selectedObj[0] = _obj;
        SelectObject((HDC)obj, map);
        selectedObj[0]->setApp(app);
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(HBITMAP map)
{
    if (!app)
    {
        printf("ѕопытка графический действий на M_HDC без доступа к приложению[%p]", this);
        return-1;
    }

    const int itemNum = 0;
    if (map)
    {
        HGDIOBJ res = SelectObject((HDC)obj, map);
        int wasntDelete = NULL;
        if (selectedObj[itemNum])
        {
            selectedObj[itemNum]->deleteObj();
            selectedObj[itemNum]->setObj(map);
            selectedObj[itemNum]->setApp(app); 
        }
        else
        {
            M_HGDIOBJ* newObj = app->getHGDIOBJ();
            newObj->setObj(map);
            selectedObj[itemNum] = newObj;
        }
        
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
        selectedObj[1]->setApp(app);
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(HPEN pen)
{
    if (!app)
    {
        printf("ѕопытка графический действий на M_HDC без доступа к приложению[%p]", this);
        return-1;
    }

    const int itemNum = 1;
    if (pen)
    {
        HGDIOBJ res = SelectObject((HDC)obj, pen);
        int wasntDelete = NULL;
        if (selectedObj[itemNum])
        {
            selectedObj[itemNum]->deleteObj();
            selectedObj[itemNum]->setObj(pen);
            selectedObj[itemNum]->setApp(app);
        }
        else
        {
            M_HGDIOBJ* newObj = app->getHGDIOBJ();
            newObj->setObj(pen);
            selectedObj[itemNum] = newObj;
        }

        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(M_HGDIOBJ* _obj, HBRUSH brush)
{
    if (!app)
    {
        printf("ѕопытка графический действий на M_HDC без доступа к приложению[%p]", this);
        return-1;
    }

    if (_obj->status >= 1)
    {
        int wasntDelete = NULL;
        if (selectedObj[2]) wasntDelete = selectedObj[2]->deleteObj();
        selectedObj[2] = _obj;
        SelectObject((HDC)obj, brush);
        selectedObj[2]->setApp(app);
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(HBRUSH brush)
{
    if (!app)
    {
        printf("ѕопытка графический действий на M_HDC без доступа к приложению[%p]", this);
        return-1;
    }

    const int itemNum = 2;
    if (brush)
    {
        HGDIOBJ res = SelectObject((HDC)obj, brush);
        int wasntDelete = NULL;
        if (selectedObj[itemNum])
        {
            selectedObj[itemNum]->deleteObj();
            selectedObj[itemNum]->setObj(brush);
            selectedObj[itemNum]->setApp(app);
        }
        else
        {
            M_HGDIOBJ* newObj = app->getHGDIOBJ();
            newObj->setObj(brush);
            selectedObj[itemNum] = newObj;
        }

        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(M_HGDIOBJ* _obj, HFONT font)
{
    if (!app)
    {
        printf("ѕопытка графический действий на M_HDC без доступа к приложению[%p]", this);
        return-1;
    }

    if (_obj->status >= 1)
    {
        int wasntDelete = NULL;
        if (selectedObj[3]) wasntDelete = selectedObj[3]->deleteObj();
        selectedObj[3] = _obj;
        SelectObject((HDC)obj, font);
        selectedObj[3]->setApp(app);
        return !wasntDelete;
    }
    return -1;
}

int M_HDC::selectObj(HFONT font)
{
    if (!app)
    {
        printf("ѕопытка графический действий на M_HDC без доступа к приложению[%p]", this);
        return-1;
    }

    const int itemNum = 3;
    if (font)
    {
        HGDIOBJ res = SelectObject((HDC)obj, font);
        int wasntDelete = NULL;
        if (selectedObj[itemNum])
        {
            selectedObj[itemNum]->deleteObj();
            selectedObj[itemNum]->setObj(font);
            selectedObj[itemNum]->setApp(app);
        }
        else
        {
            M_HGDIOBJ* newObj = app->getHGDIOBJ();
            newObj->setObj(font);
            selectedObj[itemNum] = newObj;
        }

        return !wasntDelete;
    }
    return -1;
}  

Vector M_HDC::getViewPort(struct AbstractAppData* _app/* = NULL*/)
{
    setApp(_app);
    if (!app)
    {
        assert(!"ќпераци€ не может быть выполнена без доступа к классу приложени€");
        return {};
    }
    Vector answer = {};
    app->getViewPort((HDC)obj, &answer);
    return answer;
} 

int M_HDC::setViewPort(Vector pos, struct AbstractAppData* _app/* = NULL*/)
{
    setApp(_app);
    if (!app)
    {
        assert(!"ќпераци€ не может быть выполнена без доступа к классу приложени€");
        return 0;
    }
    return app->setViewPort((HDC)obj, pos);
}          

int M_HDC::moveViewPort(Vector delta, struct AbstractAppData* _app/* = NULL*/)
{
    setApp(_app);
    if (!app)
    {
        assert(!"ќпераци€ не может быть выполнена без доступа к классу приложени€");
        return 0;
    }
    Vector oldPos = {};
    app->getViewPort((HDC)obj, &oldPos);

    oldPos += delta;

    return app->setViewPort((HDC)obj, oldPos);


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





int M_HDC::setSize(Vector size, struct AbstractAppData* _app, RGBQUAD** pixels/* = NULL*/)
{
    Vector currSize = getSize();
    size.round();
    if (size != currSize)
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
    else
    {
        printf("ѕопытка графический действий на M_HDC без доступа к приложению[%p]", this);
        return-1;
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


int M_HDC::clear()
{
    int numOfDeletedObjs = 0;
    for (int i = 1; i < 4; i++)
    {
        SelectObject((HDC)obj, defObjs[i]);
        if (selectedObj[i])
        {
            int wasnotDeleted = selectedObj[i]->deleteObj();
            if (!wasnotDeleted) numOfDeletedObjs++;
            selectedObj[i] = NULL;
        }
    }
    return numOfDeletedObjs;
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

    if (app) app->deleteDC((HDC)obj);

    unBind();
    return numOfDeletedObjs;


}