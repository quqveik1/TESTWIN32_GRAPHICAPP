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

    printf("���� ������� %d ��������, ������ ����� ���������� �������-������ ���������� %d ����\n", amountOfDeletedObjs, currlen);

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
    bind(newOBJ);
    return newOBJ;

    return NULL;
}



int HGDIManager::bind(M_HGDIOBJ* obj)
{
    objs.push_back(obj);
    //(void)printf("������ ������������ ��������: %ld\n", objs.size());
    return 0;
}


int HGDIManager::unBind(M_HGDIOBJ* obj)
{
    vector<M_HGDIOBJ*>::iterator it;
    //int timebefore = clock();
    it = find(objs.begin(), objs.end(), obj);
    if (it != objs.end())
    {
        int pos = it - objs.begin();
        objs.erase(objs.begin() + pos);
        //int currTime = clock();
        //(void)printf("������� ������, ��������� [%d]\n", currTime - timebefore);
        return 0;
    }
    
    printf("������� �������� �������������������� � ��������� ������\n");
    //DebugBreak();
    return -1;
    
}