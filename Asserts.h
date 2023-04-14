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

#define rmassert(condition, _app, whatreturn){massert(condition, _app); if(condition == NULL) return whatreturn;};

#define assert(condition) {gassert(condition)};

#define rassert(condition, whatreturn) {assert(condition); if(condition == NULL) return whatreturn;};
#define $s ;

#define exceptionCheck(condition)                                   \
{                                                            \
    if (condition == NULL)                                   \
    {                                                        \
        throw std::exception(#condition);                   \
    }                                                        \
}                                                             \


#define EC(condition) exceptionCheck(condition)