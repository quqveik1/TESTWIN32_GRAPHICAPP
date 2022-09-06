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
        _app->messageBox(_tempStr, "Ошибка", MB_OK | MB_ICONINFORMATION);         \
    }                                                        \
}                                                            \

#define assert(condition) {gassert(condition)};
#define $s ;
enum COLORS
{
    TX_BLACK = RGB(0, 0, 0),   //!< Черный цвет.
    TX_BLUE = RGB(0, 0, 128),   //!< Темно-синий цвет. <i>Плохо виден.</i>
    TX_GREEN = RGB(0, 128, 0),   //!< Зеленый цвет.
    TX_CYAN = RGB(0, 128, 128),   //!< Бирюзовый цвет.
    TX_RED = RGB(128, 0, 0),   //!< Темно-красный цвет. <i>Слишком темный.</i>
    TX_MAGENTA = RGB(128, 0, 128),   //!< Темно-малиновый цвет.
    TX_BROWN = RGB(128, 128, 0),   //!< Коричневый цвет. <i>Некрасивый. Do it yourself with RGB().</i>
    TX_ORANGE = RGB(255, 128, 0),   //!< Оранжевый цвет.
    TX_GRAY = RGB(160, 160, 160),   //!< Серый цвет.
    TX_DARKGRAY = RGB(128, 128, 128),   //!< Темно-серый цвет.
    TX_LIGHTGRAY = RGB(192, 192, 192),   //!< Светло-серый цвет.
    TX_LIGHTBLUE = RGB(0, 0, 255),   //!< Светло-синий цвет.
    TX_LIGHTGREEN = RGB(0, 255, 128),   //!< Светло-зеленый цвет.
    TX_LIGHTCYAN = RGB(0, 255, 255),   //!< Светло-бирюзовый цвет.
    TX_LIGHTRED = RGB(255, 0, 128),   //!< Светло-красный цвет.   <i>Не самого лучшего оттенка.</i>
    TX_LIGHTMAGENTA = RGB(255, 0, 255),   //!< Светло-малиновый цвет. <i>Еще менее лучшего оттенка.</i>
    TX_PINK = RGB(255, 128, 255),   //!< Розовый гламурный :)
    TX_YELLOW = RGB(255, 255, 128),   //!< Желтый цвет.
    TX_WHITE = RGB(255, 255, 255),   //!< Белый цвет.
    TX_TRANSPARENT = 0xFFFFFFFF,            //!< Прозрачный цвет. <i>Отключает рисование.</i>  //-V112
    TX_NULL = TX_TRANSPARENT,        //!< Прозрачный цвет. <i>Отключает рисование.</i>
    TX_BLM = TX_BLACK,              //!< Альтернативный политкорректный трендовый цвет!
    TX_white = TX_WHITE              //!< BLM-compatible name for this color.
};
