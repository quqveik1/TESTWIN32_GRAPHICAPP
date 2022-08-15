#pragma once
struct DebugInfo
{
    int line;
    const char *func;
    const char *file;
};


#define qassert(condition, info)         \
{                                              \
                                             \
    if (condition == NULL) printf ("[file: %s, func: %s, line: %d]\n", info.file, info.func, info.line);                               \
    if (condition == NULL) assert (condition);                                      \
}  

#define getDebugInfo {__LINE__, __FUNCSIG__, __FILE__}