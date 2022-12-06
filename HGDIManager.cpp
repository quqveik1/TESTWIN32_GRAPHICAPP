#pragma once
#include "HGDIManager.h"
#include "M_HDC.cpp"

HGDIManager::~HGDIManager()
{
    int amountOfDeletedObjs = 0;
    for (int i = 0; i < currlen; i++)
    {
        if (objs[i])
        {
            int wasntDeleted = objs[i]->deleteObj();
            if (wasntDeleted == 0) amountOfDeletedObjs++;
        }
    }

    for (int i = 0; i < currlen; i++)
    {
        if (objs[i])
        {
            delete objs[i];
        }
    }

    printf("Было удалено %d объектов, причем общее количество классов-обёрток составляет %d штук\n", amountOfDeletedObjs, currlen);

}

M_HDC* HGDIManager::getHDC()
{
    if (app)
    {
        if (currlen + 1 < maxLen)
        {
            M_HDC* newDC = new M_HDC(app);
            objs[currlen] = newDC;
            currlen++;
            return newDC;
        }
        else
        {
            massert(!"Переполнение M_HGDIOBJ", app);
        }
    }

    return NULL;
}

M_HGDIOBJ* HGDIManager::getHGDIOBJ()
{
    if (currlen + 1 < maxLen)
    {
        M_HGDIOBJ* newOBJ = new M_HGDIOBJ();
        objs[currlen] = newOBJ;
        currlen++;
        printf("Выдана %d обертка\n", currlen);
        return newOBJ;
    }
    else
    {
        massert(!"Переполнение M_HGDIOBJ", app);
    }

    return NULL;
}