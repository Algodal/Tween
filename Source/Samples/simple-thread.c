//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tw/tw-tween.h"

//thread allows you to pass an optional function for an generic purpose
//I use this for logging purposes
void logger(Tw_Float current_value, Tw_Float time_passed)
{
    printf("[%f seconds] My Scale: %f\n", time_passed, current_value);
}

int main()
{
    float scale;  //this is a random property

    float from = 40;
    float to   = 250;
    Tw_Instance* i = Tw_CreateInstance(
        from, to, TW_EASE_IN_OUT_CUBIC, &scale, TW_FLOAT_UPDATER);
    
    printf("Tweening from %f to %f\n", from, to);
    //Thread handles the loop for us
    Tw_CreateThread(i, 30, 5, logger); //Thread starts running update immediately
    
    //Cause the main program to wait until the thread is finished
    Tw_JoinThread(i, NULL);
    printf("Main Existed\n");
    return EXIT_SUCCESS;
}










