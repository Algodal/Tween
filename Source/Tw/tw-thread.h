//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_THREAD_H
#define TW_THREAD_H

#include "tw_export.h"
#include "tw-thread-types.h"

#ifdef __cplusplus
extern "C" {
#endif


TW_EXPORT bool Tw_CreateThread(Tw_Instance* i, Tw_Float steprate);
TW_EXPORT Tw_Ptr Tw_GetPlatformThreadHandle(Tw_Instance* i);


#ifdef __cplusplus
}
#endif

#endif //TW_THREAD_H










