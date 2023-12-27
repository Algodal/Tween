//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_INSTANCE_H
#define TW_INSTANCE_H

#include "tw_export.h"
#include "tw-types.h"

#ifdef __cplusplus
extern "C" {
#endif

TW_EXPORT Tw_Instance* Tw_CreateInstance(
    Tw_Float           initial,
    Tw_Float           final,
    Tw_Float           duration,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater
);
TW_EXPORT void Tw_DestroyInstance(Tw_Instance* i);

TW_EXPORT Tw_Float Tw_GetValue(Tw_Instance* i);
TW_EXPORT void Tw_Update(Tw_Instance* i, Tw_Float step);
TW_EXPORT Tw_Bool Tw_IsDone(Tw_Instance* i);
TW_EXPORT void Tw_Reset(Tw_Instance* i);
TW_EXPORT void Tw_Flip(Tw_Instance* i);







#ifdef __cplusplus
}
#endif

#endif //TW_INSTANCE_H










