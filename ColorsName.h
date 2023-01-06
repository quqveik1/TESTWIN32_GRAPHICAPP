#pragma once
#include <wingdi.h>
            
enum COLORSNAME
{
    C_BLACK = RGB(0, 0, 0),   //!< ������ ����.
    C_BLUE = RGB(0, 0, 128),   //!< �����-����� ����. <i>����� �����.</i>
    C_GREEN = RGB(0, 128, 0),   //!< ������� ����.
    C_CYAN = RGB(0, 128, 128),   //!< ��������� ����.
    C_RED = RGB(128, 0, 0),   //!< �����-������� ����. <i>������� ������.</i>
    C_MAGENTA = RGB(128, 0, 128),   //!< �����-��������� ����.
    C_BROWN = RGB(128, 128, 0),   //!< ���������� ����. <i>����������. Do it yourself with RGB().</i>
    C_ORANGE = RGB(255, 128, 0),   //!< ��������� ����.
    C_GRAY = RGB(160, 160, 160),   //!< ����� ����.
    C_DARKGRAY = RGB(128, 128, 128),   //!< �����-����� ����.
    C_LIGHTGRAY = RGB(192, 192, 192),   //!< ������-����� ����.
    C_LIGHTBLUE = RGB(0, 0, 255),   //!< ������-����� ����.
    C_LIGHTGREEN = RGB(0, 255, 128),   //!< ������-������� ����.
    C_LIGHTCYAN = RGB(0, 255, 255),   //!< ������-��������� ����.
    C_LIGHTRED = RGB(255, 0, 128),   //!< ������-������� ����.   <i>�� ������ ������� �������.</i>
    C_LIGHTMAGENTA = RGB(255, 0, 255),   //!< ������-��������� ����. <i>��� ����� ������� �������.</i>
    C_PINK = RGB(255, 128, 255),   //!< ������� ��������� :)
    C_YELLOW = RGB(255, 255, 128),   //!< ������ ����.
    C_WHITE = RGB(255, 255, 255),   //!< ����� ����.
    C_57 = RGB(57, 57, 57)
};


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