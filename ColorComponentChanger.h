#pragma once
#include "Slider2.cpp"
#include "InputButton.cpp"
#include "InputButton2.cpp"
#include "Slider3.cpp"


struct ColorComponentChanger : Manager
{
    int* component = NULL;
    int componentLastTime = NULL;
    int copyVersionOfCompoment = 0;
    Slider3Horizontal* slider = NULL;
    InputButton2* inputButton = NULL;
    Rect sliderRect = {};
    Vector sliderSize = { 0, 15 };
    Vector numSize = {};
    int minLimit = 0;
    int maxLimit = 255;
    int componentType = 0;

    ColorComponentChanger(AbstractAppData* _app, Rect _rect, int* _component, bool* _confirmColor, int _componentType) :
        Manager(_app, _rect, 2, true, NULL, {}, _app->systemSettings->TRANSPARENTCOLOR),
        component(_component),
        numSize({ 50, getSize().y }),
        componentType(_componentType)
    {
        needTransparencyOutput = true;

        Vector sliderPos = app->getCentrizedPos(sliderSize, getSize());
        sliderRect = { .pos = {0, sliderPos.y}, .finishPos = {getSize().x - numSize.x, sliderPos.y + sliderSize.y} };

        //slider = new Slider3Horizontal(app, sliderRect, component, &minLimit, &maxLimit, _confirmColor);
        slider = new Slider3Horizontal(app, sliderRect, component, &minLimit, &maxLimit);
        addWindow(slider);

        Rect inputButtonRect = { .pos = {sliderRect.finishPos.x + 5, 0}, .finishPos = getSize() };

        inputButton = new InputButton2(app, inputButtonRect, component, &minLimit, &maxLimit, 0, color, RGB(144, 144, 144), RGB(200, 200, 200), _confirmColor);
        addWindow(inputButton);
    }
    virtual void draw() override;
    virtual int onMouseMove(Vector mp,Vector delta) override;
    virtual void onClick(Vector mp) override;
};