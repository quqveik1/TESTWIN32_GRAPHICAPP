#pragma once
#include "LoadManager.h"
#include "AppApi.h"


HDC CLoadManager::loadImage(const char* path, Vector size /* = {} */)
{
    bool newImage = true;
    int suitableDCNum = -1;

    char fullPath[MAX_PATH] = {};
    sprintf(fullPath, "Files\\%s", path);

    for (int i = 0; i < currentImagesAmount; i++)
    {
        if (!strcmp(fullPath, images[i].path))
        {
            newImage = false;
            suitableDCNum = i;
            break;
        }
    }

    if (!newImage)
    {
        if (app->systemSettings->debugMode >= 4) (void)printf("Fullpath: %s; Result: %d\n", fullPath, (int)images[suitableDCNum].dc);
        if (app->systemSettings->debugMode >= 4) app->drawOnScreen (images[suitableDCNum].dc);
        return images[suitableDCNum].dc;
    }

    PowerPoint* extApp = (PowerPoint*)app;
    images[currentImagesAmount].dc = extApp->_loadImage(fullPath);
    if (app->systemSettings->debugMode == 4) (void)printf("Fullpath: %s; Result: %d\n", fullPath, (int)images[currentImagesAmount].dc);
    if (app->systemSettings->debugMode == 4) app->drawOnScreen (images[currentImagesAmount].dc);
    if (images[currentImagesAmount].dc == NULL)
    {
        _getch();
    }
    strcpy (images[currentImagesAmount].path, fullPath);
    images[currentImagesAmount].size = size;
    currentImagesAmount++;

    return images[currentImagesAmount - 1].dc;


}

int CLoadManager::deleteAllImages()
{
    int succesfullDeletedImagesAmount = 0;
    for (int i = 0; i < currentImagesAmount; i++)
    {
        int result = app->smartDeleteDC(images[i].dc);
        if (result) succesfullDeletedImagesAmount++;
    }
    if (app->systemSettings->debugMode > 0)printf("succesfullDeleteImagesAmount: %d\n", succesfullDeletedImagesAmount);
    return 0;
}

CLoadManager::~CLoadManager()
{
    int succesfullDeletedImagesAmount = 0;
    for (int i = 0; i < currentImagesAmount; i++)
    {
        int result = app->smartDeleteDC(images[i].dc);
        if (result) succesfullDeletedImagesAmount++;
    }
    if (app->systemSettings->debugMode > 0)printf("succesfullDeleteImagesAmount: %d\n", succesfullDeletedImagesAmount);
}
