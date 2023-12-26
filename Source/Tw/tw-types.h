//  Copyright (C) 2023 Alrick Grandison, Algodal™  

#ifndef TW_TYPES_H
#define TW_TYPES_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef float              Tw_Float;    ///< Float Type
typedef bool               Tw_Bool;     ///< Bool Type
typedef void*              Tw_Ptr;      ///< Generic Pointer Type
typedef struct Tw_Instance Tw_Instance; ///< Core Tween Object Type

typedef void     (*Tw_PropertyUpdater)(Tw_Ptr, Tw_Float);
typedef Tw_Float (*Tw_EasingFunction) (Tw_Float);
typedef Tw_Float (*Tw_StepGetter)     (void);


#ifdef __cplusplus
}
#endif

#endif //TW_TYPES_H










