//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_THREAD_H
#define TW_THREAD_H

#include "tw_export.h"
#include "tw-thread-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Creates a Thread and assigns it to the Instance of the Tween.
///        One Tween Instance can have only one Thread at at anytime.
///        DO NOT - Create Multiple Threads for a Instance at the Same time.
///        The purpose of the Thread is the update the Tween automatically
///        without calling @ref Tw_Update manually in a loop.  In order
///        for the thread to know how to update the Tween, you will have
///        to provide it with the update rate and the duration.
///        The Thread begins running immediately after this function is called.
/// @param i Tween Instance
/// @param update_rate The update rate is the number of times @ref Tw_Update
///                    is to be called per second.  This can be any amount
///                    you chose.  The higher the value the more smooth
///                    the tweening will be but more processing power required so
///                    Use your descetion.  A recommend approach is to match the 
///                    frame rate of your game (if you are making a game) or other
///                    established frame rate such as 60, 30, 24 etc.
/// @param duration This how long in seconds you want the tweening to spread out.
///                 The Tween will last this long in time from inital value to final value.
/// @param function This is a generic function that you may optionally pass to the 
///                 Thread.  It is called after @ref Tw_Update and is passed the 
///                 current value of the Tween and the current time the Tween has
///                 been running.
/// @return 
TW_EXPORT bool Tw_CreateThread(
    Tw_Instance*      i, 
    Tw_Float          update_rate, 
    Tw_Float          duration,
    Tw_ThreadFunction function
);

/// @brief This function mirrors the platform thread function this library is built on.
///        See https://github.com/tinycthread/tinycthread @see thrd_join for details.
/// @param i  Tween Instance
/// @param res 
TW_EXPORT void Tw_JoinThread(Tw_Instance* i, Tw_Ptr res);

/// @brief This function mirrors the platform thread function this library is built on.
///        See https://github.com/tinycthread/tinycthread @see thrd_detach for details.
/// @param i  Tween Instance
TW_EXPORT void Tw_DetachThread(Tw_Instance* i);

/// @brief This function mirrors the platform thread function this library is built on.
///        See https://github.com/tinycthread/tinycthread @see thrd_t for details.
/// @param i  Tween Instance
TW_EXPORT Tw_Ptr Tw_GetPlatformThreadHandle(Tw_Instance* i);

/// @brief This function checks if the Thread is completed.  This is different from
///        @ref Tw_IsDone which checks if the Tween is completed.
///        The Tween will complete first, then the Thread that updates the Tween
///        will complete after.
/// @param i Tween Instance
TW_EXPORT Tw_Bool Tw_IsThreadDone(Tw_Instance* i);

/// @brief This is a convenience function.  It combines @ref Tw_CreateInstance
///        @ref Tw_CreateThread.  Unlike Tw_CreateInstance, it doesn't create
///        the instance on the heap but on the stack, therefore, it doesn't need
///        @def Tw_DestroyInstance to be called.  It's parameters are the same
///        in @ref Tw_CreateInstance and @ref Tw_CreateThread.
///        With this function, you get convenience at the sacrifice of more control.
///        You don't get a reference of the Instance, therefore you can not call
///        other useful functions like @ref Tw_IsDone, @ref Tw_GetValue, etc.
/// @param initial 
/// @param final 
/// @param easing_function 
/// @param property 
/// @param property_updater 
/// @param update_rate 
/// @param duration 
/// @param function 
/// @return True if the Tween was created successfully.
TW_EXPORT Tw_Bool Tw_Tween(
    Tw_Float           initial,
    Tw_Float           final,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater,
    Tw_Float           update_rate, 
    Tw_Float           duration,
    Tw_ThreadFunction  function
);

#ifdef __cplusplus
}
#endif

#endif //TW_THREAD_H










