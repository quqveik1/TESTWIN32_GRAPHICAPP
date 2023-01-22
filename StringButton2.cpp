#pragma once
#include "StringButton2.h"


void Cursor::makeDefault()
{
    currPos = -1;
    startPos = -1;
}

void Cursor::draw(M_HDC finalDC)
{
    int clockMS = clock();

    if (clockMS - lastTimeCursorConditionChanged > 500)
    {
        if (shouldShowCursor == false) shouldShowCursor = true;
        else shouldShowCursor = false;
        lastTimeCursorConditionChanged = clock();
    }

    if (clockMS - lastTimeCursorPosChanged < 500)
    {
        shouldShowCursor = true;
    }

    /*
    if (app->isDoubleClick())
    {
        lastTimeDClick = clockMS;
    }
    */

    int cursorXPosition = getCertainCharPos(currPos);
    int startCursorXPosition = getCertainCharPos(startPos);

    if (isActiveSelection())
    {
        app->setColor(selectionColor, finalDC);
        app->rectangle(startCursorXPosition, startOfText.y, cursorXPosition, stringButton->getSize().y, finalDC);
    }

    if (!shouldShowCursor)  return;

    app->setColor(cursorColor, finalDC);
    app->line(cursorXPosition, startOfText.y, cursorXPosition, stringButton->getSize().y, finalDC);

}

int Cursor::moveLeft(bool needToChangeStartPos/* = true*/)
{
    return moveCursorTo(currPos - 1, needToChangeStartPos);
}  

int Cursor::moveRight(bool needToChangeStartPos/* = true*/)
{
    return moveCursorTo(currPos + 1, needToChangeStartPos);
}

int Cursor::moveCursorTo(int pos, bool needToChangeStartPos/* = true*/)
{
    if (0 <= pos && pos <= stringButton->getTextSize())
    {
        currPos = pos;
        if (needToChangeStartPos)startPos = pos;
        lastTimeCursorPosChanged = clock();
        return currPos;
    }
    return NULL;
}



int Cursor::getCursorPosX()
{
    return getCertainCharPos(currPos);
}


int Cursor::getCertainCharPos(int num)
{
    int positionX = -1;

    if (num < stringButton->maxTextSize)
    {
        char saveSymbol = stringButton->text[num];
        stringButton->text[num] = NULL;
        positionX = std::lround(app->getTextExtent(stringButton->text, stringButton->finalDC).x);
        stringButton->text[num] = saveSymbol;
    }

    return startOfText.x + positionX;
}

int Cursor::cursorPosFromMouse(Vector mp)
{
    int pos = stringButton->getTextSize();
    for (int i = 0; i <= stringButton->getTextSize(); i++)
    {
        int pos1 = getCertainCharPos(i);
        int pos2 = getCertainCharPos(i + 1);

        if (pos1 <= mp.x && mp.x <= pos2)
        {
            pos = i;
            break;
        }
        if (i == stringButton->getTextSize())
        {
            if (pos1 <= mp.x)
            {
                pos = i;
                break;
            }
        }

        if (i == 0)
        {
            if (mp.x <= pos2)
            {
                pos = i;
                break;
            }
        }
    }

    return pos;
}

int Cursor::mbDownCursor(Vector mp)
{
    int pos = cursorPosFromMouse(mp);

    if (/*!app->isDoubleClick() &&*/ clock() - lastTimeDClick > 500 )
    {
        isSelecting = 1;
        app->updateScreen(stringButton);
        moveCursorTo(pos);
        
    }

    return pos;

}

int Cursor::mMoveCursor(Vector mp)
{
    int pos = cursorPosFromMouse(mp);

    if (isSelecting)
    {
        if (pos != currPos)
        {
            app->updateScreen(stringButton);
        }
        moveCursorTo(pos, false);
    }

    return pos;

}


