#pragma once

#include "SystemSettings.h"
#include "AbstractApp.h"

struct Image
{
    char path[MAX_PATH] = {};
	HDC dc = NULL;
    Vector size = {};
};

struct CLoadManager
{
    AbstractAppData* app;

	int currentImagesAmount = 0;

	Image images[1000];

    CLoadManager(AbstractAppData* _app) :
        app (_app)
    {}

    ~CLoadManager();



    virtual HDC loadImage(const char* path, Vector size = {}); //needToremember = 0 if it used once and you will delete it after call.
    int deleteAllImages();
};
