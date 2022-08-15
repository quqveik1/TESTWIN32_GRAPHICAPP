#pragma once
#include "FileSavings.h"

void CFileSavings::add(const char* path)
{
    if (currLen >= LEN)
    {
        printf("Невозможно добавить путь");
        return;
    }

    strcpy(paths[currLen], path);
    currLen++;
}


void CFileSavings::deleteAllFiles()
{
    int result = 0;
    for (int i = 0; i < currLen; i++)
    {
        result = remove(paths[i]);
    }
}