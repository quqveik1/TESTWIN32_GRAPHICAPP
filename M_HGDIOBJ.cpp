#pragma once
#include "M_HGDIOBJ.h"
#include "AppApi.h"
#include "HGDIManager.h"

int M_HGDIOBJ::deleteObj()
{
    if (obj)
    {
        if (status <= 0)
        {
            //printf("Попытка удалить уже удаленный холст\n");
            return (int)1;
        }
        else
        {
            
            if (status >= 2)
            {
                printf("Попытка удалить активный и выбранный где-то объект\n");
                return (int)1;
            }
            status--;
            DeleteObject(obj);
            status = 0;
            return 0;
        }
    }
    return -1;
}

HGDIOBJ M_HGDIOBJ::setObj(HGDIOBJ  _obj)
{
    if (status == 0)
    {
        obj = _obj;
        status = 1;
        return NULL;
    }
    printf("Попытка задать в оберточный класс, в котором уже выбран объект еще один объект\n");
    return obj;
    
}