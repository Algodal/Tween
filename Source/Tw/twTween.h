#pragma once

#include "twTypes.h"
#include "twEasing.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Tw_TweenPreset Tw_TweenPreset;
typedef long long Tw_TweenId;
typedef enum Tw_ThreadMethod Tw_ThreadMethod;
typedef enum Tw_Loop Tw_Loop;

enum Tw_Loop {
    TW_FOREVER = -8,
    TW_NONE = 0, //< No Loop
    TW_ONCE //< Any number greater than 0 will loop that exact number of times.
};

struct Tw_TweenPreset {
    Tw_Float from;
    Tw_Float to;
    Tw_Float duration;
    Tw_Float delay;
    Tw_Loop loop;
    Tw_Bool flip;
};


//job
TW_EXPORT Tw_TweenId Tw_AllocateTweenJob(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_Property property, Tw_Ticker ticker, Tw_Tick tickPerSec);
TW_EXPORT Tw_Bool Tw_RunTweenJob(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_Property property, Tw_Ticker ticker, Tw_Tick tickPerSec);

//state
TW_EXPORT Tw_TweenId Tw_AllocateTweenState(Tw_TweenPreset preset, Tw_EasingFunction easingfn);
TW_EXPORT void Tw_UpdateTweenState(Tw_TweenId id, Tw_Float delta);
TW_EXPORT Tw_Float Tw_GetTweenStateValue(Tw_TweenId id);
TW_EXPORT Tw_Float Tw_GetTweenStateProgress(Tw_TweenId id);

//common
TW_EXPORT void Tw_FreeTweenId(Tw_TweenId id);
TW_EXPORT Tw_Bool Tw_TweenRunning(Tw_TweenId id);
TW_EXPORT void Tw_TweenEndLoop(Tw_TweenId id);

//utility
TW_EXPORT Tw_TweenPreset Tw_InitTween(Tw_Float from, Tw_Float to, Tw_Float duration, Tw_Float delay);


#ifdef __cplusplus
}
#endif