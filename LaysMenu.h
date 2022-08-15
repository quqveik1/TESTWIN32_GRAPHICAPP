#pragma once
#include "CanvasManager.h"


struct LaysMenu : Manager
{
    CanvasManager* canvasManager;
    int sectionHeight;
    int sectionFont;
    HDC addNewLayButton;
    Vector buttonSize;
    int needToCreateLay = false;

    LaysMenu(AbstractAppData* _app, Rect _rect, CanvasManager* _canvasManager) :
        Manager(_app, _rect, 0, true, NULL, { .pos = {0, 0}, .finishPos = {_rect.getSize().x, _app->systemSettings->HANDLEHEIGHT} }),
        canvasManager(_canvasManager),
        sectionHeight(systemSettings->HANDLEHEIGHT),
        sectionFont(sectionHeight - 4),
        addNewLayButton(_app->loadManager->loadImage("AddNewCanvas2.bmp")),
        buttonSize({ _app->systemSettings->BUTTONWIDTH, _app->systemSettings->HANDLEHEIGHT })
    {
        rect.finishPos.y = rect.pos.y + handle.rect.getSize().y;
        handle.rect.finishPos.x = rect.getSize().x;
        handle.color = color;
        handle.text = "Слои";
        handle.font = app->systemSettings->MainFont;
    }

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
};