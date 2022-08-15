#pragma once
#include "ConsoleOutput.h"
#include "stdio.h"
int ConsoleOutput::addText(const char* str, int isGlobal/* = false*/)
{
    if (isGlobal)
    {
        sprintf(globalText, "%s%s\n", globalText, str);
    }

    int numerofAdded = sprintf(currFrameText, "%s%s\n", currFrameText, str);

    if (numerofAdded == 2 || ((currFrameText[0] == '\0') && str[0] != '\0'))
    {
        return 0;
    }
    else
    {
        return numerofAdded;
    }
}

int ConsoleOutput::clear()
{
    int cDeletedItems = 0;
    for (int i = 0; i < consoleLength; i++)
    {
        if (currFrameText[i])
        {
            currFrameText[i] = NULL;
            cDeletedItems++;
        }
    }

    return cDeletedItems;
}