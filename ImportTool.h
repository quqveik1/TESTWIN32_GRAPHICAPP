#pragma once
#include "Tool.cpp"
#include "CopyDC.cpp"

struct ImportTool : CopyDC
{

    ImportTool(AbstractAppData* _app) :
        CopyDC(NULL, "Вставка изображения", _app->loadManager->loadImage("ImportDC.bmp"), _app)
    {
    }

    virtual long use(ToolLay* lay) override;
    

};