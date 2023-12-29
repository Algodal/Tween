//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_THREAD_INL
#define TW_THREAD_INL

#include "../tinycthread/tinycthread.h"
#include "tw-thread-types.h"
#include "tw-functions.h"

#ifdef DEBUG
#define TW_ASSERT_THREAD(t) \
    Tw_Assert(NULL!=(Tw_Ptr)t.handle, "Platform Thread Handle can not be NULL"); \
    (void)0
#else
#define TW_ASSERT_THREAD(t)
#endif

typedef struct Tw_Thread     Tw_Thread;

/// @brief Thread Data for the Instance
struct Tw_Thread
{
    thrd_t            handle; ///<Platform Thread Handle
    Tw_Float          update_rate; ///< The number of times @ref Tw_Update is called per second.
    Tw_Float          duration; ///< The length of time in seconds it takes for the Tween to go from it's inital value to it's final value.
    Tw_ThreadFunction function; ///< A generic function that may be passed to the thread
    Tw_Loop           loop;///< The loop action of the thread
    Tw_Bool           done; ///< signals when the thread is completed
};


#endif//TW_THREAD_INL





