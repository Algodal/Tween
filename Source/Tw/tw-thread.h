//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_THREAD_H
#define TW_THREAD_H

#include "tw_export.h"
#include "tw-thread-types.h"

#ifdef __cplusplus
extern "C" {
#endif


TW_EXPORT bool Tw_CreateThread(
    Tw_Instance*      i, 
    Tw_Float          update_rate, 
    Tw_Float          duration,
    Tw_ThreadFunction function
);
TW_EXPORT void Tw_JoinThread(Tw_Instance* i, Tw_Ptr res);
TW_EXPORT void Tw_DetachThread(Tw_Instance* i);
TW_EXPORT Tw_Ptr Tw_GetPlatformThreadHandle(Tw_Instance* i);
TW_EXPORT Tw_Bool Tw_IsThreadDone(Tw_Instance* i);
TW_EXPORT Tw_Bool Tw_Tween(
    Tw_Float           initial,
    Tw_Float           final,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater,
    Tw_Float           update_rate, 
    Tw_Float           duration,
    Tw_ThreadFunction  function
);

#ifdef __cplusplus
}
#endif

#endif //TW_THREAD_H










