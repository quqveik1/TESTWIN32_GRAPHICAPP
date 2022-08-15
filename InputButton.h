#pragma once
#include "DrawBibliothek.h"

struct InputButton : Window
{
    int* parameter = NULL;
    int parametrBeforeRedacting = NULL;
    int* minParametr = NULL;
    int* maxParametr = NULL;
    int cursorPos = 0;
    int lastTimeClicked = 0;
    int delta = 100;
    int lastTimeCursorConditionChanged = 0;
    bool shouldShowCursor = false;
    bool wasClicked = false;
    double fontSizeX = 0;
    double spaceBetween2Symbols;

    double deltaAfterCadre = 4;
    

    HCURSOR cursor = NULL;
    

    bool* confirmInput = NULL;

    COLORREF cadreColor = NULL;
    COLORREF cursorColor = NULL;

    int mode = 0;
    

    InputButton(AbstractAppData* _app, Rect _rect, int* _parameter, int* _minParametr, int* _maxParametr, int _mode/* = 0*/, COLORREF _mainColor, COLORREF _cadreColor = RGB(144, 144, 144), COLORREF _cursorColor = RGB(200, 200, 200), bool* _confirmInput = NULL);

    int getAmountOfNumbers(int num);
    void checkKeyboard();
    void backSpace();
    void moveCursorLeft();
    void moveCursorRight();
    void drawCursor();



    virtual void draw() override;
    virtual void onClick(Vector mp) override;
};
