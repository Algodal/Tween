//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tw-easing.h"

Tw_Float Tw_DefaultEase(Tw_Float x)
{
    return x;
}

Tw_Float Tw_EaseInSine(Tw_Float x)
{
    return 1.0f - cosf((x * TW_PI) / 2);
}

Tw_Float Tw_EaseOutSine(Tw_Float x)
{
    return sinf((x * TW_PI) / 2);
}

Tw_Float Tw_EaseInOutSize(Tw_Float x)
{
    return -(cosf(TW_PI * x) - 1.0f) / 2;
}

Tw_Float Tw_EaseInCubic(Tw_Float x)
{
    return x * x * x;
}

Tw_Float Tw_EaseOutCubic(Tw_Float x)
{
    return 1.0f - powf(1.0f - x, 3);
}

Tw_Float Tw_EaseInOutCubic(Tw_Float x)
{
    return x < 0.5f ? 4 * x * x * x : 1.0f - powf(-2 * x + 2.0f, 3) / 2;
}

Tw_Float Tw_EaseInQuint(Tw_Float x)
{
    return x * x * x * x * x;
}

Tw_Float Tw_EaseOutQuint(Tw_Float x)
{
    return 1.0f - powf(1.0f - x, 5);
}

Tw_Float Tw_EaseInOutQuint(Tw_Float x)
{
    return x < 0.5f ? 16 * x * x * x * x * x : 1.0f - powf(-2 * x + 2.0f, 5) / 2;
}

Tw_Float Tw_EaseInCirc(Tw_Float x)
{
    return 1.0f - sqrtf(1.0f - powf(x, 2));
}

Tw_Float Tw_EaseOutCirc(Tw_Float x)
{
    return sqrtf(1.0f - powf(x - 1.0f, 2));
}

Tw_Float Tw_EaseInOutCirc(Tw_Float x)
{
    return x < 0.5f
        ? (1.0f - sqrtf(1.0f - powf(2 * x, 2))) / 2
        : (sqrtf(1.0f - powf(-2 * x + 2.0f, 2)) + 1.0f) / 2;
}

Tw_Float Tw_EaseInElastic(Tw_Float x)
{
    const float c4 = (2 * TW_PI) / 3;

    return x == 0
        ? 0
        : x == 1
        ? 1
        : -powf(2, 10 * x - 10) * sinf((x * 10 - 10.75f) * c4);
}

Tw_Float Tw_EaseOutElastic(Tw_Float x)
{
    const float c4 = (2 * TW_PI) / 3;

    return x == 0
        ? 0
        : x == 1
        ? 1
        : powf(2, -10 * x) * sinf((x * 10 - 0.75f) * c4) + 1;
}

Tw_Float Tw_EaseInOutElastic(Tw_Float x)
{
    const float c5 = (2 * TW_PI) / 4.5;

    return x == 0
        ? 0
        : x == 1
        ? 1
        : x < 0.5
        ? -(powf(2, 20 * x - 10.0f) * sinf((20 * x - 11.125f) * c5)) / 2
        : (powf(2, -20 * x + 10.0f) * sinf((20 * x - 11.125f) * c5)) / 2 + 1.0f;
}

Tw_Float Tw_EaseInQuad(Tw_Float x)
{
    return x * x;
}

Tw_Float Tw_EaseOutQuad(Tw_Float x)
{
    return 1.0f - (1.0f - x) * (1.0f - x);
}

Tw_Float Tw_EaseInOutQuad(Tw_Float x)
{
    return x < 0.5f ? 2 * x * x : 1.0f - powf(-2 * x + 2.0f, 2) / 2.0f;
}

Tw_Float Tw_EaseInQuart(Tw_Float x)
{
    return x * x * x * x;
}

Tw_Float Tw_EaseOutQuart(Tw_Float x)
{
    return 1.0f - powf(1.0f - x, 4);
}

Tw_Float Tw_EaseInOutQuart(Tw_Float x)
{
    return x < 0.5f ? 8 * x * x * x * x : 1 - powf(-2 * x + 2.0f, 4) / 2;
}

Tw_Float Tw_EaseInExpo(Tw_Float x)
{
    return x == 0 ? 0 : powf(2, 10 * x - 10.0f);
}

Tw_Float Tw_EaseOutExpo(Tw_Float x)
{
    return x == 1 ? 1 : 1.0f - powf(2, -10 * x);
}

Tw_Float Tw_EaseInOutExpo(Tw_Float x)
{
    return x == 0
        ? 0
        : x == 1
        ? 1
        : x < 0.5f ? powf(2, 20 * x - 10.0f) / 2
        : (2 - powf(2, -20 * x + 10.0f)) / 2;
}

Tw_Float Tw_EaseInBack(Tw_Float x)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1;

    return c3 * x * x * x - c1 * x * x;
}

Tw_Float Tw_EaseOutBack(Tw_Float x)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1;

    return 1.0f + c3 * powf(x - 1.0f, 3) + c1 * powf(x - 1.0f, 2);
}

Tw_Float Tw_EaseInOutBack(Tw_Float x)
{
    const float c1 = 1.70158f;
    const float c2 = c1 * 1.525f;

    return x < 0.5
    ? (powf(2 * x, 2) * ((c2 + 1.0f) * 2 * x - c2)) / 2
    : (powf(2 * x - 2.0f, 2) * ((c2 + 1.0f) * (x * 2 - 2.0f) + c2) + 2.0f) / 2;
}

Tw_Float Tw_EaseInBounce(Tw_Float x)
{
    return 1.0f - Tw_EaseOutBounce(1.0f - x);
}

Tw_Float Tw_EaseOutBounce(Tw_Float x)
{
    const float n1 = 7.5625f;
    const float d1 = 2.75f;

    if (x < 1.0f / d1) {
        return n1 * x * x;
    } else if (x < 2.0f / d1) {
        return n1 * (x -= 1.5f / d1) * x + 0.75f;
    } else if (x < 2.5f / d1) {
        return n1 * (x -= 2.25f / d1) * x + 0.9375f;
    } else {
        return n1 * (x -= 2.625f / d1) * x + 0.984375f;
    }
}

Tw_Float Tw_EaseInOutBounce(Tw_Float x)
{
    return x < 0.5f
        ? (1.0f - Tw_EaseOutBounce(1.0f - 2 * x)) / 2
        : (1.0f + Tw_EaseOutBounce(2 * x - 1.0f)) / 2;
}