int Cursor::mbUpCursor(Vector mp)
{
    isSelecting = 0;
    /*
    int pos = cursorPosFromMouse(mp);

    if (!app->isDoubleClick() && clock() - lastTimeDClick > 500)
    {
        if (pos != currPos)app->updateScreen();
        moveCursorTo(pos, false);
    }
    */

    return 0;

}


bool Cursor::isActiveSelection()
{
    return currPos != startPos;
}

int Cursor::onTimer(UINT_PTR tm)
{
    
    if (tm == timerName)
    {
        
        if (stringButton->getInputMode())
        {
            app->updateScreen(stringButton);
            SetTimer(app->MAINWINDOW, timerName, delta, NULL);
            shouldShowCursor != shouldShowCursor;
        }
    }
    return shouldShowCursor;
}


void StringButton2::moveCursorLeft()
{
    if (app->getAsyncKeyState(VK_SHIFT))
    {
        if (app->getKeyState(VK_CONTROL))
        {
            cursor.moveCursorTo(nearestLeftWordStartPos(cursor.currPos), false);
        }
        else
        {
            cursor.moveLeft(false);
        }
    }
    else
    {
        if (app->getKeyState(VK_CONTROL))
        {
            cursor.moveCursorTo(nearestLeftWordStartPos(cursor.currPos));
        }
        else
        {
            cursor.moveLeft();
        }
    }
}

void StringButton2::moveCursorRight()
{
    
    if (app->getKeyState(VK_SHIFT))
    {
        if (app->getKeyState(VK_CONTROL))
        {
            cursor.currPos = nearestRightWordStartPos(cursor.currPos);
        }
        else
        {
            cursor.moveRight(false);
        }
    }
    else
    {

        if (app->getKeyState(VK_CONTROL))
        {
            cursor.moveCursorTo (nearestRightWordStartPos(cursor.currPos));
        }
        else
        {
            cursor.moveRight();
        }
    }
}

void StringButton2::shiftTextForward(char* _text, int startPos, int finishPos, int delta/* = 1*/)
{
    if (startPos < 0 || finishPos > maxTextSize)
    {
        massert(startPos < 0, app);
    }
    for (int localDelta = 0; localDelta < delta; localDelta++)
    {
        for (int i = finishPos + localDelta; i >= startPos + localDelta; i--)
        {
            if (finishPos < maxTextSize)
            {
                _text[i + 1] = _text[i];
            }
        }
    }
}

void StringButton2::shiftTextBack(char* _text, int startPos, int finishPos, int delta/* = 1*/)
{
    if (startPos < 0 || finishPos > maxTextSize)
    {
        massert(startPos < 0, app);
    }
    for (int localDelta = 0; localDelta < delta; localDelta++)
    {
        for (int i = startPos - localDelta; i <= finishPos - localDelta; i++)
        {
            if (i - 1 >= 0)
            {
                _text[i - 1] = _text[i];
            }
        }
    }

}

int StringButton2::getTextSize(char* _text/* = NULL*/)
{
    if (_text == NULL) _text = text;

    int i = 0;
    while (_text[i] != NULL)
    {
        i++;
    }
    return i;
}


void StringButton2::getTextAfterEnteringSymbol(char* finalText, char* originalText, int _currentTextSize, int _cursorPos, char symbol)
{
    sprintf(finalText, "%s", originalText);

    shiftTextForward(finalText, _cursorPos, _currentTextSize - 1);
    finalText[_cursorPos] = symbol;
}


bool StringButton2::isSepSymbol(char symbol)
{
    if (symbol == ' ')
    {
        return true;
    }     
    
    if (symbol == '.')
    {
        return true;
    }   

    if (symbol == ',')
    {
        return true;
    }    
    
    if (symbol == '(')
    {
        return true;
    }     
    
    if (symbol == ')')
    {
        return true;
    }

    return false;
}

