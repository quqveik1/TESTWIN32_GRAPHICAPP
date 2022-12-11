#pragma once
#include "WindowsLib.h"

struct Slider2 : Manager
{
    double doubleVersionOfParameter = NULL;
    int* parameter = NULL;
    int* minParameter = NULL;
    int* maxParameter = NULL;
    HDC    slider = NULL; 
    Vector sliderPos = {};
    Vector sliderSize = {10, 9};
    Rect possibleSliderPos = {};
    bool isSliderClicked = false;
    double kOfparameter = 0;

    bool* confirmed = NULL;

    Slider2(AbstractAppData* _app, Rect _rect, int* _parameter, int* _minParameter, int* _maxParameter, bool* _confirmed = NULL) :
        Manager(_app, _rect, 1, true, NULL, {}, RGB (144, 144, 144)),
        parameter (_parameter),
        slider (app->loadManager->loadImage("SliderPointer.bmp")),
        confirmed (_confirmed),
        minParameter (_minParameter),
        maxParameter (_maxParameter)
    {
        needTransparencyOutput = true;

        doubleVersionOfParameter = *parameter;
        
    };

    Rect getsliderRect();
    void confirm();
    virtual int setParameter(double _data);
    virtual int isParameterValid(int parameter);

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onSize(Vector newManagerSize, Rect newRect = {}) override;
};
