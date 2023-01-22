#pragma once
#include "DoubleInputButton.h"
#include <iostream>
#include <string>


double DoubleInputButton::getDoubleFromText(const char* _text, int textSize/* = 0 */)
{
    double resultNum = 0;
    if (_text)
    {
        if (_text[0] != 0)
        {
            std::string strText = _text;
            resultNum = std::stod(strText);
        }
    }

    return resultNum;

}



void* DoubleInputButton::getParameterFromText(char* text, int textSize/* = 0*/)
{
    static double answer = getDoubleFromText(text, textSize);
    return &answer;
}

void DoubleInputButton::parameterToString(char* text, void* _num)
{
    double* intNum = (double*)_num;
    if (text && intNum)
    {
        (void)sprintf(text, "%d", *intNum);
    }
}

bool DoubleInputButton::parameterIsBiggerMaximum(void* _num)
{
    if (*((double*)_num) > *((double*)maxParameter))
    {
        return true;
    }
    return false;
}


bool DoubleInputButton::parameterIsSmallerMinimum(void* _num)
{
    if (*((double*)_num) < *((double*)minParameter))
    {
        return true;
    }
    return false;
}


bool DoubleInputButton::isParametersEqual(void* a, void* b)
{
    if (*((double*)a) == *((double*)a))
    {
        return true;
    }
    return false;
}


void DoubleInputButton::copyParameter(const void* source)
{
    double* _dest = (double*)parameter;
    double* _source = (double*)source;
    *_dest = *_source;
}


bool DoubleInputButton::isSymbolAllowed(char symbol)
{

    /*
    char* newText = new char[currentTextSize + 2]{};

    getTextAfterEnteringSymbol(newText, text, currentTextSize, cursor.currPos, symbol);
    int newInt = getDoubleFromText(newText, 0);
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
    if (symbol == '.')
    {
        if (text)
        {
            std::string stringVersion = text;
            size_t pos = stringVersion.find(symbol);
            if (pos == std::string::npos)
            {
                return true;
            }
        }
    }
    return false;
}

void DoubleInputButton::modifyOutput(char* outputStr, char* originalStr)
{
    assert(outputStr && originalStr);
    if (mode == 1)
    {
        sprintf(outputStr, "%s%%", originalStr);
        return;
    }

    sprintf(outputStr, "%s", originalStr);


}



void DoubleInputButton::confirmEnter()
{
    int numBeforeRedacting = getDoubleFromText(textBeforeRedacting, 0);
    sprintf(text, "%lf", *parameter);
    int numAfterRedacting = getDoubleFromText(text, 0);
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

void DoubleInputButton::doBeforeMainBlock()
{
    int currNum = getDoubleFromText(text);
    if (text)
    {
        if ((currNum != *parameter && !getInputMode()) || (text[0] == NULL && !getInputMode()))
        {
            sprintf(text, "%lf", *parameter);
        }
    }
}

void DoubleInputButton::doAfterMainBlock()
{
    int finalNum = getDoubleFromText(text, 0);
    if (finalNum > *maxParametr) finalNum = *maxParametr;

    *parameter = finalNum;
}
