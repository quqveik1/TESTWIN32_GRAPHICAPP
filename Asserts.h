#pragma once

#include <conio.h>

#define gassert(condition)                                   \
{                                                            \
    if (condition == NULL)                                   \
    {                                                        \
        (void)printf("[%s] == NULL", #condition);                   \
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