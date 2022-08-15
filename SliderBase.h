#pragma once
#include "WindowsLib.cpp"

enum Oriantation
{
    O_HORIZONTAL = 1,
    O_VERTICAL   = 2
};

struct SliderBase : Manager
{
    double doubleVersionOfParameter = NULL;
    int* parametr = NULL;
    int* minParameter = NULL;
    int* maxParameter = NULL;
    Vector sliderRectPos = {};
    Vector sliderRectSize = { 10, 9 };
    Vector arrowSize = {};
    double firstSidePos = 0;
    double finishSidePos = 0;
    bool isSliderClicked = false;
    double kompressOfParametr = 0;
    Oriantation oriantation;

    SliderBase(AbstractAppData* _app, Rect _rect, int* _parametr, int* _minParameter, int* _maxParameter, Oriantation _oriantation, Vector _arrowSize = {});

    Rect getSliderRect();
    void mainBlock (double _mp, double _mpLastTime, double _size, double& _sliderRectPos, double& _sliderRectSize);

    virtual void countCompress() =0;
    virtual void confirmUse() {};
    virtual void drawSliderBackground() = 0;
    virtual void drawSliderRect() = 0;
    virtual void drawArrows() {};

    virtual void draw() override;
    virtual void onClick(Vector mp) override;

};