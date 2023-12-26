//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_INSTANCE_H
#define TW_INSTANCE_H

#include "tw-types.h"

#ifdef __cplusplus
extern "C" {
#endif

Tw_Instance* Tw_CreateInstance(
    Tw_Float           initial,
    Tw_Float           final,
    Tw_Float           duration,
    Tw_StepGetter      step_getter,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater
);

Tw_Float Tw_GetValue(Tw_Instance* i);
void Tw_Update(Tw_Instance* i);
Tw_Bool Tw_IsDone(Tw_Instance* i);
void Tw_Reset(Tw_Instance* i);
void Tw_Flip(Tw_Instance* i);


Tw_Float Tw_DefaultStepGetter();
Tw_Float Tw_DefaultEasingFunction(Tw_Float x);

#define TW_DEFAULT_STEP_GETTER Tw_DefaultStepGetter
#define TW_DEFAULT_EASING_FUNCTION Tw_DefaultEasingFunction


#ifdef __cplusplus
}
#endif

#endif //TW_INSTANCE_H










