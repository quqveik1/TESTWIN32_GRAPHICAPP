#pragma once
#include "Q_Vector.h"
#include <Windows.h>
struct ProgrammeDate
{
    Vector absMouseCoordinats = {};
    Vector mousePos = {};
    Vector managerPos = {};
    Vector canvasCoordinats = {};
    COLORREF color = NULL;
    COLORREF backGroundColor = NULL;
    int thickness = NULL;
    int gummiThickness = NULL;
    int clickedMB = NULL;

    virtual Vector getMousePos() { return mousePos; };

};