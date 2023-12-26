//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tw-instance.h"
#include "tw-functions.h"

struct Tw_Instance
{
    Tw_Float           initial;
    Tw_Float           final;
    Tw_Float           duration;
    Tw_Float           current;
    Tw_Ptr             property;
    Tw_PropertyUpdater property_updater;
    Tw_EasingFunction  easing_function;
    Tw_StepGetter      step_getter;
};

#define TW_ASSERT_INSTANCE(i) \
    Tw_Assert(i->property!=NULL, "Property can not be NULL"); \
    Tw_Assert(i!=property_updater, "Property Updater can not be NULL"); \

Tw_Instance* Tw_CreateInstance(
    Tw_Float           initial,
    Tw_Float           final,
    Tw_Float           duration,
    Tw_StepGetter      step_getter,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater
)
{
    Tw_Instance* i = malloc(sizeof(Tw_Instance));
    memset(i, 0, sizeof(Tw_Instance));
    Tw_Assert(i!=NULL, "Failed to allocate Instance");
    i->initial = initial;
    i->final = final;
    i->duration = duration;
    i->step_getter = step_getter ? step_getter : Tw_DefaultStepGetter;
    i->easing_function = easing_function ? easing_function : Tw_DefaultEasingFunction;
    i->property = property;
    i->property_updater = property_updater;
    TW_ASSERT_INSTANCE(i);
    return i;
}

Tw_Float Tw_GetValue(Tw_Instance* i)
{
    float percent = TW_CLAMP(i->current / i->duration, 0, 1);
	float size = i->final - i->initial;
	return i->initial + ((size * percent) * TW_DIRECTION(i->initial, i->final));
}

void Tw_Update(Tw_Instance* i)
{
    
    i->property_updater(i->property, Tw_GetValue(i));
    if(false == Tw_IsDone(i)) i->current += i->step_getter();
}

Tw_Bool Tw_IsDone(Tw_Instance* i)
{
    return i->current >= i->duration;
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

Tw_Float Tw_DefaultStepGetter()
{
    return 1.0f / 60;
}

Tw_Float Tw_DefaultEasingFunction(Tw_Float x)
{
    return x;
}








