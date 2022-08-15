#pragma once
#include "Slider2.cpp"
#include "InputButton.cpp"
#include "InputButton2.cpp"


struct ColorComponentChanger : Manager
{
    int* component = NULL;
    int copyVersionOfCompoment = 0;
    Slider2* slider = NULL;
    InputButton2* inputButton = NULL;
    Rect sliderRect = {};
    Vector sliderSize = { 0, 15 };
    Vector numSize = {};
    int minLimit = 0;
    int maxLimit = 255;

    ColorComponentChanger(AbstractAppData* _app, Rect _rect, int* _component, bool* _confirmColor) :
        Manager(_app, _rect, 2, true, NULL, {}, _app->systemSettings->TRANSPARENTCOLOR),
        component(_component),
        numSize({ 50, getSize().y })
    {
        needTransparencyOutput = true;

        Vector sliderPos = app->getCentrizedPos(sliderSize, getSize());
        sliderRect = { .pos = {0, sliderPos.y}, .finishPos = {getSize().x - numSize.x, sliderPos.y + sliderSize.y} };

        slider = new Slider2(app, sliderRect, component, &minLimit, &maxLimit, _confirmColor);
        addWindow(slider);

        Rect inputButtonRect = { .pos = {sliderRect.finishPos.x + 5, 0}, .finishPos = getSize() };

        inputButton = new InputButton2(app, inputButtonRect, component, &minLimit, &maxLimit, 0, color, RGB(144, 144, 144), RGB(200, 200, 200), _confirmColor);
        addWindow(inputButton);
    }
    virtual void draw() override;
    virtual void onClick(Vector mp) override;
};