bool StringButton2::isSymbolAllowed(char _symbol)
{
    unsigned char symbol = _symbol;
    if (0x30 <= symbol && symbol <= 0x7E)
    {
        return true; 
    }

    //КИРИЛИЦА
    if (192 <= symbol && symbol <= 255)
    {
        return true;
    }
    
    if (33 <= symbol && symbol <= 126)
    {
        return true;
    }

    //знаки препинания
    if (137 <= symbol && symbol <= 186)
    {
        return true;
    }

    if (symbol == VK_SPACE)
    {
        return true;
    }
    return false;
}

int StringButton2::onKeyboardChar(int key)
{
    if (getInputMode())
    {
        checkKeyboardChar(key);
    }
    return 0;
}


int StringButton2::onKeyboard(int key)
{

    if (getInputMode())
    {
        if (app->getKeyState(VK_ESCAPE))
        {
            getInputMode() = 0;
            if (textBeforeRedacting)
            {
                strcpy(text, textBeforeRedacting);
            }
        }

        checkKeyboard(key);

        
        if (currentTextSize > (int)strlen(text)) currentTextSize = strlen(text);

        text[currentTextSize] = 0;
        //if (getInputMode() && getMBCondition() == 1) cursor.clickCursor(getMousePos());
    }
    return 0;
}

void StringButton2::modifyOutput(char* outputStr, char* originalStr)
{
    assert(outputStr);
    assert(originalStr);

    sprintf(outputStr, "%s", originalStr);
}

void StringButton2::draw()
{
    doBeforeMainBlock();

    if (isVisible())
    {
        app->setColor(color, finalDC);
        app->rectangle({ 0, 0 }, getSize(), finalDC);

        if (getInputMode())
        {
            cursor.draw(finalDC);
        }

        char parametrString[MAX_PATH] = {};
        sprintf(parametrString, "%s", text);

        char output[MAX_PATH] = {};

        modifyOutput(output, parametrString);

        app->selectFont(app->systemSettings->FONTNAME, font, finalDC);
        app->setColor(app->systemSettings->TextColor, finalDC);
        app->drawText(deltaAfterCadre, 0, getSize().x, getSize().y, output, finalDC, DT_VCENTER);

        Rect cadreRect = { .pos = {0, 0}, .finishPos = {getSize().x, getSize().y} };
        app->drawCadre(cadreRect, finalDC, cadreColor, 2);
    }

    doAfterMainBlock();

    setMbLastTime();
}



int StringButton2::onMouseMove(Vector mp, Vector delta)
{
    if (cursor.isSelecting)cursor.mMoveCursor(mp);

    if (cursor.isSelecting) cursor.isLastTimeSelecting = true;
    if ((rect - rect.pos).inRect(mp) || cursor.isSelecting)
    {
        if (isVisible())app->setCursor(cursorImage);
    }
    else if ((rect - rect.pos).inRect(mp - delta))
    {
        app->setCursor();
    }

    if (cursor.isLastTimeSelecting && cursor.isSelecting == 0)
    {
        cursor.isLastTimeSelecting = false;
        app->setCursor();
    }
    return 0;
}

int StringButton2::onTimer(UINT_PTR timerName)
{

    return cursor.onTimer(timerName);
}



void StringButton2::onClick(Vector mp)
{
    /*
    setActiveWindow(this);

    cursor.clickCursor(mp);
    if (!isClickedLastTime())
    {
        if (!getInputMode())
        {
            if (textBeforeRedacting) delete textBeforeRedacting;
            textBeforeRedacting = new char[maxTextSize];
            currentTextSize = strlen(text);
            assert(textBeforeRedacting);
            strcpy(textBeforeRedacting, text);
        }
        getInputMode() = 1;
    }
    */
}

