//  Copyright (C) 2023 Alrick Grandison, Algodal™  

#ifndef TW_THREAD_TYPES_H
#define TW_THREAD_TYPES_H

#include "tw-types.h"

#ifdef __cplusplus
extern "C" {
#endif


#define TW_DEFAULT_UPDATERATE 1.0f
#define TW_DEFAULT_DURATION 1.0f

typedef void (*Tw_ThreadFunction)(Tw_Float, Tw_Float); ///< Thread Generic Function


#ifdef __cplusplus
}
#endif

#endif //TW_THREAD_TYPES_H










