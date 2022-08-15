#pragma once
#include "DrawBibliothek.h"


struct StringButton : Window
{
    bool advancedMode;
    char* inText;
    int cursorPosition;
    int textLen;
    int lastButton;
    int lastTimeClicked;
    bool onlyNums;
    const int MaxNum;



    StringButton(AbstractAppData* _app, Rect _rect, COLORREF _color, char* _redactingText, int _redactingTextLength, Manager* _manager, int _MaxNum = 20, bool _onlyNums = false) :
        Window(_app, _rect, _color, NULL, _manager),
        inText(_redactingText),
        advancedMode(true),
        cursorPosition(_redactingTextLength - 1),
        textLen(_redactingTextLength + 1),
        lastButton(0),
        lastTimeClicked(0),
        onlyNums(_onlyNums),
        MaxNum(_MaxNum)
    {}


    virtual void draw() override;
    void checkSymbols();
    void cursorMovement(int side);
    void backSpace();
};