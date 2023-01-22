#pragma once
#include "InputButton2.h"



void InputButton2::parameterToString(char* text, void* _num)
{
    int* intNum = (int*)_num;
    if (text && intNum)
    {
        (void)sprintf(text, "%d", *intNum);
    }
}

void* InputButton2::getParameterFromText(char* text, int textSize/* = 0*/)
{
    static int answer = getIntFromText(text, textSize);
    return &answer;
}

bool InputButton2::parameterIsBiggerMaximum(void* _num)
{
    if (*((int*)_num) > *((int*)maxParameter))
    {
        return true;
    }
    return false;
}


bool InputButton2::parameterIsSmallerMinimum(void* _num)
{
    if (*((int*)_num) < *((int*)minParameter))
    {
        return true;
    }
    return false;
}


bool InputButton2::isParametersEqual(void* a, void* b)
{
    if (*((int*)a) == *((int*)a))
    {
        return true;
    }
    return false;
}

void InputButton2::setParameter(void* source)
{
    parameter = source;
}

void InputButton2::copyParameter(const void* source)
{
    int* _dest = (int*)parameter;
    int* _source = (int*)source;
    *_dest = *_source;
}


int InputButton2::getIntFromText(char* _text, int textSize/* = 0 */)
{
    /*
    int resultNum = 0;
    if (!textSize) textSize = strlen(_text);

    bool isNegative = 0;

    if (_text)
    {
        if (_text[0] == '-')
        {
            textSize--;
            _text += 1; 
            isNegative = 1;
        }
    }

    for (int i = 0; i < textSize; i++)
    {
        if (!_text[i]) break;

        resultNum += std::lround( (_text[i] - '0') * pow(10, textSize - i - 1) );
    }

    if (isNegative)
    {
        resultNum *= -1;
    }
    */
    int resultNum = 0;
    if (_text)
    {
        if (_text[0] != 0)
        {
            resultNum = std::atoi(_text);
        }
    }

    return resultNum;

}



bool InputButton2::isSymbolAllowed(char symbol)
{

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
    if (mode == NEGATIVE_MODE)
    {
        if (symbol == '-')
        {      
            if (text)
            {
                std::string stringVersion = text;
                size_t pos = stringVersion.find(symbol);
                if (pos == std::string::npos)
                {
                    if (cursor.currPos == 0 || cursor.startPos == 0)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}



void InputButton2::modifyOutput(char* outputStr, char* originalStr)
{
    assert(outputStr && originalStr);
    if (mode == PERCANTAGE_MODE)
    {
        sprintf(outputStr, "%s%%", originalStr);
        return;
    }

    (void)sprintf(outputStr, "%s", originalStr);

    
}



void InputButton2::confirmEnter()
{
    /*
    void* numBeforeRedacting = getParameterFromText(textBeforeRedacting, 0));
    //sprintf(text, "%d", *parameter);
    parameterToString(text, parameter);
    void* numAfterRedacting = getParameterFromText(text, 0);
    /*
    if (parameterIsBiggerMaximum(&numAfterRedacting))
    {
        strcpy(text, textBeforeRedacting);
        return;
    }
    if (parameterIsSmallerMinimum(&numAfterRedacting))
    {
        strcpy(text, textBeforeRedacting);
        return;
    }
    
    if (numBeforeRedacting != numAfterRedacting && confirmInput)
    {
        *confirmInput = true; 
    }
    */
}

void InputButton2::doBeforeMainBlock()
{
    void* currNum = getParameterFromText(text);
    if ((!isParametersEqual(currNum, parameter) && !getInputMode()) || (text[0] == NULL && !getInputMode()))
    {
        parameterToString(text, parameter);
    }
}

void InputButton2::doAfterMainBlock()
{
    void* finalNum = getParameterFromText(text, 0);
    if (parameterIsBiggerMaximum(finalNum)) finalNum = maxParameter;

    copyParameter(finalNum);
}
