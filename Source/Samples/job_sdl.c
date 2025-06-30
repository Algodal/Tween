// Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h> // SDL for ticks and sleep

#include "Tw/twTween.h"
#include "utils.h" // your own utility header if needed

int main()
{
    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    float scale = 0.0f;
    float translation = 0.0f;
    const float duration = 3.0f;

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

    // SDL_GetTicks64 returns ms, so tickPerSec = 1000
    res = Tw_RunTweenJob(preset1, TW_EASE_IN_BOUNCE, &translation, (Tw_Ticker)SDL_GetTicks64, 1000);
    if (!res) {
        printf("Failed to Run Tween Job!\n");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    res = Tw_RunTweenJob(preset2, TW_EASE_OUT_QUAD, &scale, (Tw_Ticker)SDL_GetTicks64, 1000);
    if (!res) {
        printf("Failed to Run Tween Job!\n");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < INT_MAX / 10000; i++) {
        printf("translation: %.2f | scale: %.2f\n", translation, scale);
    }

    SDL_Delay((Uint32)(duration * 2)); // Wait for completion
    printf("done!\n");

    SDL_Quit();
    return EXIT_SUCCESS;
}
