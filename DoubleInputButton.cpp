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
            if ((_text[0] == '-' && strText.size() > 1) || _text[0] != '-')
            {
                resultNum = std::stod(strText);
            }
        }
    }

    return resultNum;

}



void* DoubleInputButton::getParameterFromText(char* text, int textSize/* = 0*/)
{
    static double answer = getDoubleFromText(text, textSize);
    answer = getDoubleFromText(text, textSize);
    return &answer;
}

void DoubleInputButton::parameterToString(char* text, void* _num)
{
    double* intNum = (double*)_num;
    if (text && intNum)
    {
        (void)sprintf(text, "%lf", *intNum);
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
    bool othersKey = InputButton2::isSymbolAllowed(symbol);
    if (othersKey)
    {
        return othersKey;
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