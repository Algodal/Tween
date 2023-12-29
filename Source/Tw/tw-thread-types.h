//  Copyright (C) 2023 Alrick Grandison, Algodal™  

#ifndef TW_THREAD_TYPES_H
#define TW_THREAD_TYPES_H

#include "tw-types.h"

#ifdef __cplusplus
extern "C" {
#endif


#define TW_DEFAULT_UPDATERATE 1.0f
#define TW_DEFAULT_DURATION 1.0f

typedef struct Tw_ThreadFunctionParam Tw_ThreadFunctionParam;
typedef enum Tw_ThreadFunctionRequest Tw_ThreadFunctionRequest;

struct Tw_ThreadFunctionParam
{
    Tw_Float total_time; ///< The total running time of the thread over all loops
    unsigned long loop_count; ///< The total number of loops
    Tw_Float time; ///< The current running time of the thread for this current loop
    unsigned long long update_count; ///< The current number of update for this current loop
    Tw_Float value; ///< The current value of the Tween during this current loop
    Tw_Float percent; ///< The percent is the input value into the Tween during this current loop
};

enum Tw_ThreadFunctionRequest
{
    TW_THREAD_FUNCTION_NOTHING = 0, ///< Does nothing
    TW_THREAD_FUNCTION_EXIT = -1 ///< Requests to exit the loop early.  This sets @ref Tw_IsThreadDone to true but @ref Tw_IsDone may still be false
};
/// @brief Generic Thread function
/// This function is called after @ref Tw_Update.
/// It provides updates about the thread and allows the user to request exiting the
/// thread early.
typedef Tw_ThreadFunctionRequest (*Tw_ThreadFunction)(Tw_ThreadFunctionParam);
typedef enum Tw_Loop Tw_Loop; ///< Specifies the type of loop the thread applies

enum Tw_Loop
{
    TW_LOOP_NONE = 0,
    TW_LOOP_RESET,
    TW_LOOP_FLIP
};

#ifdef __cplusplus
}
#endif

#endif //TW_THREAD_TYPES_H










