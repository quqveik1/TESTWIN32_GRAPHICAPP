#pragma once
#include "WindowsLib.h"

struct TextView : Window
{
    bool wrapContentX = 0;
    bool wrapContentY = 0;
    double relativeFontSize = 0.9;
    TextView(AbstractAppData* _app, int _font = NULL, const char* _text = NULL) :
        Window(_app)
    {
        setText(_text);
        setFont(_font);
    }

    void wrapControl();

    virtual int setFont(int newFont) override;
    virtual const char* setText(const char* newText) override;
    virtual void setWrapStatus(bool status);
    virtual void setWrapStatusX(bool status);
    virtual void setWrapStatusY(bool status);

    virtual double setRelativeFontSize(double _size);//0 <= _size <= 1

    virtual int onSize(Vector managerSize, Rect _newRect = {}) override;
};