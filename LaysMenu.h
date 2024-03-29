#pragma once
#include "CanvasManager.h"  
#include "Menu.cpp"


struct LaysMenu : Menu
{
    CanvasManager* canvasManager;
    int sectionHeight;
    int sectionFont;
    HDC addNewLayButton;
    Vector buttonSize;
    int needToCreateLay = false;

    LaysMenu(AbstractAppData* _app, Vector _pos, CanvasManager* _canvasManager) :
        Menu(_app, { .pos = _pos, .finishPos = {_pos.x + appData->systemSettings->BUTTONWIDTH * 2, _pos.y} }, {}, _app->systemSettings->ONELAYTOOLSLIMIT, true),
        canvasManager(_canvasManager),
        sectionHeight(systemSettings->HANDLEHEIGHT),
        sectionFont(sectionHeight - 4),
        addNewLayButton(_app->loadManager->loadImage("AddNewCanvas2.bmp")),
        buttonSize({ _app->systemSettings->BUTTONWIDTH, _app->systemSettings->HANDLEHEIGHT })
    {
        needToControlHandleInDefaultFuncs = 1;
        handle.resize({ .pos = {0, 0}, .finishPos = {rect.getSize().x, _app->systemSettings->HANDLEHEIGHT} });
        handle.color = color;
        handle.text = "����";
        handle.font = app->systemSettings->MainFont;
        rect.finishPos.y = rect.pos.y + handle.rect.getSize().y;
    }

    //virtual void draw() override;
    //virtual void onClick(Vector mp) override;
};