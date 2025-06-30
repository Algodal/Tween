#include "twTween.h"
#include "twEasing.h"
#include "time.h" //for thread
#include <tinycthread.h>
#include "twUtils.inl"
#include <stdlib.h> //EXIT_SUCCESS
#include <math.h> //fabs
#include <stdio.h> //printf

// Common Thread Definitions

typedef struct TweenJob TweenJob;
typedef struct TweenState TweenState;
typedef struct TweenVariant TweenVariant;

enum {
    TYPE_STATE = 0,
    TYPE_JOB = 1
};

struct TweenJob {
    Tw_TweenPreset preset;
    Tw_EasingFunction easingfn;
    Tw_Property property;
    Tw_Ticker ticker;
    Tw_Tick tickPerSec;
    thrd_t thr;
    Tw_Bool running;
    int res;
    bool autofree;
};

struct TweenState {
    Tw_TweenPreset preset;
    Tw_EasingFunction easingfn;
    Tw_Float elapsed;
    Tw_Float value;
    Tw_Bool running;
};

struct TweenVariant {
    int type; //TYPE_STATE, TYPE_JOB
    union {
        TweenJob job;
        TweenState state;
    };
};

Tw_TweenPreset Tw_InitTween(Tw_Float from, Tw_Float to, Tw_Float duration, Tw_Float delay) {
    Tw_TweenPreset preset = {0};
    preset.from = from;
    preset.to = to;    
    preset.duration = duration;
    preset.delay = delay;
    return preset;
}

// Threads

