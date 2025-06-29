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
        .to = 200
    };

    Tw_Bool res = false;

    Tw_TweenId id1 = Tw_AllocateTweenJob(preset1, TW_EASE_IN_BOUNCE, 0, 0, TW_JOIN, &translation, NULL, 0);
    if(!id1)
    {
        printf("Failed to Run Tween Job!");
        exit(EXIT_FAILURE);
    }
    Tw_FreeTweenId(id1);

    

    //Ignore neither detach or join. User required to join manually. Ignore is not available for RunTweenJob func
    //need to wait on thread before freeing id
    //Loop is set to true. This job will run infinitely
    Tw_TweenId id2 = Tw_AllocateTweenJob(preset2, TW_EASE_OUT_QUAD, true, false, TW_DETACH, &scale, NULL, 0);

    if(!id2)
    {
        printf("Failed to Run Tween Job!");
        exit(EXIT_FAILURE);
    }


    //infinite loop due to .loop parameter set to true in Tw_AllocateTweenJob
    while(Tw_TweenJobRunning(id2))
    {
        printf("translation: %.2f | scale: %.2f\n", translation, scale);
    }
    //Tw_TweenJobJoin(id2);
    Tw_FreeTweenId(id2);


    printf("done!\n");
    return EXIT_SUCCESS;
}