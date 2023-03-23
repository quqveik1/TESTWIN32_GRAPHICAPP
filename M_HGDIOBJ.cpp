#pragma once
#include "M_HGDIOBJ.h"
#include "AbstractApp.h"
#include "HGDIManager.h"

int M_HGDIOBJ::deleteObj()
{
    if (obj)
    {
        if (status <= 0)
        {
            (void)printf("������� ������� ��� ��������� �����\n");
            return (int)1;
        }
        else
        {
            
            if (status >= 2)
            {
                printf("������� ������� �������� � ��������� ���-�� ������\n");
                return (int)1;
            }
            unBind();
            status--;
            int res = DeleteObject(obj);
            status = 0;
            if (res == 0)
            {
                printf("������ �������� M_HGDIOBJ\n");
            }
            return 0;
        }
    }
    return -1;
}



int M_HGDIOBJ::unBind()
{
    if (app)
    {
        if (app->hgdiManager && bindStatus == BS_BINDED)
        {
            app->hgdiManager->unBind(this);
            bindStatus = BS_UNBINDED;
            return 0;
        }
        else
        {
            printf("������� ������� �� ���������, ���� � ���� � �� �������������\n");
            //DebugBreak();
        }
    }
    else
    {
        printf("��� ������� � �������� ����������!");
    }
    return 1;
}

HGDIOBJ M_HGDIOBJ::setObj(HGDIOBJ  _obj)
{
    if (status == 0)
    {
        obj = _obj;
        status = 1;
        return NULL;
    }
    printf("������� ������ � ���������� �����, � ������� ��� ������ ������ ��� ���� ������\n");
    return obj;
    
}


int M_HGDIOBJ::setApp(struct AbstractAppData* _app)
{
    if (_app != NULL)
    {
        app = _app;

        if (bindStatus == BS_UNBINDED)
        {
            app->hgdiManager->bind(this);
            bindStatus = BS_BINDED;
            return 0;
        }
    }
    return 1;
}