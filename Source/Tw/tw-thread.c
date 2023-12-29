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
    Tw_Instance*      i, 
    Tw_Float          update_rate, 
    Tw_Float          duration,
    Tw_ThreadFunction function,
    Tw_Loop           loop
)
{
    TW_ASSERT_INSTANCE(i);
    i->thread.update_rate = update_rate;
    i->thread.duration = duration;
    i->thread.function = function;
    i->thread.loop     = loop;
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

void Tw_ThreadExit(int res)
{
    thrd_exit(res);
}

/// @brief Built-in Thread callback function
/// @param arg passed Tween Instance
static int Tw_DefaultThreadCallback(void* arg)
{
    Tw_Instance* i = (Tw_Instance*)arg;
    clock_t previous = clock(), current = previous, log_start;
    float accumulate = 0, delta;
    const int direction = TW_DIRECTION(i->initial, i->final);
    const Tw_Float size = TW_SIZE(i->initial, i->final) * direction;
    const Tw_Float step_per_sec = size / i->thread.duration;
    const Tw_Float step_per_update = step_per_sec / i->thread.update_rate;
    const Tw_Float time_per_update = 1.0f / i->thread.update_rate;
    const clock_t clockrate = time_per_update * CLOCKS_PER_SEC;
    const clock_t log_initial = previous;

    Tw_ThreadFunctionParam param = {};
    
    BEGIN_LOOP:
    i->thread.done = false;
    log_start = previous;

    param.loop_count ++;

    if(i->thread.function) 
    {
        param.total_time = (Tw_Float)(current - log_initial) / CLOCKS_PER_SEC;
        param.time = (Tw_Float)(current - log_start) / CLOCKS_PER_SEC;
        param.percent = i->current / size;
        param.value = Tw_GetValue(i);
        Tw_ThreadFunctionRequest req = i->thread.function(param);
        if(req == TW_THREAD_FUNCTION_EXIT)
        {
            i->thread.done = true;
            return 0;
        }
    }

    while(false == Tw_IsDone(i))
    {
        current = clock();
        if(current >= (previous + clockrate))
        {
            previous = current;
            Tw_Update(i, step_per_update);
            if(i->thread.function) 
            {
                param.total_time = (Tw_Float)(current - log_initial) / CLOCKS_PER_SEC;
                param.time = (Tw_Float)(current - log_start) / CLOCKS_PER_SEC;
                param.percent = i->current / size;
                param.value = Tw_GetValue(i);
                param.update_count ++; //Count the number of Tw_Update
                Tw_ThreadFunctionRequest req = i->thread.function(param);
                if(req == TW_THREAD_FUNCTION_EXIT)
                {
                    i->thread.done = true;
                    return 0;
                }
            }
        }
        
    }

    //Signal thread completed
    i->thread.done = true;

    if(i->thread.loop == TW_LOOP_RESET)
    {
        Tw_Reset(i);
        goto BEGIN_LOOP;
    }

    if(i->thread.loop == TW_LOOP_FLIP)
    {
        Tw_Reset(i);
        Tw_Flip(i);
        goto BEGIN_LOOP;
    }

    //Exit thread
    return 0;
}

Tw_Bool Tw_IsThreadDone(Tw_Instance* i)
{
    return i->thread.done;
}

/// @brief Gets the assigned loop value of the Thread.
///        Even if a thread is done - @ref Tw_IsDone returns true
///        If thread loop is RESET or FLIP it will continue running
///        To stop the thread, you will have to set the loop as NONE via
///        @ref Tw_SetThreadLoop
/// @param i Tween Instance
/// @return Loop Type
Tw_Loop Tw_GetThreadLoop(Tw_Instance* i)
{
    return i->thread.loop;
}

/// @brief Set the loop type of a Tween Instance Thread
/// @param i Tween Instance
/// @param loop Loop Type
void Tw_SetThreadLoop(Tw_Instance* i, Tw_Loop loop)
{
    i->thread.loop = loop;
}

Tw_Bool Tw_CreateTween(
    Tw_Instance**      ret_instance,  
    Tw_Float           initial,
    Tw_Float           final,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater,
    Tw_Float           update_rate, 
    Tw_Float           duration,
    Tw_ThreadFunction  function,
    Tw_Loop            loop
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

    Tw_Instance* i = &instance;

    if(ret_instance)
    {
        ret_instance[0] = Tw_CopyInstance(&instance);
        i = ret_instance[0];
    }
    return Tw_CreateThread(
        i, update_rate, duration, function, loop);
}








