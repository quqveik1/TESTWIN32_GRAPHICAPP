#pragma once
#include "DLLManager.h"
#include "io.h"

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
    bool result = true;
    FILE* libsList = fopen(pathToDLLList, "r");
    if (!libsList)
    {
        printf("%s Не найден\n", pathToDLLList);
        return false;
    }
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

            _finddata_t fileinfo;
            long long placeData = 0;


            for (int j = 0; ; j++)
            {
                long long returnableValue = 0;
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
                if (libs[currLen]) currLen++;
                else result = false;

                if (appData->systemSettings->debugMode >= 0) printf("Путь к библиотеке: %s\n", fullPath);
            }
        }
        else
        {
            int extensionPlace = findSymbol(path, MAX_PATH, '.');
            int resultOfExtensonComparision = strcmp(&path[extensionPlace], fileExtension);
            if (resultOfExtensonComparision == 0)
            {

                libs[currLen] = LoadLibrary(path);
                if (libs[currLen]) currLen++;
                else result = false;
            }

            if (appData->systemSettings->debugMode >= 0) printf("Путь к библиотеке[%p]: %s\n", libs[currLen], path);
        }
    }
    if (appData->systemSettings->debugMode >= 0) printf("Инструменты(DLL) загрузились в exe\n");

    return result;
}


int DLLManager::getNumberOfLibs()
{
    return currLen;
}