#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Tw/twTween.h"

#define FRAME_RATE 60
#define FRAME_TIME (1.0f / FRAME_RATE)
#define FRAME_TICKS (FRAME_TIME * CLOCKS_PER_SEC)

int main()
{
    Tw_EasingFunction easingfn = TW_EASE_OUT_QUAD;
    Tw_TweenPreset preset = Tw_InitTween(0.0f, 100.0f, 3.0f, 0.0f);
    Tw_TweenId tween = Tw_AllocateTweenState(preset, easingfn);

    if (!tween) {
        fprintf(stderr, "Failed to allocate tween.\n");
        return EXIT_FAILURE;
    }

    clock_t lastTime = clock();
    float delta = 0.0f;
    long frame = 0;

    while (true) {
        clock_t now = clock();
        clock_t ticks = now - lastTime;
        if(ticks >= FRAME_TICKS || frame == 0)
        {
            lastTime = now;
            delta = (float)(ticks) / CLOCKS_PER_SEC;
            Tw_UpdateTweenState(tween, delta);
            float value = Tw_GetTweenStateValue(tween);
            float progress = Tw_GetTweenStateProgress(tween);
            float eased_progress = easingfn(progress);
            printf("Frame %ld) Tween Value: %.2f, Progress: %.4f, Eased Progress: %.4f\n", frame++, value, progress, eased_progress);
        }

        if(!Tw_TweenRunning(tween)) break;
    }

    printf("Tween complete!\n");
    Tw_FreeTweenId(tween);
    return EXIT_SUCCESS;
}
