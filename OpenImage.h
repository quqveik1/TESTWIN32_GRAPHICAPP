#pragma once
#include "ImportImage.h"

struct OpenImage : ImportImage
{
    OpenImage(AbstractAppData* _app) :
        ImportImage(_app)
    {

    }

    const char* getlastNameOfFile(const char* file);

    virtual void draw() override;
};