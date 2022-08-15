#pragma once
#include "DLLManager.h"

int findSymbol(const char* text, int size, char symbol)
{
    for (int i = 0; i < size; i++)
    {
        if (text[i] == symbol) return i + 1;
    }
    return 0;
}


bool DLLManager::loadLibs()
{
    int result = true;
    FILE* libsList = fopen(pathToDLLList, "r");
    if (!libsList) printf("%s �� ������\n", pathToDLLList);
    assert(libsList);

    for (int i = 0; ; i++)
    {
        char path[MAX_PATH] = {};

        if (!fscanf(libsList, "%s ", path)) break;
        if (path[0] == 0) break;
        int numOfStarSymbol = findSymbol(path, MAX_PATH, '*');
        if (numOfStarSymbol)
        {
            numOfStarSymbol--;
            path[numOfStarSymbol] = NULL;
            char pattern[100] = {};
            sprintf(pattern, "%s*.%s", path, fileExtension);

            struct _finddata_t fileinfo;
            int placeData = 0;


            for (int j = 0; ; j++)
            {
                int returnableValue = 0;
                if (j == 0)
                {
                    placeData = _findfirst(pattern, &fileinfo);
                    returnableValue = placeData;
                }
                if (j != 0)
                {
                    returnableValue = _findnext(placeData, &fileinfo);
                }
                if (returnableValue < 0) break;

                char fullPath[100] = {};

                assert(fileinfo.name);

                sprintf(fullPath, "%s%s", path, fileinfo.name);

                libs[currLen] = LoadLibrary(fullPath);
                result *= (int)libs[currLen];
                if (result) currLen++;

                if (appData->systemSettings->debugMode >= 0) printf("���� � ����������: %s\n", fullPath);
            }
        }
        else
        {
            int extensionPlace = findSymbol(path, MAX_PATH, '.');
            int resultOfExtensonComparision = strcmp(&path[extensionPlace], fileExtension);
            if (resultOfExtensonComparision == 0)
            {

                libs[currLen] = LoadLibrary(path);
                result *= (int)libs[currLen];
                if (libs[currLen]) currLen++;
            }

            if (appData->systemSettings->debugMode >= 0) printf("���� � ����������[%p]: %s\n", libs[currLen], path);
        }
    }
    if (appData->systemSettings->debugMode >= 0) printf("�����������(DLL) ����������� � exe\n");

    return result;
}


int DLLManager::getNumberOfLibs()
{
    return currLen;
}