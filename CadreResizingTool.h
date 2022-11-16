#pragma once

/*
struct CadreResizingTool : Tool2
{

    const int controlSquareLength = 4;
    Rect* controlSquare = new Rect[controlSquareLength]{};

    int activeControlSquareNum = -1;
    bool draggedLastTime = false;
    Vector lastTimeMP = {};
    Vector controlSquareSize = { 10, 10 };
    Vector deltaForControlButtons = {};
    COLORREF cadreColor = TX_BLACK;

    CadreResizingTool(ÑDllSettings* _dllSettings, const char* _name, const int _ToolSaveLen, HDC _dc, AbstractAppData* _data) :
        Tool(_dllSettings, _name, _ToolSaveLen, _dc, _data)
    {
    }

    void controlMoving();
    void controlLeftButton();
    void controlRightButton();
    void setControlSquares();
    void drawControlButtons(HDC outDC);
    int getSign(double num);

    virtual  void countDeltaForControlButtons();
    virtual void countToolZone();

    long edit(ToolLay* toollay) override;
};
*/