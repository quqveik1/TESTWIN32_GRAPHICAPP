#pragma once
#include "StringButton2.cpp"
#include "cmath"


struct InputButton2 : StringButton2
{
    void* parameter = NULL;
    void* minParameter = NULL;
    void* maxParameter = NULL;

    bool* confirmInput = NULL;  
    static const int STANDART_MODE = 0;
    static const int PERCANTAGE_MODE = 1;
    static const int POSITIVE_MODE = 2;
    int mode = STANDART_MODE;
    char numText[MAX_PATH] = {};


    InputButton2(AbstractAppData* _app, Rect _rect, void* _parameter, void* _minParametr, void* _maxParametr, int _mode/* = 0*/, COLORREF _mainColor, COLORREF _cadreColor = RGB(144, 144, 144), COLORREF _cursorColor = RGB(200, 200, 200), bool* _confirmInput = NULL) :
        StringButton2(_app, _rect, NULL, MAX_PATH, _mainColor, _cadreColor, _cursorColor),
        parameter(_parameter),
        confirmInput (_confirmInput), 
        minParameter (_minParametr),
        maxParameter (_maxParametr),
        mode (_mode)
    {
        text = numText;
    }

    int getIntFromText(char* text, int textSize = 0);
    void setParameter(void* source);
    
    virtual void* getParameterFromText(char* text, int textSize = 0);//returns STATIC object
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