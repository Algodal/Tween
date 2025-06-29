//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_EASING_H
#define TW_EASING_H

#include "twExport.h"
#include "twTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

///@file Built-in Easing Functions

#define TW_PI 3.141592f ///< Tween Library PI Value

TW_EXPORT Tw_Float Tw_Linear(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInSine(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutSine(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutSine(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInCubic(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutCubic(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutCubic(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInQuint(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutQuint(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutQuint(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInCirc(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutCirc(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutCirc(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInElastic(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutElastic(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutElastic(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInQuad(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutQuad(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutQuad(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInQuart(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutQuart(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutQuart(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInExpo(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutExpo(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutExpo(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInBack(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutBack(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutBack(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInBounce(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseOutBounce(Tw_Float x);
TW_EXPORT Tw_Float Tw_EaseInOutBounce(Tw_Float x);

#define TW_LINEAR Tw_Linear
#define TW_EASE_IN_SINE Tw_EaseInSine
#define TW_EASE_OUT_SINE Tw_EaseOutSine
#define TW_EASE_IN_OUT_SINE Tw_EaseInOutSine
#define TW_EASE_IN_CUBIC Tw_EaseInCubic
#define TW_EASE_OUT_CUBIC Tw_EaseOutCubic
#define TW_EASE_IN_OUT_CUBIC Tw_EaseInOutCubic
#define TW_EASE_IN_QUINT Tw_EaseInQuint
#define TW_EASE_OUT_QUINT Tw_EaseOutQuint
#define TW_EASE_IN_OUT_QUINT Tw_EaseInOutQuint
#define TW_EASE_IN_CIRC Tw_EaseInCirc
#define TW_EASE_OUT_CIRC Tw_EaseOutCirc
#define TW_EASE_IN_OUT_CIRC Tw_EaseInOutCirc
#define TW_EASE_IN_ELASTIC Tw_EaseInElastic
#define TW_EASE_OUT_ELASTIC Tw_EaseOutElastic
#define TW_EASE_IN_OUT_ELASTIC Tw_EaseInOutElastic
#define TW_EASE_IN_QUAD Tw_EaseInQuad
#define TW_EASE_OUT_QUAD Tw_EaseOutQuad
#define TW_EASE_IN_OUT_QUAD Tw_EaseInOutQuad
#define TW_EASE_IN_QUART Tw_EaseInQuart
#define TW_EASE_OUT_QUART Tw_EaseOutQuart
#define TW_EASE_IN_OUT_QUART Tw_EaseInOutQuart
#define TW_EASE_IN_EXPO Tw_EaseInExpo
#define TW_EASE_OUT_EXPO Tw_EaseOutExpo
#define TW_EASE_IN_OUT_EXPO Tw_EaseInOutExpo
#define TW_EASE_IN_BACK Tw_EaseInBack
#define TW_EASE_OUT_BACK Tw_EaseOutBack
#define TW_EASE_IN_OUT_BACK Tw_EaseInOutBack
#define TW_EASE_IN_BOUNCE Tw_EaseInBounce
#define TW_EASE_OUT_BOUNCE Tw_EaseOutBounce
#define TW_EASE_IN_OUT_BOUNCE Tw_EaseInOutBounce


#ifdef __cplusplus
}
#endif

#endif //TW_EASING_H