int StringButton2::mbDown(Vector mp, int button)
{
    if ((rect - rect.pos).inRect(mp) && isVisible())
    {
        setActiveWindow(this);
        cursor.mbDownCursor(mp);
        if (!getInputMode())
        {
            if (textBeforeRedacting) delete textBeforeRedacting;
            textBeforeRedacting = new char[maxTextSize];
            currentTextSize = strlen(text);
            assert(textBeforeRedacting);
            strcpy(textBeforeRedacting, text);
        }
        getInputMode() = 1;
        return 0;
    }
    else
    {
        if (getInputMode())app->updateScreen(this);
        getInputMode() = 0;
        
    }
    return 0;
}

int StringButton2::mbUp(Vector mp, int button)
{
    cursor.mbUpCursor(mp);
    if (getInputMode())
    {
        SetTimer(app->MAINWINDOW, cursor.timerName, cursor.delta, NULL);
    }
    //getInputMode() = 0;
    return 0;
}



int StringButton2::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    TextView::onSize(managerSize, _newRect);
    font = rect.getSize().y * 0.9;
    return 0;
}




void StringButton2::copyInBuf()
{
    int localStartPos = cursor.startPos;
    int localCurrPos = cursor.currPos;

    if (localStartPos > localCurrPos)
    {
        int cpyStartPos = localStartPos;
        localStartPos = localCurrPos;
        localCurrPos = cpyStartPos;
    }

    if (localStartPos >= 0 && localCurrPos <= currentTextSize)
    {
        if (OpenClipboard(NULL))
        {
            if (cursor.isActiveSelection())
            {
                EmptyClipboard();
                HGLOBAL buffer = NULL;
                char cpySymbol = text[localCurrPos];
                text[localCurrPos] = NULL;
                int selectedZoneSize = strlen(&text[localStartPos]) + 1;
                buffer = GlobalAlloc(GMEM_DDESHARE, selectedZoneSize);
                if (buffer)
                {
                    char* tempBuffer = (char*)GlobalLock(buffer);
                    if (tempBuffer)
                    {
                        strcpy(tempBuffer, &text[localStartPos]);
                        text[localCurrPos] = cpySymbol;
                    }
                    GlobalUnlock(buffer);
                    SetClipboardData(CF_TEXT, buffer);
                }
            }

            CloseClipboard();
        }
    }
}

void StringButton2::pasteFromBuf()
{
    int localStartPos = cursor.startPos;
    int localCurrPos = cursor.currPos;

    if (localStartPos > localCurrPos)
    {
        int cpyStartPos = localStartPos;
        localStartPos = localCurrPos;
        localCurrPos = cpyStartPos;
    }

    if (localStartPos >= 0 && localCurrPos <= currentTextSize)
    {
        if (OpenClipboard(NULL))
        {
            HANDLE hData = GetClipboardData(CF_TEXT);
            if (hData)
            {
                char* pasteBuffer = (char*)GlobalLock(hData);
                if (pasteBuffer)
                {
                    int pasteBufferLength = strlen(pasteBuffer);
                    bool needToPaste = true;
                    for (int i = 0; i < pasteBufferLength; i++)
                    {
                        if (!isSymbolAllowed(pasteBuffer[i]))
                        {
                            needToPaste = false;
                            break;
                        }
                    }
                    if (needToPaste)
                    {
                        int selectionZoneSize = localCurrPos - localStartPos;
                        if (pasteBufferLength > selectionZoneSize)
                        {
                            shiftTextForward(text, localCurrPos, currentTextSize, pasteBufferLength - selectionZoneSize);
                        }

                        if (pasteBufferLength < selectionZoneSize)
                        {
                            shiftTextBack(text, localCurrPos, currentTextSize, selectionZoneSize - pasteBufferLength);
                        }

                        char cpyNullingSymbol = text[localStartPos + pasteBufferLength];
                        strcpy(&text[localStartPos], pasteBuffer);
                        text[localStartPos + pasteBufferLength] = cpyNullingSymbol;
                        currentTextSize = getTextSize(text);
                        cursor.moveCursorTo(localStartPos + pasteBufferLength);
                    }
                }
                GlobalUnlock(hData);
            }
            CloseClipboard();
        }
    }
}


