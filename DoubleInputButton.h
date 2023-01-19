#pragma once
#include "StringButton2.cpp"

struct DoubleInputButton : StringButton2
{
    double* parameter = NULL;
    double* minParametr = NULL;
    double* maxParametr = NULL;

    bool* confirmInput = NULL;
    int mode = 0;
    char numText[MAX_PATH] = {};
    DoubleInputButton(AbstractAppData* _app, Rect _rect, double* _parameter, double* _minParametr, double* _maxParametr, int _mode/* = 0*/, COLORREF _mainColor, COLORREF _cadreColor = RGB(144, 144, 144), COLORREF _cursorColor = RGB(200, 200, 200), bool* _confirmInput = NULL) :
        StringButton2(_app, _rect, NULL, MAX_PATH, _mainColor, _cadreColor, _cursorColor),
        parameter(_parameter),
        confirmInput(_confirmInput),
        minParametr(_minParametr),
        maxParametr(_maxParametr),
        mode(_mode)
    {
        text = numText;
        //setText(numText);
    }

    double getDoubleFromText(const char* text, int textSize = 0);

    void setParameter(double* newParameter);

    virtual bool isSymbolAllowed(char symbol) override;
    virtual void modifyOutput(char* outputStr, char* originalStr) override;
    virtual void confirmEnter() override;
    virtual void doBeforeMainBlock() override;
    virtual void doAfterMainBlock() override;
};