//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tw-instance.h"
#include "tw-functions.h"
#include "tw-easing.h"

#include "tw-functions.inl"
#include "tw-instance.inl"

Tw_Instance* Tw_CreateInstance(
    Tw_Float           initial,
    Tw_Float           final,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater
)
{
    Tw_Instance* i = malloc(sizeof(Tw_Instance));
    memset(i, 0, sizeof(Tw_Instance));
    return Tw_InitializeInstance(i, initial, final, easing_function, property, property_updater);
}

Tw_Instance* Tw_InitializeInstance(
    Tw_Instance* i,
    Tw_Float           initial,
    Tw_Float           final,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater
)
{
    Tw_Assert(NULL!=i, "Failed to allocate Instance");
    i->initial = initial;
    i->final = final;
    i->easing_function = easing_function ? easing_function : Tw_DefaultEasingFunction;
    i->property = property;
    i->property_updater = property_updater;
    TW_ASSERT_INSTANCE(i);
    return i;
}

Tw_Instance* Tw_CopyInstance(Tw_Instance* i)
{
    Tw_Instance* new_i = malloc(sizeof(Tw_Instance));
    memcpy(new_i, i, sizeof(Tw_Instance));
    return new_i;
}

void Tw_DestroyInstance(Tw_Instance* i)
{
    if(i)
    {
        free(i);
    }
}

Tw_Float Tw_GetValue(Tw_Instance* i)
{
    const int direction = TW_DIRECTION(i->initial, i->final);
    const Tw_Float size = TW_SIZE(i->initial, i->final) * direction;
    Tw_Float percent = TW_CLAMP(i->current / size, 0, 1);
    Tw_Float easing = i->easing_function(percent);
	return i->initial + ((size * easing) * direction);
}

void Tw_Update(Tw_Instance* i, Tw_Float step)
{
    if(false == Tw_IsDone(i)) i->current += step;
    i->property_updater(i->property, Tw_GetValue(i));
}

Tw_Bool Tw_IsDone(Tw_Instance* i)
{
    const int direction = TW_DIRECTION(i->initial, i->final);
    const Tw_Float size = TW_SIZE(i->initial, i->final) * direction;
    return i->current >= size;
}

void Tw_Reset(Tw_Instance* i)
{
    i->current = 0;
}

void Tw_Flip(Tw_Instance* i)
{
    Tw_Float temp = i->initial;
	i->initial = i->final;
	i->final = temp;
}

void Tw_FloatUpdater(Tw_Ptr property, Tw_Float value)
{
    float* float_property = (float*)property;
    float_property[0] = (float)value;
}










