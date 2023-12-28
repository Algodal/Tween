//Copyright (C) 2023 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tw-thread.h"
#include "tw-instance.h"
#include "tw-instance.inl"
#include "tw-thread.inl"
#include "tw-functions.inl"

typedef int (*Tw_ThreadCallback)(void*);
static int Tw_DefaultThreadCallback(void* arg);
#define Tw_ThreadDefaultCallback TW_DEFAULT_THREAD_CALLBACK

bool Tw_CreateThread(
    Tw_Instance*            i, 
    Tw_Float                update_rate, 
    Tw_Float                duration,
    Tw_ThreadFunction function
)
{
    TW_ASSERT_INSTANCE(i);
    i->thread.update_rate = update_rate;
    i->thread.duration = duration;
    i->thread.function = function;
    i->thread.done = false;
    int result = thrd_create(&i->thread.handle, Tw_DefaultThreadCallback, (void*)i);
    return result == thrd_success;
}

Tw_Ptr Tw_GetPlatformThreadHandle(Tw_Instance* i)
{
    TW_ASSERT_INSTANCE(i);
    TW_ASSERT_THREAD(i->thread);
    return (Tw_Ptr)i->thread.handle;
}

void Tw_JoinThread(Tw_Instance* i, Tw_Ptr res)
{
    thrd_join(i->thread.handle, (int*)res);
}

void Tw_DetachThread(Tw_Instance* i)
{
    thrd_detach(i->thread.handle);
}

static int Tw_DefaultThreadCallback(void* arg)
{
    Tw_Instance* i = (Tw_Instance*)arg;
    clock_t previous = clock(), current;
    float accumulate = 0, delta;
    const int direction = TW_DIRECTION(i->initial, i->final);
    const Tw_Float size = TW_SIZE(i->initial, i->final) * direction;
    const Tw_Float step_per_sec = size / i->thread.duration;
    const Tw_Float step_per_update = step_per_sec / i->thread.update_rate;
    const Tw_Float time_per_update = 1.0f / i->thread.update_rate;
    clock_t clockrate = time_per_update * CLOCKS_PER_SEC;
    
    clock_t log_start = previous;

    while(false == Tw_IsDone(i))
    {
        current = clock();
        if(current >= (previous + clockrate))
        {
            previous = current;
            Tw_Update(i, step_per_update);
            if(i->thread.function) 
                i->thread.function(
                    Tw_GetValue(i), 
                    (Tw_Float)(current - log_start) / CLOCKS_PER_SEC
            );
        }
        
    }

    if(i->thread.function) 
        i->thread.function(
            Tw_GetValue(i), 
            (Tw_Float)(current - log_start) / CLOCKS_PER_SEC
        );
    i->thread.done = true;
    return 0;
}

Tw_Bool Tw_Tween(
    Tw_Float           initial,
    Tw_Float           final,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater,
    Tw_Float           update_rate, 
    Tw_Float           duration,
    Tw_ThreadFunction  function
)
{
    Tw_Instance instance = {};
    Tw_InitializeInstance(
        &instance,
        initial,
        final,
        easing_function,
        property,
        property_updater
    );
    return Tw_CreateThread(
        &instance, update_rate, duration, function);
}








