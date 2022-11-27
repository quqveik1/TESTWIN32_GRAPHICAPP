#pragma once
#include "Menu.cpp"
#include "CanvasManager.h"





struct ToolsPalette : Menu
{
    Vector defaultSize = {};

    ToolsPalette(AbstractAppData* _app, Vector _pos, int _length) :
        defaultSize ({ appData->systemSettings->BUTTONWIDTH , (double)appData->toolManager->currentLength * 50 + appData->systemSettings->HANDLEHEIGHT }),
        Menu(_app, {.pos = _pos, .finishPos = {_pos.x + appData->systemSettings->BUTTONWIDTH, _pos.y + (double)appData->toolManager->currentLength * 50 + appData->systemSettings->HANDLEHEIGHT } }, { .pos = {0, 0}, .finishPos = {(double)_app->systemSettings->BUTTONWIDTH, (double)_app->systemSettings->HANDLEHEIGHT} }, _length, true)
    {
        Window** tools = new Window* [app->toolManager->currentLength];
        for (int i = 0; i < app->toolManager->currentLength; i++)
        {
            tools[i] = new Window(app);
        }

        for (int i = 0; i < app->toolManager->currentLength; i++)
        {
            tools[i]->rect = { .pos = {0, (double)i * 50}, .finishPos = {50, (double)(i + 1) * 50} };
            if (app->toolManager->tools[i])tools[i]->dc = app->toolManager->tools[i]->dc;
            tools[i]->finalDC.setSize(tools[i]->getSize(), app);
            tools[i]->originalRect = tools[i]->rect;
            addWindow(tools[i]);
            currentSize++;
        }

    }

    virtual void drawOneLine(int lineNum);
    virtual int  onClickLine(Vector mp);
};




//ћеню, которое будет позвол€ть управл€ть уже нарисованными на слое инструментами
struct ToolMenu : Menu
{
    struct CanvasManager* canvasManager = NULL;
    HDC emptyToolDC = NULL;

    Vector realEyeSize = {18, 13};
    Vector eyeSize = {};
    HDC eye = NULL;
    COLORREF hideColor = RGB (60, 60, 60);


    ToolMenu(AbstractAppData* _app, CanvasManager* _canvasManager) :
        Menu(_app, { .pos = {_app->systemSettings->SizeOfScreen.x - 300, 300}, .finishPos = {_app->systemSettings->SizeOfScreen.x - 5, _app->systemSettings->ONELAYTOOLSLIMIT * _app->systemSettings->BUTTONHEIGHT} }, {}, _app->systemSettings->ONELAYTOOLSLIMIT, true),
        canvasManager(_canvasManager),
        eyeSize({ app->systemSettings->BUTTONWIDTH, app->systemSettings->BUTTONHEIGHT }),
        eye (app->loadManager->loadImage ("Eye.bmp"))
    {
        assert(app);
        loadManager = app->loadManager;;
        emptyToolDC = loadManager->loadImage("addToolButton2.bmp");



        app->setColor(color, finalDC);
        app->rectangle(0, 0, rect.finishPos.x, rect.finishPos.y, finalDC);
        font = std::lround (_app->systemSettings->MainFont);
        app->selectFont(_app->systemSettings->FONTNAME, font, finalDC);
        
        handle.rect = { .pos = {0, 0}, .finishPos = {getSize().x, app->systemSettings->HANDLEHEIGHT} };
        handle.resize(handle.rect);
        handle.rect.finishPos.x = rect.getSize().x;
        handle.text = "»нструменты на слое";
        handle.color = color;
        handle.font = app->systemSettings->MainFont;
    }


    Rect getLineRect(int numberOfLine);
    Rect getEyeRect(Rect lineRect);

    virtual void onUpdate();
    virtual void drawOneLine(int lineNum);
    virtual int  onClickLine(Vector mp);

};