int StringButton2::nearestLeftWordStartPos(int cursorPos)
{
    bool wasNonSpaceSymbolChecked = false;
    int answer = cursorPos;

    for (int i = cursorPos - 1; i >= 0; i--)
    {
        if (isSepSymbol (text[i]))
        {
            wasNonSpaceSymbolChecked = true;
        }
        else
        {
            if (wasNonSpaceSymbolChecked)
            {
                answer = i + 1;
                break;
            }
        }
        if (i == 0)
        {
            if (answer == cursorPos)
            {
                answer = i;
                break;
            }
        }
    }

    return answer;
}

int StringButton2::nearestRightWordStartPos(int cursorPos)
{
    bool wasSpaceSymbolChecked = false;
    int answer = cursorPos;

    for (int i = cursorPos; ; i++)
    {
        if (isSepSymbol(text[i]))
        {
            wasSpaceSymbolChecked = true;
        }
        else
        {
            if (wasSpaceSymbolChecked)
            {
                answer = i;
                break;
            }
        }
        if (!text[i])
        {
            if (answer == cursorPos)
            {
                answer = i;
                break;
            }
        }
    }

    return answer;


}


void StringButton2::startAndEndOfClickedWord(int cursorPos, int& pos1, int& pos2)
{        
    bool wasSepSymbolChecked = false;
    bool wasUsualSymbolChecked = false;

    for (int i = cursorPos; i >= 0; i--)
    {
        if (isSepSymbol(text[i]))
        {

            wasSepSymbolChecked = true;

            if (wasUsualSymbolChecked)
            {
                pos1 = i + 1;
                break;
            }
        }
        else
        {
            if (i == 0)
            {
                pos1 = i;
                break;
            }
            wasUsualSymbolChecked = true;

            if (wasSepSymbolChecked)
            {
                pos1 = i + 1;
                break;
            }
        }
    }


    wasSepSymbolChecked = false;
    wasUsualSymbolChecked = false;

    for (int i = cursorPos; ; i++)
    {
        if (isSepSymbol(text[i]))
        {
            wasSepSymbolChecked = true;

            if (wasUsualSymbolChecked)
            {
                pos2 = i;
                break;
            }
        }
        else
        {
            if (text[i] == 0)
            {
                pos2 = i;
                break;
            }
            wasUsualSymbolChecked = true;

            if (wasSepSymbolChecked)
            {
                pos2 = i;
                break;
            }
        }
    }
}

void StringButton2::backSpace()
{
    setActiveWindow(this);
    if (app->getAsyncKeyState(VK_CONTROL) && !app->getAsyncKeyState(VK_SHIFT) && !cursor.isActiveSelection())
    {
        int nearestWordPos = nearestLeftWordStartPos(cursor.currPos);
        //cursor.moveCursorTo(nearestWordPos, false);
    }

    if (cursor.isActiveSelection())
    {
        if (cursor.startPos > cursor.currPos)
        {
            int savePos = cursor.startPos;
            cursor.startPos = cursor.currPos;
            cursor.currPos = savePos;
        }

        for (int i = cursor.startPos; i < cursor.startPos + (cursor.currPos - cursor.startPos); i++)
        {
            text[i] = NULL;
        }

        shiftTextBack(text, cursor.currPos, currentTextSize, cursor.currPos - cursor.startPos);

        cursor.moveCursorTo(cursor.startPos, false);
        currentTextSize = getTextSize();

    }
    else
    {

        text[cursor.currPos - 1] = NULL;
        shiftTextBack(text, cursor.currPos, currentTextSize);
        cursor.moveLeft();
        currentTextSize--;
    }

}     

void StringButton2::selectAll()
{
    cursor.moveCursorTo(0, true);
    cursor.moveCursorTo(getTextSize(text), false);
}


