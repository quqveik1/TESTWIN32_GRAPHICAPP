#pragma once
#include "WindowsLib.h"

struct FrameZone
{
    Rect* rect = {};
    HCURSOR cursor = {};
};

struct ZoneSizeControl
{
    Rect* zone = NULL;
    Vector* minSize = NULL;
    Manager* manager = NULL;
    double frameThickness = NULL;
    bool* needFrameToWork = NULL;
    int activeZone = 0;
    bool wasZoneClicked = false;
    HCURSOR cursorHorizontal = NULL;
    HCURSOR cursorVertical = NULL;
    HCURSOR cursorSNDiagonal = NULL;
    HCURSOR cursorNSDiagonal = NULL;
    Rect upRect = {};//zone = 1
    Rect rightRect = {};//zone = 2
    Rect bottomRect = {};//zone = 3
    Rect leftRect = {};//zone = 4

    Rect upLeft = {}; //zone = 5
    Rect upRight = {}; //zone = 6
    Rect bottomRight = {}; //zone = 7
    Rect bottomLeft = {}; //zone = 8
    int zonesNum = 8;
    FrameZone zones[8] = {};
    Vector mousePosLastTime = {};

    ZoneSizeControl(Manager* _manager, Rect* _zone, bool* _needFrameToWork, Vector* _minSize = NULL) :
        manager(_manager),
        zone(_zone),
        frameThickness(_manager->app->systemSettings->FrameThickness),
        needFrameToWork(_needFrameToWork), 
        minSize (_minSize)
    {
        assert(manager);
        cursorHorizontal = LoadCursor(NULL, IDC_SIZEWE);
        cursorVertical = LoadCursor(NULL, IDC_SIZENS);
        cursorSNDiagonal = LoadCursor(NULL, IDC_SIZENESW);
        cursorNSDiagonal = LoadCursor(NULL, IDC_SIZENWSE);
        zones[0].rect = &upRect;
        zones[0].cursor = cursorVertical;
        zones[1].rect = &rightRect;
        zones[1].cursor = cursorHorizontal;
        zones[2].rect = &bottomRect;
        zones[2].cursor = cursorVertical;
        zones[3].rect = &leftRect;
        zones[3].cursor = cursorHorizontal;
        zones[4].rect = &upLeft;
        zones[4].cursor = cursorNSDiagonal;
        zones[5].rect = &upRight;
        zones[5].cursor = cursorSNDiagonal;
        zones[6].rect = &bottomRight;
        zones[6].cursor = cursorNSDiagonal;
        zones[7].rect = &bottomLeft;
        zones[7].cursor = cursorSNDiagonal;
    }


    int findZone();
    void setFrameZones();
    void controlScreenResizing();
    void setFrameCursor();

    void controlFrame();
    int clickFrame();

    void drawFrame();
};
