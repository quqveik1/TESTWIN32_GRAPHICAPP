#pragma once

struct ConsoleOutput
{
    const int consoleLength = 1000;
    char currFrameText[1000] = {};
    char globalText[1000] = {};

    virtual int addText(const char* str, int isGlobal = false);
    virtual int clear();
};