void StringButton2::checkKeyboard(int key)
{
    
    if (app->getKeyState(VK_RIGHT))
    {
        moveCursorRight();
        lastTimeClicked = clock();
        setActiveWindow(this);
        app->updateScreen(this);
        return;
    }

    if (app->getKeyState(VK_LEFT))
    {
        moveCursorLeft();
        lastTimeClicked = clock();
        setActiveWindow(this);
        app->updateScreen(this);
        return;
    }

    if (app->getKeyState(VK_BACK))
    {
        backSpace();
        lastTimeClicked = clock();
        setActiveWindow(this);
        app->updateScreen(this);
        return;
    }

    if (app->getKeyState(VK_CONTROL) && app->getKeyState('C'))
    {
        copyInBuf();
        lastTimeClicked = clock();
        setActiveWindow(this);
        app->updateScreen(this);
        return;
    }

    if (app->getKeyState(VK_CONTROL) && app->getKeyState('V'))
    {
        pasteFromBuf();
        lastTimeClicked = clock();
        setActiveWindow(this);
        app->updateScreen(this);
        return;
    }

    if (app->getKeyState(VK_CONTROL) && app->getKeyState('X'))
    {
        copyInBuf();
        backSpace();
        lastTimeClicked = clock();
        setActiveWindow(this);
        app->updateScreen(this);
        return;
    }

    if (app->getKeyState(VK_CONTROL) && app->getKeyState('A'))
    {
        selectAll();
        app->updateScreen(this);
        return;
    }

    if (app->getKeyState(VK_RETURN))
    {
        confirmEnter();
        cursor.mbUpCursor({});
        if (getInputMode())app->updateScreen(this);
        getInputMode() = 0;
        app->setCursor();
        return;
    }

    /*
    if (app->isDoubleClick() && (rect-rect.pos).inRect(getMousePos()) && clock() - lastTimeClicked > specButtonsDelta)
    int left = 0;
    int right = 0;
    startAndEndOfClickedWord(cursor.currPos, left, right);
    cursor.moveCursorTo(left, true);
    cursor.moveCursorTo(right, false);
    lastTimeClicked = clock();
    */
}

void StringButton2::checkKeyboardChar(int key)
{
    
    int symbol = key;
   
    if (!isSymbolAllowed(symbol))
    {                    
        return;
    }

    if (currentTextSize < maxTextSize)
    {
        //getTextAfterEnteringSymbol(text, text, currentTextSize, cursor.currPos, symbol);
        setActiveWindow(this);

        if (!cursor.isActiveSelection())
        {
            shiftTextForward(text, cursor.currPos, currentTextSize);
            text[cursor.currPos] = symbol;
            currentTextSize = strlen(text);
            cursor.moveRight();
            
        }
        else
        {
            shiftTextBack(text, max(cursor.currPos, cursor.startPos), currentTextSize, abs(cursor.currPos - cursor.startPos) - 1);
            text[min(cursor.currPos, cursor.startPos)] = symbol;
            currentTextSize = strlen(text);
            if (cursor.currPos > cursor.startPos)
            {
                cursor.moveCursorTo(cursor.startPos);
            }
            else
            {
                cursor.moveCursorTo(cursor.currPos);
            }
            cursor.moveRight();
        }

        app->updateScreen(this);
        
    }

}

bool StringButton2::isAnyNormalKeyButtonClicked()
{
    // буквы да цифры
    for (int i = 0x30; i < 0x5A; i++)
    {
        if (app->getAsyncKeyState(i))
        {
            return true;
        }
    }
    //знаки препинания
    for(int i = 0xBB; i < 0xDF; i++)
    {
        if (app->getAsyncKeyState(i))
        {
            return true;
        }
    }

    if (app->getAsyncKeyState(VK_SPACE))
    {
        return true;
    }
    return false;
}

int StringButton2::findClickedKey()
{
    for (int i = 0; i <= 0xFF; i++)
    {
        if (app->getAsyncKeyState(i))
        {
            return i;
        }
    }

    return 0;
}

void StringButton2::drawCursor()
{
    


}
