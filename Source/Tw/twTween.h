#pragma once

#include "twTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Tw_TweenPreset Tw_TweenPreset;
typedef long long Tw_TweenId;


struct Tw_TweenPreset {
    Tw_Float from;
    Tw_Float to;
    Tw_Float duration;
    Tw_Float delay;
};

#ifdef __cplusplus
}
#endif