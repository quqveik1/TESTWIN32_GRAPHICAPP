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

    int _imagepos = currentImagesAmount;
    if (!newImage)
    {
        HDC suitableDC = images[suitableDCNum].dc;
        if (app->systemSettings->debugMode >= 4) (void)printf("Fullpath: %s; Result: %d\n", fullPath, (int)images[suitableDCNum].dc);
        if (app->systemSettings->debugMode >= 4) app->drawOnScreen(images[suitableDCNum].dc);
        COLORREF _color = app->getPixel({ 1, 1 }, suitableDC);
        if (_color != CLR_INVALID)
        {
            return images[suitableDCNum].dc;
        }
        _imagepos = suitableDCNum;
    }   

    //PowerPoint* extApp = (PowerPoint*)app;
    images[_imagepos].dc = app->loadImage(fullPath);
    strcpy (images[_imagepos].path, fullPath);
    images[_imagepos].size = size;
    if (images[_imagepos].dc == NULL)
    {
        (void)printf("Картинка из [%s] не загрузилась\n", fullPath);
        images[_imagepos].dc = app->createDIBSection({ 100, 100 });
        M_HDC* _m_hdc = app->getHDC();
        _m_hdc->setObj(images[_imagepos].dc);
        app->setColor(C_RED, *_m_hdc);
        app->rectangle({}, {100, 100}, *_m_hdc);
    }
    if (newImage)
    {
        currentImagesAmount++;
    }

    return images[_imagepos].dc;


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
