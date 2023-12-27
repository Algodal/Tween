//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_THREAD_INL
#define TW_THREAD_INL

#include "../tinycthread/tinycthread.h"
#include "tw-thread-types.h"
#include "tw-functions.h"

#ifdef DEBUG
#define TW_ASSERT_THREAD(t) \
    Tw_Assert(NULL!=t, "Thread can not be null"); \
    Tw_Assert(NULL!=(Tw_Ptr)t->handle, "Platform Thread Handle can not be NULL"); \
    (void)0
#else
#define TW_ASSERT_THREAD(t)
#endif

typedef struct Tw_Thread     Tw_Thread;

struct Tw_Thread
{
    thrd_t   handle;
    Tw_Float steprate;
};

void Tw_DestroyThread(Tw_Instance* i);



#endif//TW_THREAD_INL





