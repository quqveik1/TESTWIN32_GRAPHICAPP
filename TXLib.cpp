#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>


#define gassert(condition)                                   \
{                                                            \
    if (condition == NULL)                                   \
    {                                                        \
        printf("[%s] == NULL", #condition);                   \
        (void)_getch();                                      \
    }                                                        \
}                                                            \


#define massert(condition, _app)                             \
{                                                            \
    if (condition == NULL)                                   \
    {                                                        \
        char _tempStr[MAX_PATH] = {};                        \
        sprintf(_tempStr, "[%s] == NULL", #condition);        \
        _app->messageBox(_tempStr, "������", MB_OK | MB_ICONINFORMATION);         \
    }                                                        \
}                                                            \

#define assert(condition) {gassert(condition)};
#define $s ;
enum COLORS
{
    TX_BLACK = RGB(0, 0, 0),   //!< ������ ����.
    TX_BLUE = RGB(0, 0, 128),   //!< �����-����� ����. <i>����� �����.</i>
    TX_GREEN = RGB(0, 128, 0),   //!< ������� ����.
    TX_CYAN = RGB(0, 128, 128),   //!< ��������� ����.
    TX_RED = RGB(128, 0, 0),   //!< �����-������� ����. <i>������� ������.</i>
    TX_MAGENTA = RGB(128, 0, 128),   //!< �����-��������� ����.
    TX_BROWN = RGB(128, 128, 0),   //!< ���������� ����. <i>����������. Do it yourself with RGB().</i>
    TX_ORANGE = RGB(255, 128, 0),   //!< ��������� ����.
    TX_GRAY = RGB(160, 160, 160),   //!< ����� ����.
    TX_DARKGRAY = RGB(128, 128, 128),   //!< �����-����� ����.
    TX_LIGHTGRAY = RGB(192, 192, 192),   //!< ������-����� ����.
    TX_LIGHTBLUE = RGB(0, 0, 255),   //!< ������-����� ����.
    TX_LIGHTGREEN = RGB(0, 255, 128),   //!< ������-������� ����.
    TX_LIGHTCYAN = RGB(0, 255, 255),   //!< ������-��������� ����.
    TX_LIGHTRED = RGB(255, 0, 128),   //!< ������-������� ����.   <i>�� ������ ������� �������.</i>
    TX_LIGHTMAGENTA = RGB(255, 0, 255),   //!< ������-��������� ����. <i>��� ����� ������� �������.</i>
    TX_PINK = RGB(255, 128, 255),   //!< ������� ��������� :)
    TX_YELLOW = RGB(255, 255, 128),   //!< ������ ����.
    TX_WHITE = RGB(255, 255, 255),   //!< ����� ����.
    TX_TRANSPARENT = 0xFFFFFFFF,            //!< ���������� ����. <i>��������� ���������.</i>  //-V112
    TX_NULL = TX_TRANSPARENT,        //!< ���������� ����. <i>��������� ���������.</i>
    TX_BLM = TX_BLACK,              //!< �������������� ��������������� ��������� ����!
    TX_white = TX_WHITE              //!< BLM-compatible name for this color.
};
