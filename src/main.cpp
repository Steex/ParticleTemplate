// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file main.cpp
// author: Gennady Filazopovich



#ifdef PLATFORM_WINDOWS

#define ENTRY_POINT_HERE
#include "head.h"

#else

extern void run(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    run(argc, argv);
    return 0;
}

#endif // PLATFORM_WINDOWS