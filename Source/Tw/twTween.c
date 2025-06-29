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
    Tw_Bool loop;
    Tw_Bool flip;
    thrd_t thr;
};

struct TweenState {
    Tw_TweenPreset preset;
    Tw_EasingFunction easingfn;
    Tw_Bool loop;
    Tw_Bool flip;
    Tw_Float elapsed;
    Tw_Float progress;
    Tw_Float value;
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
        TweenJob job = variant->job;
        Tw_TweenPreset preset = job.preset;

        Tw_Float vector_distance = preset.to - preset.from;
        Tw_Tick stamp = job.ticker();
        
        do
        {
            Tw_Float elapsed = (job.ticker() - stamp) / job.tickPerSec;
            Tw_Float progress = TW_MAX(elapsed / preset.duration, 1.0f);
            Tw_Float eased_progress = job.easingfn(progress);
            Tw_Float value = (vector_distance * eased_progress) + preset.from;
            *job.property = value;

            if(elapsed < preset.delay) continue; else elapsed -= preset.delay;

            if(elapsed >= preset.duration)
            {
                if(job.loop)
                {
                    stamp = job.ticker();
                    
                    if(job.flip)
                    {
                        Tw_Float temp = preset.to;
                        preset.to = preset.from;
                        preset.from = temp;
                    }
                }
                else
                {
                    break;
                }
            }
        } while(true);

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

Tw_TweenId Tw_AllocateTweenJob(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_Property property, Tw_Ticker ticker, Tw_Tick tickPerSec, Tw_Bool loop, Tw_Bool flip)
{
    TweenVariant variant = {0};
    variant.type = TYPE_JOB;
    variant.job.preset;
    variant.job.property = property;
    variant.job.ticker = ((void*)ticker == (void*)clock || ticker == NULL) ? (Tw_Ticker)clock : ticker;
    variant.job.tickPerSec = ((void*)ticker == (void*)clock || ticker == NULL) ? CLOCKS_PER_SEC : (tickPerSec == 0) ? 1 : tickPerSec;
    variant.job.easingfn = (easingfn == NULL) ? TW_LINEAR : easingfn;
    variant.job.loop = loop;
    variant.job.flip = flip;
    
    if(property && preset.duration && preset.from != preset.to) {
        thrd_t thr;
        int op = thrd_create(&thr, SpawnCallback, (void*)&variant);
        if(op == thrd_success) thrd_detach(thr); else return 0;

        variant.job.thr = thr;
        TweenVariant* allocContext = malloc(sizeof(TweenVariant));
        *allocContext = variant;


        return (Tw_TweenId)allocContext;
    }

    TW_LOG(property == NULL, "Tw: Property can not be NULL");
    TW_LOG(preset.duration == 0, "Tw: Duration can not be 0");
    TW_LOG(preset.from == preset.to, "Tw: To and From can not be the same");

    return 0;
}

Tw_Bool Tw_RunJob(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_Property property, Tw_Ticker ticker, Tw_Tick tickPerSec)
{
    TweenVariant variant = {0};
    variant.type = TYPE_JOB;
    variant.job.preset;
    variant.job.property = property;
    variant.job.ticker = ((void*)ticker == (void*)clock || ticker == NULL) ? (Tw_Ticker)clock : ticker;
    variant.job.tickPerSec = ((void*)ticker == (void*)clock || ticker == NULL) ? CLOCKS_PER_SEC : (tickPerSec == 0) ? 1 : tickPerSec;
    variant.job.easingfn = (easingfn == NULL) ? TW_LINEAR : easingfn;
    
    if(property && preset.duration && preset.from != preset.to) {
        thrd_t thr;
        int op = thrd_create(&thr, SpawnCallback, (void*)&variant);
        if(op == thrd_success) thrd_detach(thr); else return false;

        return true;
    }

    TW_LOG(property == NULL, "Tw: Property can not be NULL");
    TW_LOG(preset.duration == 0, "Tw: Duration can not be 0");
    TW_LOG(preset.from == preset.to, "Tw: To and From can not be the same");

    return false;
}

// Loops

Tw_TweenId Tw_AllocateTweenState(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_Bool loop, Tw_Bool flip)
{
    if(preset.duration && preset.from != preset.to)
    {
        TweenVariant* variant = malloc(sizeof(TweenVariant));
        memset(variant, 0, sizeof(TweenVariant));
        variant->type = TYPE_STATE;    
        variant->state.preset = preset;
        variant->state.easingfn = (easingfn == NULL) ? TW_LINEAR : easingfn;
        variant->state.loop = loop;
        variant->state.flip = flip;
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
            Tw_Float progress = TW_MAX(variant->state.elapsed / preset.duration, 1.0f);
            Tw_Float eased_progress = variant->state.easingfn(progress);
            variant->state.value = (vector_distance * eased_progress) + preset.from;

            Tw_Float elapsed = variant->state.elapsed;
            if(elapsed >= preset.delay)
            {
                elapsed -= preset.delay;
                
                if(elapsed >= preset.duration)
                {
                    if(variant->state.loop)
                    {
                        variant->state.elapsed = 0;
                        
                        if(variant->state.flip)
                        {
                            Tw_Float temp = variant->state.preset.to;
                            variant->state.preset.to = variant->state.preset.from;
                            variant->state.preset.from = temp;
                        }
                    }
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

Tw_Bool Tw_TweenStateIncomplete(Tw_TweenId id)
{
    if(id)
    {
        TweenVariant* variant = (TweenVariant*)id;
        if(variant->type == TYPE_STATE) return variant->state.elapsed < (variant->state.preset.duration + variant->state.preset.delay);
    }
    return 0;
}

void Tw_FreeTweenId(Tw_TweenId id)
{
    if(id) free((void*)id);
}
