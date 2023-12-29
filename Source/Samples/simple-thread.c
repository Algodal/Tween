//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tw/tw-tween.h"

//thread allows you to pass an optional function for an generic purpose
//I use this for logging purposes
Tw_ThreadFunctionRequest scale_logger(Tw_ThreadFunctionParam param)
{
    printf("[%f seconds] SCALE: %f, processing %.0f%%\n", param.time, param.value, param.percent*100);
    return TW_THREAD_FUNCTION_NOTHING;
}

Tw_ThreadFunctionRequest trans_logger(Tw_ThreadFunctionParam param)
{
    printf("[%f seconds] TRANSLATION: %f, processing %.0f%%\n", param.time, param.value, param.percent*100);
    return TW_THREAD_FUNCTION_NOTHING;
}

int main()
{
    float scale;  //this is a random property
    float translation; //another property

    float from = 40;
    float to   = 250;
    Tw_Instance* i = Tw_CreateInstance(
        from, to, TW_EASE_IN_OUT_CUBIC, &scale, TW_FLOAT_UPDATER);
    
    printf("Tweening from %f to %f\n", from, to);
    //Thread handles the loop for us
    Tw_CreateThread(i, 30, 5, scale_logger, TW_LOOP_NONE); //Thread starts running update immediately

    //wait some time before starting next thread
    for(int n = 0; n < 64000000; n++); 

    from = 0;
    to = 1000;
    Tw_Instance* trans_i = 0;
    Tw_CreateTween(
        &trans_i, 
        from, to, 
        TW_EASE_OUT_ELASTIC, 
        &translation, TW_FLOAT_UPDATER,
        16, 4, trans_logger, TW_LOOP_NONE);
    
    //Cause the main program to wait until the thread is finished
    Tw_JoinThread(i, NULL);
    Tw_JoinThread(trans_i, NULL);

    printf("Main Existed\n");
    return EXIT_SUCCESS;
}










