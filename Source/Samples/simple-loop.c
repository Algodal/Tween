//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tw/tw-tween.h"


int main()
{
    //The property is provided by the user.
    //Can be anything or any type (not just float).
    //If it is anything other than a simple float
    //user would need to provide a user defined property updater functions.
    //Otherwise, can use the default float updater function.
    float property;  //this is a random property

    float from = 0;
    float to   = 100;
    Tw_Instance* i = Tw_CreateInstance(
        from, to, TW_EASE_IN_BACK, &property, TW_FLOAT_UPDATER);
    
    printf("Tweening from %f to %f\n", from, to);
    //random loop (for, while, etc)
    int count = 0;
    const int delta = 1;
    while(0 == Tw_IsDone(i))
    {
        count += delta;
        Tw_Update(i, (Tw_Float)delta);
        printf("Input %d, Property: %f(direct), %f(indirect)\n", 
            count, property, Tw_GetValue(i));
    }
    return EXIT_SUCCESS;
}










