#pragma once
#include "WindowsLib.h"
#include "TimerManager.h"
#include "TextView.h"

struct StringButton2;

struct Cursor
{
    StringButton2* stringButton = NULL;

    AbstractAppData* app = NULL;
    Vector startOfText = {};
    COLORREF cursorColor = NULL;
    COLORREF selectionColor = RGB(90, 90, 200);

    int startPos = -1;
    int currPos = -1;
    int isSelecting = 0;
    int isLastTimeSelecting = false;
    int lastTimeCursorConditionChanged = 0;
    bool wasClicked = false;
    bool shouldShowCursor = false;
    int lastTimeCursorPosChanged = 0;
    int delta = 200;
    UINT_PTR timerName = 0;

    int lastTimeDClick = 0;

    Cursor(AbstractAppData* _app, StringButton2* _stringButton, Vector _startOfText, COLORREF _cursorColor) :
        app (_app),
        stringButton (_stringButton),
        startOfText(_startOfText),
        cursorColor (_cursorColor)
    {
        assert(app);
        assert(stringButton);
        if (app->timerManager)
        {
            timerName = app->timerManager->getNewTimerNum();
        }
    }


    void makeDefault();
    void draw(M_HDC finalDC);
    int moveLeft(bool needToChangeStartPos = true);
    int moveRight(bool needToChangeStartPos = true);
    int moveCursorTo(int pos, bool needToChangeStartPos = true);
    int getCursorPosX();
    int getCertainCharPos(int num);
    int cursorPosFromMouse(Vector mp);
    int mbDownCursor(Vector mp);
    int mMoveCursor(Vector mp);
    int mbUpCursor(Vector mp);
    bool isActiveSelection();
    int onTimer(UINT_PTR tm);


};

struct StringButton2 : TextView
{
    char* text = NULL;
    int currentTextSize = 0;
    int maxTextSize = 0;
    char* textBeforeRedacting = NULL;

    int lastTimeClicked = 0;
    int specButtonsDelta = 200;

    int inputMode = 0;

    HCURSOR cursorImage = NULL;

    double deltaAfterCadre = 4;
    COLORREF cadreColor = NULL;
    
    Cursor cursor;
    

    StringButton2(AbstractAppData* _app, Rect _rect, char* _text, int _maxTextSize, COLORREF _mainColor, COLORREF _cadreColor = RGB(144, 144, 144), COLORREF _cursorColor = RGB(200, 200, 200)) :
        //TextView(_app, _rect, 1, true, NULL, {}, _mainColor),
        TextView(_app),
        text(_text),
        maxTextSize(_maxTextSize),
        cadreColor (_cadreColor),
        cursor(_app, this, {deltaAfterCadre, 0}, _cursorColor)
    {
        setColor(_mainColor);
        setTrancparencyOutput(true);
        cursorImage = LoadCursor(NULL, IDC_IBEAM);
    }

    void checkKeyboardChar(int key);
    void checkKeyboard(int key);
    void backSpace();
    void copyInBuf();
    void pasteFromBuf();
    void selectAll();
    void moveCursorLeft();
    void moveCursorRight();
    void drawCursor();
    bool isAnyNormalKeyButtonClicked();
    int findClickedKey();
    int nearestLeftWordStartPos (int cursorPos);
    int nearestRightWordStartPos(int cursorPos);
    void startAndEndOfClickedWord(int cursorPos, int& pos1, int& pos2);

    void shiftTextForward(char* _text, int startPos, int finishPos, int delta = 1);
    void shiftTextBack(char* _text, int startPos, int finishPos, int delta = 1);

    int getTextSize(char* _text = NULL);
    int& getInputMode() { return inputMode; };

    void getTextAfterEnteringSymbol(char* finalText, char* originalText, int _currentTextSize, int _cursorPos, char symbol);
    

    virtual bool isSymbolAllowed(char symbol);
    virtual bool isSepSymbol(char symbol);
    virtual void modifyOutput(char* outputStr, char* originalStr);
    virtual void confirmEnter() {};
    virtual void doBeforeMainBlock() {};
    virtual void doAfterMainBlock() {};
    

    virtual void draw() override;
    virtual int onKeyboard(int key) override;
    virtual int onKeyboardChar(int key) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
    virtual int onTimer(UINT_PTR timerName) override;
    virtual void onClick(Vector mp) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onDoubleClick(Vector mp, int button) override;
    virtual int onSize(Vector managerSize, Rect _newRect = {}) override;


};