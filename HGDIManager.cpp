#pragma once
#include "HGDIManager.h"
#include "M_HDC.cpp"

HGDIManager::~HGDIManager()
{
    int amountOfDeletedObjs = 0;
    for (int i = 0; i < (int)objs.size(); i++)
    {
        if (objs[i])
        {
            int wasntDeleted = objs[i]->deleteObj();
            if (wasntDeleted == 0) amountOfDeletedObjs++;
        }
    }

    for (int i = 0; i < (int)objs.size(); i++)
    {
        if (objs[i])
        {
            //delete objs[i];
        }
    }

    printf("Было удалено %d объектов, причем общее количество классов-обёрток составляет %d штук\n", amountOfDeletedObjs, (int)objs.size());

}

M_HDC* HGDIManager::getHDC()
{
    if (app)
    {
        M_HDC* newDC = new M_HDC(app);
        return newDC;
    }

    return NULL;
}

M_HGDIOBJ* HGDIManager::getHGDIOBJ()
{

    M_HGDIOBJ* newOBJ = new M_HGDIOBJ(app);
    return newOBJ;

    return NULL;
}



int HGDIManager::bind(M_HGDIOBJ* obj)
{
    objs.push_back(obj);
    //(void)printf("Теперь присоединено объектов: %ld\n", (int)objs.size());
    return 0;
}


int HGDIManager::unBind(M_HGDIOBJ* obj)
{
    //int timebefore = clock();

    short howManyDeleted = 0;
    for (int i = (int)objs.size() - 1; i >= 0; i--)
    {
        if (objs[i] == obj)
        {
            objs.erase(objs.begin() + i);
            howManyDeleted++;
        }
    }

    if (howManyDeleted == 0)
    {
        printf("Попытка отвязать незарегестрированный в мэнеджере объект\n");
        //DebugBreak();
        return -1;
    }
    else
    {
        return howManyDeleted;
    }
    
    /*
    
    while (it < objs.end())
    {
        it = find(it, objs.end(), obj);
        if (it < objs.end())
        {
            int pos = it - objs.begin();
            objs.erase(objs.begin() + pos);
            if (it < objs.end())
            {
                ++it;
                howManyDeleted++;
            }
            
            //int currTime = clock();
            //(void)printf("Отвязан объект, потрачено [%d]\n", currTime - timebefore);
        }
    }
    */
    /*
    short howManyDeleted = 0;;
    vector<M_HGDIOBJ*>::iterator it = find(objs.begin(), objs.end(), obj);
    while (it != objs.end())
    {
        if (*it == obj)
        {
            howManyDeleted++;
            int pos = it - objs.begin();
            objs.erase(objs.begin() + pos);
        }

        if(it < objs.end() - 1)it++;
    }

    
    
    */
    
    
}