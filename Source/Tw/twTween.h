#pragma once

#include "twTypes.h"
#include "twEasing.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Tw_TweenPreset Tw_TweenPreset;
typedef long long Tw_TweenId;
typedef enum Tw_ThreadMethod Tw_ThreadMethod;


struct Tw_TweenPreset {
    Tw_Float from;
    Tw_Float to;
    Tw_Float duration;
    Tw_Float delay;
};

enum Tw_ThreadMethod {
    TW_DETACH,
    TW_JOIN,
    TW_IGNORE
};

TW_EXPORT Tw_TweenPreset Tw_InitTween(Tw_Float from, Tw_Float to, Tw_Float duration, Tw_Float delay);
TW_EXPORT Tw_TweenId Tw_AllocateTweenJob(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_Bool loop, Tw_Bool flip, Tw_ThreadMethod method, Tw_Property property, Tw_Ticker ticker, Tw_Tick tickPerSec);
TW_EXPORT Tw_Bool Tw_RunTweenJob(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_ThreadMethod method, Tw_Property property, Tw_Ticker ticker, Tw_Tick tickPerSec);
TW_EXPORT Tw_TweenId Tw_AllocateTweenState(Tw_TweenPreset preset, Tw_EasingFunction easingfn, Tw_Bool loop, Tw_Bool flip);
TW_EXPORT void Tw_UpdateTweenState(Tw_TweenId id, Tw_Float delta);
TW_EXPORT Tw_Float Tw_GetTweenStateValue(Tw_TweenId id);
TW_EXPORT Tw_Bool Tw_TweenStateIncomplete(Tw_TweenId id);
TW_EXPORT void Tw_FreeTweenId(Tw_TweenId id);
TW_EXPORT Tw_Bool Tw_TweenJobRunning(Tw_TweenId id);
TW_EXPORT void Tw_TweenJobJoin(Tw_TweenId id);


#ifdef __cplusplus
}
#endif