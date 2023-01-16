#pragma once
#include "ColorComponentChanger.cpp" 
#include "HSLPalette.h"

struct ColorHistory
{
    static const int HistoryLength = 15;
    COLORREF colorHistory[HistoryLength] = {};
    Rect colorRect[HistoryLength] = {};
    int currentPos = 0;
    int currHistoryLen = 0;

    int getByteSize();
};

struct ColorSection
{
    Rect section = {};
    COLORREF color = NULL;
};

struct ColorMenu : Manager
{
    ColorComponentChanger* redChanger = NULL;
    ColorComponentChanger* greenChanger = NULL;
    ColorComponentChanger* blueChanger = NULL;
    int redComponent = 0;
    int greenComponent = 0;
    int blueComponent = 0;

    
    //saveable part
    ColorHistory colorHistory;
    //saveable part
    char pathToSaveHistory[MAX_PATH] = {};

    //M_HDC palette = {};
    //Vector paletteSize = { 256, 256 };
    Vector palettePos = { 25, handle.rect.finishPos.y + 25 };
    //Rect paletteRect = { .pos = palettePos,  .finishPos = palettePos + paletteSize };
    

    HSLPalette hslPalette;

    Vector currColorPos = {};
    

    Vector colorSectionSize = { 25, 25 };
    Vector colorHistoryStartPos = {};
    Vector exampleColorStartPos = {};
    ColorSection* exampleColorRects = NULL;
    int colorExamplesNum = NULL;
    COLORREF colorLastTime = NULL;

    COLORREF frameColor = RGB(144, 144, 144);
    COLORREF splitLinesColor = RGB(144, 144, 144);
    
    Vector sizeOfColorMenu = {412, 227};
    bool confirmedColor = false;

    
    

    void loadHistory();


    ColorMenu(EngineAppApi* _app, Vector _pos, bool _needToShow = false);


    virtual void saveMenu();
    void setColorHistoryRects();
    void controlHistoryClick();
    void moveHistory(int clickedNumOFColorRect);
    virtual void confirmColor();
    void setColorComponents();
    void drawColorHistory();
    void setColorExamples();
    void drawColorExamples();
    void drawOneColorSection(Rect sectionRect, COLORREF sectionColor);
    void controlExampleClick();
    
    void initPalette();
    
    
    virtual void show() override;

    virtual void draw() override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
    virtual void onClick(Vector mp) override;
    virtual int onKeyboard(int key) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onDestroy() override;
};