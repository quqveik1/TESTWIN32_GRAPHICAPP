#include <iostream>
#include <cstdio>

#ifdef _DEBUG
#define dcout std::cout
#else
#define dcout if(false) std::cout
#endif

#ifdef _DEBUG
#define dprintf(...) printf(__VA_ARGS__)
#else
#define dprintf(...) (void)0
#endif