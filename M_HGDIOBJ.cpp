#pragma once
#include "M_HGDIOBJ.h"
#include "AppApi.h"

int M_HGDIOBJ::deleteObj()
{
    if (obj)
    {
        if (status <= 0)
        {
            printf("������� ������� ��� ��������� �����\n");
            return (int)obj;
        }
        else
        {
            status--;
            if (status >= 2)
            {
                printf("������� ������� �������� � ��������� ���-�� ������\n");
                return (int)obj;
            }
            DeleteObject(obj);
            status = 0;
            return 0;
        }
    }
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