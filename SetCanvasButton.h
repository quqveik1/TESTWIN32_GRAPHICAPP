#pragma once
#include "DrawBibliothek.h"
#include "InputButton.cpp"
#include "StringButton2.cpp"
#include "CanvasManager.h"


struct SetCanvasButton : Manager
{
    CanvasManager* canvasManager = NULL;
    const char* defaultCanvasName = "Холст";
    Vector defaultCanvasSize = { 500, 500 };
    Vector newCanvasSize = {};

    Vector size = { 300, 200 };
    Vector oneLineSize = { rect.getSize().x - rect.getSize().x * 0.2, 25 };
    Vector inputButtonSize = { 50, 25 };
    Rect sizeXText = {};
    Rect sizeYText = {};
    double deltaYFromHandle = 10;
    double deltaBetweenSizes = 5;
    int sizeX = 0;
    int sizeY = 0;
    int minSize = 0;
    int maxSize = 1000;
    InputButton2 inputX;
    InputButton2 inputY;
    double downSectionPosY = 0;
    Vector buttonPos = {};
    Vector buttonSize = { app->systemSettings->BUTTONWIDTH + 20, 25 };
    double deltaBetweenButtons = 10;
    Rect confirmButton = {};
    Rect cancelButton = {};

    
    char canvasName[MAX_PATH] = {};
    Vector inputNameSize = { getSize().x - 0.1 * getSize().x, 25 };
    Rect nameTextRect = {};
    StringButton2 inputName;
    int enterStatus = false;

    SetCanvasButton(AbstractAppData* _app, CanvasManager* _canvasManager) :
        size ({ 300, 200 }),
        Manager(_app, { .pos = {}, .finishPos = {300, 200} }, 3, false, NULL, {}, _app->systemSettings->MenuColor),
        canvasManager (_canvasManager),
        inputX(app, { .pos = {}, .finishPos = inputButtonSize }, &sizeX, &minSize, &maxSize, 0, app->systemSettings->TRANSPARENTCOLOR),
        inputY(app, { .pos = {}, .finishPos = inputButtonSize }, &sizeY, &minSize, &maxSize, 0, app->systemSettings->TRANSPARENTCOLOR),
        inputName(app, { .pos = {}, .finishPos = {inputNameSize.x, inputNameSize.y} }, canvasName, MAX_PATH, app->systemSettings->TRANSPARENTCOLOR)
    {
        assert (app);
        handle.resize({ .pos = {}, .finishPos = {getSize().x, app->systemSettings->HANDLEHEIGHT } });
        handle.text = "Создать холст";
        handle.font = 30;
        format = DT_LEFT;

        Vector centralizedPos = app->getCentrizedPos(oneLineSize, size);
        sizeXText = { .pos = {centralizedPos.x, handle.rect.finishPos.y + deltaYFromHandle}, .finishPos =  {centralizedPos.x + (oneLineSize.x - inputButtonSize.x), handle.rect.finishPos.y + deltaYFromHandle  + oneLineSize.y} };
        sizeYText = { .pos = {centralizedPos.x, sizeXText.finishPos.y   + deltaBetweenSizes}, .finishPos = {centralizedPos.x + (oneLineSize.x - inputButtonSize.x), sizeXText.finishPos.y   + deltaBetweenSizes + oneLineSize.y} };

        inputX.MoveWindowTo({ sizeXText.finishPos.x,  sizeXText.pos.y });
        inputY.MoveWindowTo({ sizeYText.finishPos.x,  sizeYText.pos.y });

        
        addWindow(inputX);
        addWindow(inputY);

        downSectionPosY = getSize().y - 40;
        buttonPos.y = downSectionPosY + (((getSize().y - downSectionPosY) - buttonSize.y)) * 0.5;
        confirmButton = { .pos = {(getSize().x - deltaBetweenButtons) * 0.5 - buttonSize.x, buttonPos.y}, .finishPos = {(getSize().x - deltaBetweenButtons) * 0.5, buttonPos.y + buttonSize.y} };
        cancelButton = { .pos = {(getSize().x + deltaBetweenButtons) * 0.5, buttonPos.y}, .finishPos = {(getSize().x + deltaBetweenButtons) * 0.5 + buttonSize.x, buttonPos.y + buttonSize.y} };

        Vector inputCentrizedPos = app->getCentrizedPos(inputName.getSize(), getSize());
        inputName.MoveWindow({ inputCentrizedPos.x,  downSectionPosY - inputName.getSize().y - 5 });
        addWindow(inputName);
        nameTextRect = { .pos = {centralizedPos.x, inputName.rect.pos.y - oneLineSize.y - 5}, .finishPos = {centralizedPos.x + oneLineSize.x, inputName.rect.pos.y - 5} };
        
    }


    void confirmEnter();
    void cancelEnter();

    virtual int isResultEntered();
    virtual char* getNewCanvasName();

    virtual void show();

    virtual void draw() override;
    virtual void print(HDC dc) override;
    virtual void onClick(Vector mp) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
    virtual int onKeyboard(int key) override;
   
};