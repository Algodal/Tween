//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_FUNCTIONS_H
#define TW_FUNCTIONS_H

#include <stdbool.h>
#include "tw_export.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEBUG
TW_EXPORT void Tw_Assert(bool cond, const char* msg);
#else
#define Tw_Assert(...)
#endif

#define TW_MIN(a,b) (((a)<(b))?(a):(b))
#define TW_MAX(a,b) (((a)>(b))?(a):(b))
#define TW_CLAMP(x, lower, upper) (TW_MIN((upper), TW_MAX((x), (lower))))
#define TW_DIRECTION(i, f) (((i)<=(f))?(+1):(-1))

#ifdef __cplusplus
}
#endif

#endif //TW_FUNCTIONS_H










