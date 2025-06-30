//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Tw/twTween.h"

int main()
{
    float scale;  //property
    float translation; //property
    const float duration = 3;// time of tween

    Tw_TweenPreset preset1 = {
        .delay = 0,
        .duration = duration,
        .from = 0,
        .to = 100
    };

    Tw_TweenPreset preset2 = {
        .delay = 0,
        .duration = duration,
        .from = 75,
        .to = 200,
        .loop = TW_FOREVER
    };

    Tw_Bool res = false;
    int count;    

    Tw_TweenId id1 = Tw_AllocateTweenJob(preset1, TW_EASE_IN_BOUNCE, &translation, NULL, 0);
    
    if(!id1)
    {
        printf("Failed to Run Tween Job!");
        exit(EXIT_FAILURE);
    }

    count = 0;
    while(Tw_TweenRunning(id1))
    {
        if(count++ % 10 == 0) printf("translation: %.2f\n", translation);
    }
    Tw_FreeTweenId(id1);

    for(int i = 0; i < 10000; i++); //wait a little

    Tw_TweenId id2 = Tw_AllocateTweenJob(preset2, TW_EASE_OUT_QUAD, &scale, NULL, 0);

    if(!id2)
    {
        printf("Failed to Run Tween Job!");
        exit(EXIT_FAILURE);
    }


    //infinite loop due to .loop parameter set to true in Tw_AllocateTweenJob
    count = 0;
    while(Tw_TweenRunning(id2))
    {
        if(count++ % 10 == 0) printf("scale: %.2f\n", scale);

        if (count == 1000) 
        {
            printf("Terminating Loop\n");
            Tw_TweenEndLoop(id2);
        }
    }
    Tw_FreeTweenId(id2);


    printf("done!\n");
    return EXIT_SUCCESS;
}