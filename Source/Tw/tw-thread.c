//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tw-thread.h"
#include "tw-instance.h"
#include "tw-instance.inl"
#include "tw-thread.inl"

typedef int (*Tw_ThreadCallback)(void*);
static int Tw_DefaultThreadCallback(void* arg);
#define Tw_ThreadDefaultCallback TW_DEFAULT_THREAD_CALLBACK

bool Tw_CreateThread(Tw_Instance* i, Tw_Float steprate)
{
    TW_ASSERT_INSTANCE(i);
    Tw_Thread* thread = malloc(sizeof(Tw_Thread));
    memset(thread, 0, sizeof(Tw_Thread));
    i->thread = thread;
    Tw_Assert(NULL!=i->thread, "Failed to allocate Thread");
    i->thread->steprate = steprate>0?steprate:TW_DEFAULT_STEPRATE;
    int result = thrd_create(&thread->handle, Tw_DefaultThreadCallback, (void*)i);
    return result == thrd_success;
}

Tw_Ptr Tw_GetPlatformThreadHandle(Tw_Instance* i)
{
    TW_ASSERT_INSTANCE(i);
    TW_ASSERT_THREAD(i->thread);
    return (Tw_Ptr)i->thread->handle;
}

static int Tw_DefaultThreadCallback(void* arg)
{
    Tw_Instance* i = (Tw_Instance*)arg;
    clock_t previous = clock(), current;
    float accumulate = 0, delta;
    const float timerate = 1.0f / i->thread->steprate;

    while(false == Tw_IsDone(i))
    {
        current = clock();
        if(current > previous)
        {
            delta = (float)(current - previous) / CLOCKS_PER_SEC;
            previous = current;
            accumulate += delta;
        }
        if(accumulate>=timerate)
        {
            accumulate-=timerate;
            Tw_Update(i, timerate);
        }
    }
    return 0;
}

void Tw_DestroyThread(Tw_Instance* i)
{
    free(i->thread);
}