static int SpawnCallback(void* arg)
{
    TweenVariant* variant = (TweenVariant*)arg;
    if(variant->type == TYPE_JOB)
    {
        TweenJob* job = &variant->job;
        Tw_TweenPreset preset = job->preset;

        Tw_Float vector_distance = preset.to - preset.from;
        Tw_Tick stamp = job->ticker();
        
        do
        {
            Tw_Float elapsed = (Tw_Float)((long double)(job->ticker() - stamp) / (long double)job->tickPerSec);
            if(elapsed < preset.delay) continue; 

            Tw_Float tween_elapsed = elapsed - preset.delay;
            Tw_Float progress = TW_MIN(tween_elapsed / preset.duration, 1.0f);
            Tw_Float eased_progress = job->easingfn(progress);
            Tw_Float value = (vector_distance * eased_progress) + preset.from;
            *job->property = value;

            
            

            if(tween_elapsed >= preset.duration)
            {
                if(preset.loop == TW_FOREVER || preset.loop > TW_NONE)
                {
                    stamp = job->ticker();
                    
                    if(preset.flip)
                    {
                        Tw_Float temp = preset.to;
                        preset.to = preset.from;
                        preset.from = temp;
                    }

                    if(preset.loop > TW_NONE) preset.loop --;
                }
                else
                {
                    break;
                }
            }
        } while(true);

        variant->job.running = false;
        if(variant->job.autofree)
        {
            free(variant);
        }
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

Tw_TweenId Tw_AllocateTweenJob(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_Property property, Tw_Ticker ticker, Tw_Tick tickPerSec)
{
    if(property && preset.duration && preset.from != preset.to) {
        TweenVariant* variant = malloc(sizeof(TweenVariant));
        if (!variant) return 0;
        memset(variant, 0, sizeof(TweenVariant));

        variant->type = TYPE_JOB;
        variant->job.preset = preset;
        variant->job.property = property;
        variant->job.ticker = ((void*)ticker == (void*)clock || ticker == NULL) ? (Tw_Ticker)clock : ticker;
        variant->job.tickPerSec = ((void*)ticker == (void*)clock || ticker == NULL) ? CLOCKS_PER_SEC : (tickPerSec == 0) ? 1 : tickPerSec;
        variant->job.easingfn = (easingfn == NULL) ? TW_LINEAR : easingfn;
        variant->job.running = true;

        int op = thrd_create(&variant->job.thr, SpawnCallback, (void*)variant);
        if(op == thrd_success) 
        {
            thrd_detach(variant->job.thr);

            return (Tw_TweenId)variant;
        } else
        {
            memset(variant, 0, sizeof(TweenVariant));
            free(variant);
        }

        

        return 0;
    }

    TW_LOG(property == NULL, "TW: Property can not be NULL");
    TW_LOG(preset.duration == 0, "TW: Duration can not be 0");
    TW_LOG(preset.from == preset.to, "TW: To and From can not be the same");

    return 0;
}

Tw_Bool Tw_RunTweenJob(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_Property property, Tw_Ticker ticker, Tw_Tick tickPerSec)
{
    if(property && preset.duration && preset.from != preset.to && preset.loop != TW_FOREVER) {
        TweenVariant* variant = malloc(sizeof(TweenVariant));
        if (!variant) return 0;
        memset(variant, 0, sizeof(TweenVariant));

        variant->type = TYPE_JOB;
        variant->job.preset = preset;
        variant->job.property = property;
        variant->job.ticker = ((void*)ticker == (void*)clock || ticker == NULL) ? (Tw_Ticker)clock : ticker;
        variant->job.tickPerSec = ((void*)ticker == (void*)clock || ticker == NULL) ? CLOCKS_PER_SEC : (tickPerSec == 0) ? 1 : tickPerSec;
        variant->job.easingfn = (easingfn == NULL) ? TW_LINEAR : easingfn;
        variant->job.autofree = true;
        variant->job.running = true;

        int op = thrd_create(&variant->job.thr, SpawnCallback, (void*)variant);
        if(op == thrd_success) 
        {
            thrd_detach(variant->job.thr);

            return true;
        } else
        {
            memset(variant, 0, sizeof(TweenVariant));
            free(variant);
        }
    }

    TW_LOG(preset.loop == TW_FOREVER, "TW: Run Job is not allowed to loop forever\n");
    TW_LOG(property == NULL, "TW: Property can not be NULL\n");
    TW_LOG(preset.duration == 0, "TW: Duration can not be 0\n");
    TW_LOG(preset.from == preset.to, "TW: To and From can not be the same\n");

    return false;
}

// Loops

Tw_TweenId Tw_AllocateTweenState(Tw_TweenPreset preset, Tw_EasingFunction easingfn)
{
    if(preset.duration && preset.from != preset.to)
    {
        TweenVariant* variant = malloc(sizeof(TweenVariant));
        memset(variant, 0, sizeof(TweenVariant));
        variant->type = TYPE_STATE;    
        variant->state.preset = preset;
        variant->state.easingfn = (easingfn == NULL) ? TW_LINEAR : easingfn;
        variant->state.running = true;
        return (Tw_TweenId) variant;
    }
    return 0;
}

void Tw_UpdateTweenState(Tw_TweenId id, Tw_Float delta)
{
    TweenVariant* variant = (TweenVariant*)id;
    if(variant->type == TYPE_STATE)
    {
        Tw_TweenPreset preset = variant->state.preset;
        Tw_Float vector_distance = preset.to - preset.from;
        
        if(true)
        {
            variant->state.elapsed += delta;
            Tw_Float progress = TW_MIN(variant->state.elapsed / preset.duration, 1.0f);
            Tw_Float eased_progress = variant->state.easingfn(progress);
            variant->state.value = (vector_distance * eased_progress) + preset.from;

            Tw_Float elapsed = variant->state.elapsed;
            if(elapsed < preset.delay) return;

            Tw_Float tween_elapsed = elapsed - preset.delay;

            if(tween_elapsed >= preset.duration)
            {
                if(preset.loop == TW_FOREVER || preset.loop > TW_NONE)
                {
                    variant->state.elapsed = 0;
                    
                    if(preset.flip)
                    {
                        Tw_Float temp = variant->state.preset.to;
                        variant->state.preset.to = variant->state.preset.from;
                        variant->state.preset.from = temp;
                    }

                    if(preset.loop > TW_NONE) preset.loop --;
                } else {
                     variant->state.running = false;
                }
            }
        }
    }
}

Tw_Float Tw_GetTweenStateValue(Tw_TweenId id)
{
    if(id)
    {
        TweenVariant* variant = (TweenVariant*)id;
        if(variant->type == TYPE_STATE) return variant->state.value;
    }
    return 0;
}

Tw_Float Tw_GetTweenStateProgress(Tw_TweenId id)
{
    if(id)
    {
        TweenVariant* variant = (TweenVariant*)id;
        if(variant->type == TYPE_STATE) return TW_MIN(variant->state.elapsed / variant->state.preset.duration, 1.0f);
    }
    return 0;
}

// Common

Tw_Bool Tw_TweenRunning(Tw_TweenId id)
{
    TW_LOG(id == 0, "TW: Invalid ID\n");

    TweenVariant* variant = (TweenVariant*)id;
    if(variant && variant->type == TYPE_STATE)
    {
        return variant->state.running;
    } else
    if(variant && variant->type == TYPE_JOB)
    {
        return variant->job.running;
    }

    return false;
}

void Tw_FreeTweenId(Tw_TweenId id)
{
    TW_LOG(id == 0, "TW: Invalid ID\n");

    if(id) {
        TweenVariant* variant = (TweenVariant*)id;
        if(variant && variant->type == TYPE_STATE)
        {
            Tw_TweenEndLoop(id);
            variant->state.running = false;
        } else
        if(variant && variant->type == TYPE_JOB)
        {
            Tw_TweenEndLoop(id);
            while(Tw_TweenRunning(id)); //wait until thread returns
        }

        free((void*)id);
    }
}

void Tw_TweenEndLoop(Tw_TweenId id)
{
    TW_LOG(id == 0, "TW: Invalid ID\n");

    TweenVariant* variant = (TweenVariant*)id;
    Tw_TweenPreset* preset = NULL;

    if(variant && variant->type == TYPE_STATE)
    {
        preset = &variant->state.preset;
    } else
    if(variant && variant->type == TYPE_JOB)
    {
        preset = &variant->job.preset;
    }

    if(preset)
    {
        preset->loop = TW_NONE;
    }
}
