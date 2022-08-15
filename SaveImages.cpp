#pragma once
#include "SaveImages.h"


void SaveImages::draw()
{
    if (needToShow)
    {
        //условие выхода если холст не создан
        Canvas* activeCanvas = canvasManager->getActiveCanvas();

        if (!activeCanvas)
        {
            app->messageBox("Нечего сохранять, холст не создан", "Ошибка", MB_OK);
            needToShow = false;
            return;
        }

        const char* pathToSave = app->getSaveFileName("Место сохранения изображения", "Image (*.bmp)\0*.bmp\0Image (*.png)\0*.png\0Image (*.jpg)\0*.jpg\0", activeCanvas->getName());
        char fullPath[MAX_PATH] = {};
        if (pathToSave)strcpy(fullPath, pathToSave);

        if (fullPath[0])
        {
            HDC saveDC = NULL;

            saveDC = activeCanvas->getImageForSaving();


            int wasErrorInSavings = 0;
            if (saveDC)
            {
                if (saveImage)
                {
                    wasErrorInSavings = saveImage(saveDC, fullPath);
                }
            }


            //int result = app->saveImage(saveDC, fullPath);
            app->deleteDC(saveDC);


            if (wasErrorInSavings) app->messageBox("Ничего не сохранилось", "Ошибка", MB_OK);
        }
    }

    needToShow = false;
}


