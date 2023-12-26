//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tw-functions.h"

#ifdef DEBUG
void Tw_Assert(bool cond, const char* msg)
{
    if(cond == false)
    {
        printf("Tween error: %s\n", msg);
        exit(EXIT_FAILURE);
    }
}
#endif









