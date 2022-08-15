#pragma once
#include "InputButton2.h"


int InputButton2::getIntFromText(char* _text, int textSize/* = 0 */)
{
    int resultNum = 0;
    if (!textSize) textSize = strlen(_text);

    for (int i = 0; i < textSize; i++)
    {
        if (!_text[i]) break;

        resultNum += std::lround( (_text[i] - '0') * pow(10, textSize - i - 1) );
    }

    return resultNum;

}



bool InputButton2::isSymbolAllowed(char symbol)
{
    int currentInt = getIntFromText (text, currentTextSize);

    /*
    char* newText = new char[currentTextSize + 2]{};

    getTextAfterEnteringSymbol(newText, text, currentTextSize, cursor.currPos, symbol);
    int newInt = getIntFromText(newText, 0);
    assert(maxParametr);
    if (newInt > *maxParametr)
    {
        return false;
    }

    delete[] newText;
    */
    if ('0' <= symbol && symbol <= '9')
    {
        return true;
    }
    return false;
}

void InputButton2::setParameter(int* newParameter)
{
    parameter = newParameter;

}


void InputButton2::modifyOutput(char* outputStr, char* originalStr)
{
    assert(outputStr && originalStr);
    if (mode == 1)
    {
        sprintf(outputStr, "%s%%", originalStr);
        return;
    }

    sprintf(outputStr, "%s", originalStr);

    
}



void InputButton2::confirmEnter()
{
    int numBeforeRedacting = getIntFromText(textBeforeRedacting, 0);
    sprintf(text, "%d", *parameter);
    int numAfterRedacting = getIntFromText(text, 0);
    if (numAfterRedacting > *maxParametr)
    {
        strcpy(text, textBeforeRedacting);
        return;
    }
    if (numBeforeRedacting != numAfterRedacting && confirmInput)
    {
        *confirmInput = true; 
    }
}

void InputButton2::doBeforeMainBlock()
{
    int currNum = getIntFromText(text);
    if ((currNum != *parameter && !getInputMode()) || (text[0] == NULL && !getInputMode()))
    {
        sprintf(text, "%d", *parameter);
    }
}

void InputButton2::doAfterMainBlock()
{
    int finalNum = getIntFromText(text, 0);
    if (finalNum > *maxParametr) finalNum = *maxParametr;

    *parameter = finalNum;
}
