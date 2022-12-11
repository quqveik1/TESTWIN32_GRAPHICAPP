#pragma once

#include "WindowsLib.h"
#include "Slider3Vertical.cpp"


struct Menu : Manager
{
    int lastSelected = 0;
    int currentSectionLen = 0;
    Rect oneSection = {};
    double maxheight = 0;
    int sliderStatus;// 1 - active; 0 - disabled
    Slider3Vertical slider;
    double sliderwidth = 16;
    int startCoordinat = 0;
    int minCoordinat = 0;
    int maxCoordinat = 0;

    Menu(AbstractAppData* _app, Vector _startPos, Rect _oneSection, double _maxheight, bool _isDefaultActive = false, int _sliderStatus = 1) :
        Manager(_app, {}, app->systemSettings->ONELAYTOOLSLIMIT, _isDefaultActive, NULL, {}, _app->systemSettings->MenuColor, false),
        oneSection (_oneSection),
        maxheight(_maxheight),
        sliderStatus (_sliderStatus),
        slider(_app, {}, &startCoordinat, &minCoordinat, &maxCoordinat)
    {
    }

    virtual void drawOneLine(int lineNum) = NULL;
    virtual int drawBeforeMainBlock() { return 1; };
    virtual int drawAfterMainBlock() { return 1; };
    virtual int onClickLine(Vector mp) = NULL;
    virtual int findSectionNum(Vector mp);
    virtual Rect getSectionRect(int num);
    

    virtual void draw() override;
    virtual void onClick(Vector mp) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
    virtual int onSize(Vector newManagerSize, Rect newRect = {}) override;


};