#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h> // Use <SDL.h> if installed differently

#include "Tw/twTween.h"

#define FRAME_RATE 60
#define FRAME_TIME_MS (1000 / FRAME_RATE)

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    Tw_EasingFunction easingfn = TW_EASE_OUT_QUAD;
    Tw_TweenPreset preset = Tw_InitTween(0.0f, 100.0f, 3.0f, 0.0f);
    Tw_TweenId tween = Tw_AllocateTweenState(preset, easingfn);

    if (!tween) {
        fprintf(stderr, "Failed to allocate tween.\n");
        SDL_Quit();
        return EXIT_FAILURE;
    }

    Uint64 lastTicks = SDL_GetTicks64();
    float delta = 0.0f;
    long frame = 0;

    while (Tw_TweenRunning(tween)) {
        Uint64 currentTicks = SDL_GetTicks64();
        Uint64 elapsedMs = currentTicks - lastTicks;

        if (elapsedMs >= FRAME_TIME_MS || frame == 0) {
            lastTicks = currentTicks;
            delta = elapsedMs / 1000.0f;

            Tw_UpdateTweenState(tween, delta);
            float value = Tw_GetTweenStateValue(tween);
            float progress = Tw_GetTweenStateProgress(tween);
            float eased_progress = easingfn(progress);

            printf("Frame %ld) Tween Value: %.2f, Progress: %.4f, Eased Progress: %.4f\n",
                   frame++, value, progress, eased_progress);
        }

        SDL_Delay(1); // Prevent busy-waiting
    }

    printf("Tween complete!\n");
    Tw_FreeTweenId(tween);
    SDL_Quit();
    return EXIT_SUCCESS;
}
