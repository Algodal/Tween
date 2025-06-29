//  Copyright (C) 2023 Alrick Grandison, Algodal™  

#ifndef TW_TYPES_H
#define TW_TYPES_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef float Tw_Float;    ///< Float Type
typedef bool Tw_Bool;
typedef Tw_Float* restrict Tw_Property;
typedef long long Tw_Tick;

typedef Tw_Float (*Tw_EasingFunction) (Tw_Float); ///< Easing Function Type
typedef Tw_Tick (*Tw_Ticker)(void);


#ifdef __cplusplus
}
#endif

#endif //TW_TYPES_H










