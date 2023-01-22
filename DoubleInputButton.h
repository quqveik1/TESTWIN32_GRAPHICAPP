#pragma once
#include "InputButton2.cpp"

struct DoubleInputButton : InputButton2
{

    bool* confirmInput = NULL;
    int mode = 0;
    DoubleInputButton(AbstractAppData* _app, Rect _rect, void* _parameter, void* _minParametr, void* _maxParametr, int _mode/* = 0*/, COLORREF _mainColor, COLORREF _cadreColor = RGB(144, 144, 144), COLORREF _cursorColor = RGB(200, 200, 200), bool* _confirmInput = NULL) :
        InputButton2(_app, _rect, _parameter, _minParametr, _maxParametr, _mode, _mainColor, _cadreColor, _cursorColor, _confirmInput)
    {
    }

    double getDoubleFromText(const char* text, int textSize = 0);

    virtual void* getParameterFromText(char* text, int textSize = 0);
    virtual void parameterToString(char* text, void* _num);
    virtual bool parameterIsBiggerMaximum(void* _num);
    virtual bool parameterIsSmallerMinimum(void* _num);
    virtual bool isParametersEqual(void* a, void* b);
    virtual void copyParameter(const void* source);

    virtual bool isSymbolAllowed(char symbol) override;
    virtual void modifyOutput(char* outputStr, char* originalStr) override;
    virtual void confirmEnter() override;
    virtual void doBeforeMainBlock() override;
    virtual void doAfterMainBlock() override;
};