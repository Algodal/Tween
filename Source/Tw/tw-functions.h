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


#ifdef __cplusplus
}
#endif

#endif //TW_FUNCTIONS_H










