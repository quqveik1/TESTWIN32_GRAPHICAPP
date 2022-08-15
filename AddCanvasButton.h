#pragma once
#include "SetCanvasButton.cpp"
#include "WindowsLib.cpp"

struct AddCanvasButton : Manager
{
    struct CanvasManager* canvasManager = NULL;
    SetCanvasButton setCanvasButton;
    const char* defaultCanvasName = "Холст";

    
    bool isEnterActive = false;


    AddCanvasButton(AbstractAppData* _app, struct CanvasManager* _canvasManager) :
        Manager(_app, {}, 1, true),
        canvasManager(_canvasManager),
        setCanvasButton(_app, canvasManager)
    {
        text = "Создать";
        //addWindow(&setCanvasButton);
    }

    virtual SetCanvasButton* getSetCanvasButton();

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
};