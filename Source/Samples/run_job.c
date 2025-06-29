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

    Tw_TweenPreset preset1 = {
        .delay = 0,
        .duration = 3,
        .from = 0,
        .to = 100
    };

    Tw_TweenPreset preset2 = {
        .delay = 0,
        .duration = 3,
        .from = 75,
        .to = 200
    };

    clock_t stamp = clock();

    Tw_RunJob(preset1, TW_EASE_IN_BOUNCE, &translation, NULL, 0);
    Tw_RunJob(preset2, TW_EASE_OUT_QUAD, &scale, NULL, 0);

    while(((clock() - stamp) / CLOCKS_PER_SEC) < 3.0f)
    {
        printf("translation: %.2f | scale: %.2f\n", translation, scale);
    }

    printf("done!\n");
    return EXIT_SUCCESS;
}