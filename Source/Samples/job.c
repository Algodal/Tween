//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Tw/twTween.h"
#include "utils.h"

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

    /*Tw_TweenPreset preset2 = {
        .delay = 0,
        .duration = 1,
        .from = 75,
        .to = 200
    };*/

    Tw_Bool res = false;

    //Running Tween Job Thread in Detach State. Thread will not wait for Main program. Therefore we use Sleep to wait.
    res = Tw_RunTweenJob(preset1, TW_EASE_IN_BOUNCE, TW_DETACH, &translation, NULL, 0);

    if(!res)
    {
        printf("Failed to Run Tween Job!");
        exit(EXIT_FAILURE);
    }

    //Tw_TweenId id1 = Tw_AllocateTweenJob(preset1, TW_EASE_IN_BOUNCE, 0, 0, TW_IGNORE, &translation, NULL, 0);
    //Tw_TweenId id2 = Tw_AllocateTweenJob(preset2, TW_EASE_OUT_QUAD, &scale, NULL, 0, 0, 0);

    /*if(id1 == 0) {
        printf("Failed to Run Tween Job!");
        exit(EXIT_FAILURE);
    }*/

    /*if(id2 == 0)
    {
        printf("Failed to Run Tween Job!");
        exit(EXIT_FAILURE);
    }*/

    for(int i = 0; i < 1000; i++)
    {
        printf("translation: %.2f | scale: %.2f\n", translation, scale);
    }

    sleep_seconds(duration * 2);
    printf("done!\n");
    return EXIT_SUCCESS;
}