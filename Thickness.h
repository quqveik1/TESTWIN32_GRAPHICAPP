#pragma once
#include "Slider2.cpp"
#include "InputButton.cpp"

struct ThicknessMenu : Manager
{
    Slider2* slider = NULL;
    InputButton2* inputButton = NULL;
    Vector inputButtonSize = {};
    int minThickness = 1;
    int maxThickness = 100;
    Vector buttonSize = {400, 70};
    Vector sliderSize = {};


    ThicknessMenu(AbstractAppData* _app, Vector _pos, bool _advancedMode) :
        Manager(_app, {}, 2, _advancedMode, NULL, {}),
        inputButtonSize({50, getSize().y})
    {
        needToControlHandleInDefaultFuncs = 1;
        Rect newRect = { .pos = _pos, .finishPos = _pos + buttonSize };
        resize(newRect);

        handle.rect = { .pos = {0, 0}, .finishPos = {getSize().x, app->systemSettings->HANDLEHEIGHT} };
        handle.resize(handle.rect);
        handle.rect.finishPos.x = rect.getSize().x;
        handle.text = "Толщина";
        handle.color = color;
        handle.font = app->systemSettings->MainFont;

        Rect rectWithOutHandle = { .pos = {0, handle.rect.finishPos.y}, .finishPos = getSize() };

        sliderSize = {getSize().x - (inputButtonSize.x + 5), 15};
        Rect sliderRect = rectWithOutHandle;
        Vector rectWithOutHandleSize = rectWithOutHandle.getSize();
        sliderRect.finishPos.x -= inputButtonSize.x + 5;
        sliderRect.pos.y = (rectWithOutHandleSize.y - sliderSize.y) / 2 + handle.rect.finishPos.y;
        sliderRect.finishPos.y = sliderRect.pos.y + sliderSize.y;
        
        slider = new Slider2(app, sliderRect, &app->systemSettings->Thickness, &minThickness, &maxThickness, NULL);
        addWindow(slider);

        Rect inputButtonRect = { .pos = {sliderRect.finishPos.x + 5, sliderRect.pos.y}, .finishPos = {getSize().x - 5,  getSize().y - 5} };
        inputButton = new InputButton2(app, inputButtonRect, &app->systemSettings->Thickness, &minThickness, &maxThickness, 0, color, RGB(144, 144, 144), RGB(200, 200, 200));
        addWindow(inputButton);
    }

    virtual void draw();
    virtual void onClick(Vector mp);
};