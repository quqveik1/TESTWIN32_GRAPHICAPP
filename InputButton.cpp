#pragma once
#include "InputButton.h"



InputButton::InputButton(AbstractAppData* _app, Rect _rect, int* _parameter, int* _minParametr, int* _maxParametr, int _mode/* = 0*/, COLORREF _mainColor, COLORREF _cadreColor/* = RGB(144, 144, 144)*/, COLORREF _cursorColor/* = RGB(200, 200, 200)*/, bool* _confirmInput/* = NULL*/) :
    Window(_app, _rect, _mainColor),
    parameter(_parameter),
    cadreColor(_cadreColor),
    cursorColor(_cursorColor),
    minParametr(_minParametr),
    maxParametr(_maxParametr),
    confirmInput(_confirmInput),
    mode (_mode)
{
    needTransparencyOutput = true;

    font = lround(rect.getSize().y - 1);
    fontSizeX = font / 3;
    spaceBetween2Symbols = fontSizeX * 0.4;
    if (parameter) cursorPos = getAmountOfNumbers(*parameter);

    cursor = LoadCursor(NULL, IDC_IBEAM);

}


int InputButton::getAmountOfNumbers(int num)
{
    int answer = 1;
    while ((num /= 10) > 0) answer++;

    return answer;
}

void InputButton::moveCursorLeft()
{
    if (cursorPos - 1 >= 0 && *parameter != 0) cursorPos--;
    lastTimeClicked = clock();
}

void InputButton::moveCursorRight()
{
    if (cursorPos + 1 <= getAmountOfNumbers(*parameter) && *parameter != 0) cursorPos++;
    lastTimeClicked = clock();
}

void InputButton::backSpace()
{
    int newNum = *parameter;
    if (newNum == 0 || cursorPos <= 0) return;
    int numLength = getAmountOfNumbers(*parameter);;
    newNum /= lround(pow(10, numLength - cursorPos + 1));

    int numsAfterEnteredNum = *parameter % ((int)pow(10, numLength - cursorPos));

    int numsAfterEnteredNumLength = numLength - cursorPos;

    newNum *= pow(10, numsAfterEnteredNumLength);
    newNum += numsAfterEnteredNum;

    if (newNum >= 0)
    {
        *parameter = newNum;        
        cursorPos--;
    }


}

void InputButton::checkKeyboard()
{
    if (clock() - lastTimeClicked < delta) return;

    if (app->getAsyncKeyState (VK_RIGHT)) moveCursorRight();
    if (app->getAsyncKeyState(VK_LEFT)) moveCursorLeft();

    if (!_kbhit())	return;
    int symbol = _getch();

    if (symbol == VK_BACK)
    {
        backSpace();
    }
    

    if (!(symbol >= 48 && symbol <= 57)) return;

    int newNum = *parameter;
    int numLength = getAmountOfNumbers(*parameter);
    newNum /= pow(10, numLength - cursorPos);

    newNum *= 10;
    newNum += symbol - 48;


    int numsAfterEnteredNum = *parameter % ((int)pow(10, numLength - cursorPos));

    int numsAfterEnteredNumLength = numLength - cursorPos;

    newNum *= pow(10, numsAfterEnteredNumLength);
    newNum += numsAfterEnteredNum;


    if (newNum <= *maxParametr && newNum >= *minParametr)
    {
        if (*parameter != 0)cursorPos++;
        *parameter = newNum;
    }

    lastTimeClicked = clock();

}

void InputButton::drawCursor()
{
    int clockMS = clock();

    if (clockMS - lastTimeCursorConditionChanged > 500)
    {
        if (shouldShowCursor == false) shouldShowCursor = true;
        else shouldShowCursor = false;
        lastTimeCursorConditionChanged = clock();
    }

    if (!shouldShowCursor)  return;
    app->setColor(cursorColor, finalDC);
    int tempCursorPos = cursorPos;
    if (*parameter == 0) tempCursorPos = 0;
    int cursorXPosition = deltaAfterCadre + fontSizeX * tempCursorPos;
    if (tempCursorPos > 0)
    {
        cursorXPosition += spaceBetween2Symbols * (tempCursorPos - 1);
    }
    app->line(cursorXPosition, 0, cursorXPosition, getSize().y, finalDC);

    
}

void InputButton::draw()
{
    app->setColor(color, finalDC);
    app->rectangle({ 0, 0 }, getSize(), finalDC);


    

    if (rect.inRect(getAbsMousePos()))
    {
        app->setCursor(cursor);
    }

    char parametrString[MAX_PATH] = {};

    sprintf(parametrString, "%d", *parameter);
    if (wasClicked)
    {
        if (getActiveWindow() != this || app->getAsyncKeyState(VK_RETURN))
        {
            wasClicked = false;
            if (*parameter != parametrBeforeRedacting && confirmInput) *confirmInput = true;
        }

        if (app->getAsyncKeyState(VK_ESCAPE))
        {
            wasClicked = false;
            *parameter = parametrBeforeRedacting;
        }

        if (*parameter == 0)
        {
            cursorPos = 1;
            sprintf(parametrString, "");
        }

        drawCursor();

        checkKeyboard();
        
    }
    else
    {
        cursorPos = getAmountOfNumbers(*parameter);
    }

    char output[MAX_PATH] = {};

    char addition[10] = {};

    if (mode == 1)
    {
        int aditionPrintfResult = sprintf(addition, "%%");
    }
    (void)sprintf(output, "%s%s", parametrString, addition);

    app->selectFont(app->systemSettings->FONTNAME, font, finalDC, fontSizeX);
    app->setColor(app->systemSettings->TextColor, finalDC);
    app->drawText(deltaAfterCadre, 0, getSize().x, getSize().y, output, finalDC, DT_VCENTER);

    Rect cadreRect = { .pos = {0, 0}, .finishPos = {getSize().x, getSize().y} };
    app->drawCadre(cadreRect, finalDC, cadreColor, 2);

    setMbLastTime();
}


void InputButton::onClick(Vector mp)
{
    setActiveWindow(this);
    if (!isClickedLastTime())
    {
        if (wasClicked)
        {
            int amountOfNumbers = getAmountOfNumbers(*parameter);
            double trueMP = mp.x - deltaAfterCadre + spaceBetween2Symbols;
            if (!isEqual(fontSizeX + spaceBetween2Symbols, 0))
            {
                int potentialCursorPos = trueMP / (fontSizeX + spaceBetween2Symbols);
                if (potentialCursorPos <= amountOfNumbers)
                {
                    cursorPos = potentialCursorPos;
                }
            }
        }
        wasClicked = true;
        parametrBeforeRedacting = *parameter;
        

    }
}