//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_THREAD_H
#define TW_THREAD_H

#include "tw_export.h"
#include "tw-thread-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Creates a Thread and assigns it to the Instance of the Tween.
///        A thread is expected to be created once per instance. 
///        Multiple thread behavior is undefined.
///        The purpose of the Thread is the update the Tween automatically
///        without by calling @ref Tw_Update for you.  In order
///        for the thread to know how to update the Tween, you will have
///        to provide it with the update rate and the duration.
///        @attention The Thread begins running immediately after this function is called.
/// @param i Tween Instance
/// @param update_rate The update rate is the number of times @ref Tw_Update
///                    is to be called per second.  This can be any amount
///                    you choose.  The higher the value the more smooth
///                    the tweening will be but more processing power required so
///                    use your descretion.  A reccommended approach is to match the 
///                    frame rate of your game (if you are making a game) or other
///                    established frame rate such as 60, 30, 24 etc.
/// @param duration This how long in seconds you want the tweening to spread out.
///                 The Tween will last this long in time from inital value to final value.
/// @param function This optional function provides feedback on the thread process via @ref Tw_ThreadFunctionParam.
///                 You can also post requests to the thread as well via @ref Tw_ThreadFunctionRequest
/// @param loop     This optional value indicates if you want the thread to loop.
///                 Looping occurs when the Tween is completed.  The thread will reset
///                 the Tween and run it again.  A thread that has loop set will never stop.
///                 In order to stop such a thread you will have to use @ref Tw_SetThreadLoop
///                 and set the value to @ref TW_LOOP_NONE.
/// @return True if the thread was created successfully.
TW_EXPORT bool Tw_CreateThread(
    Tw_Instance*      i, 
    Tw_Float          update_rate, 
    Tw_Float          duration,
    Tw_ThreadFunction function,
    Tw_Loop           loop
);

/// @brief This function mirrors the platform thread function this library is built on.
///        See https://github.com/tinycthread/tinycthread thrd_join for details.
/// @param i  Tween Instance
/// @param res 
TW_EXPORT void Tw_JoinThread(Tw_Instance* i, Tw_Ptr res);

/// @brief This function mirrors the platform thread function this library is built on.
///        See https://github.com/tinycthread/tinycthread thrd_detach for details.
/// @param i  Tween Instance
TW_EXPORT void Tw_DetachThread(Tw_Instance* i);

/// @brief This function mirrors the platform thread function this library is built on.
///        See https://github.com/tinycthread/tinycthread thrd_exit for details.
TW_EXPORT void Tw_ThreadExit(int res);

/// @brief This function mirrors the platform thread function this library is built on.
///        See https://github.com/tinycthread/tinycthread thrd_t for details.
/// @param i  Tween Instance
TW_EXPORT Tw_Ptr Tw_GetPlatformThreadHandle(Tw_Instance* i);

/// @brief This function checks if the Thread is completed.  This is different from
///        @ref Tw_IsDone which checks if the Tween is completed.
///        The Tween will complete first, then the Thread that updates the Tween
///        will complete after.
/// @param i Tween Instance
TW_EXPORT Tw_Bool Tw_IsThreadDone(Tw_Instance* i);

/// @brief This is a convenience function.  It combines @ref and Tw_CreateInstance
///        @ref Tw_CreateThread into a single call.  
///        It's parameters are the same as in @ref Tw_CreateInstance and @ref Tw_CreateThread.
///        @param ret_instance An optional parameter to return the instance created
///                            for the tween.  If it is NULL, then the instance is
///                            not returned and the function will handle freeing the 
///                            instance itself.
TW_EXPORT Tw_Bool Tw_CreateTween(
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
);

#ifdef __cplusplus
}
#endif

#endif //TW_THREAD_H










