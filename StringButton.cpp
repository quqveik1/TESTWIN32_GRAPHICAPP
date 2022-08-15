#pragma once
#include "StringButton.h"


void StringButton::draw ()
{
    $s;
    bool switched = false;
    bool isShifted = false;
    bool deleteChar = false;


    if (manager->getActiveWindow () == this)
    {
        if (checkDeltaTime (lastTimeClicked))
        {
            if (app->getAsyncKeyState(VK_LEFT) && cursorPosition >= 0)
            {
                cursorMovement (VK_LEFT);
                //printf ("left");
                switched = true;
            }
            if (app->getAsyncKeyState(VK_RIGHT) && cursorPosition <= textLen - 2)
            {
                cursorMovement (VK_RIGHT);
                switched = true;
            }

            if (app->getAsyncKeyState (VK_BACK))
            {
                backSpace ();
            }

            checkSymbols ();
        }

        if (clock() % 500 < 250)
        {
            if (!switched)
                shiftArrForward (&inText[cursorPosition + 1], 10);

            inText[cursorPosition + 1] = '|';
            printf ("");
        }
        else
        {
            if (!switched)
                shiftArrForward (&inText[cursorPosition + 1], 10);

            inText[cursorPosition + 1] = ' ';
        }
    }

    //txSetTextAlign (TA_LEFT);
    //app->setColor (TX_WHITE);

    //txTextOut (rect.pos.x, rect.pos.y, inText);

    if (manager->getActiveWindow () == this) shiftArrBack (&inText[cursorPosition + 1], 10);

    if (onlyNums)
    {
        double num;
        if (!strcmp ("", inText)) num = 0;

        sscanf  (inText, "%lf", &num);
        if (num > MaxNum)
        {
            if ( ((int) log10 (num)) - ((int) log10 (MaxNum)) >= 1)
            {
                cursorPosition--;
            }
            sprintf (inText, "%d", (int) MaxNum);
        }
    }

    return;
}

void stringToInt (const char *str, const int  strLen, int &num)
{
    num = 0;
    for (int i = 0; i < strLen; i++)
    {
        num += (str[i] - 48) * pow (10, strLen - i - 1);
    }
}


void StringButton::checkSymbols ()
{
    if (!_kbhit ())	return;
    int symbol = _getch ();

    if (! (symbol >= 48 && symbol <= 57) && onlyNums) return;
    if (lastButton == symbol || symbol == '\b') return;
    if (symbol == 48 &&	onlyNums && cursorPosition == -1) return;

    lastTimeClicked = clock();
    shiftArrForward(&inText[cursorPosition + 1], textLen - cursorPosition);
    inText[cursorPosition + 1] = symbol;
    cursorPosition++;
    textLen++;
}

bool checkDeltaTime (int lastTimeClicked)
{
    const int DELTACLOCKTIME = 100;
    return clock () - lastTimeClicked > DELTACLOCKTIME;
}

void StringButton::backSpace ()
{
    if (cursorPosition >= 0)
    {
        lastTimeClicked = clock();
        shiftArrBack(&inText[cursorPosition], textLen - cursorPosition  + 1);
        cursorPosition--;
        textLen--;
    }
}


void StringButton::cursorMovement (int side)
{
    bool validMovement = false;
    if (side == VK_RIGHT) validMovement = (cursorPosition < textLen - 2);
    if (side == VK_LEFT)  validMovement = (cursorPosition >= 0);

    /*
    if (validMovement && clock () - lastTimeClicked > _app->systemSettings->DELTACLOCKTIME)
    {
        lastTimeClicked = clock();
        //shiftArrBack(&inText[cursorPosition + 1], textLen - cursorPosition);
        if (side == VK_RIGHT) cursorPosition++;
        if (side == VK_LEFT) cursorPosition--;
        shiftArrForward(&inText[cursorPosition + 1], textLen - cursorPosition);
    }

}

