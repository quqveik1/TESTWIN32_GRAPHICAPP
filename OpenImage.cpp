#pragma once
#include "OpenImage.h"
#include "CanvasManager.h"


void OpenImage::draw()
{
    if (needToShow)
    {
        needToShow = false;
        
        const char* pathToSave = app->getOpenFileName("Место хранения изображения", "All Images (*.bmp;*.png;*.jpg)\0*.bmp;*.png;*.jpg\0Image (*.bmp)\0*.bmp\0Image (*.png)\0*.png\0Image (*.jpg)\0*.jpg\0");
        char fullPath[MAX_PATH] = {};
        if (pathToSave)strcpy(fullPath, pathToSave);

        if (fullPath[0])
        {
            if (importImage)
            {
                Vector newDCSize = {};
                HDC dc = importImage(fullPath, newDCSize, app);
                if (!dc)
                {
                    app->messageBox("Ничего не загрузилось", "Ошибка", MB_OK);
                    return;
                }

                assert(app->canvasManager);
                Vector sizeOfDC = app->getHDCSize(dc);

                const char* lastName = getlastNameOfFile(fullPath);
                if (!lastName)
                {
                    app->messageBox("Ошибка в имени файла", "Ошибка", MB_OK);
                    return;
                }

                app->canvasManager->addCanvas(lastName, sizeOfDC);
                Canvas* activeCanvas = app->canvasManager->getActiveCanvas();

                if (!activeCanvas)
                {
                    app->messageBox("Холст не создался", "Ошибка", MB_OK);
                    return;
                }

                activeCanvas->importImage(dc);
            }
        }
    }
}


const char* OpenImage::getlastNameOfFile(const char* file)
{
    int fileLength = strlen(file);

    for (int i = fileLength - 1; i >= 0; i--)
    {
        if (file[i] == '\\')
        {
            return &file[i + 1];
        }
    }

    return NULL;
}

