//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_INSTANCE_H
#define TW_INSTANCE_H

#include "tw_export.h"
#include "tw-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief The core of a Tween.  Each instance represent a single Tween.
///        A tween can not be made without an instance.  This is the first
///        function called when creating a tween.
/// @param initial The initial value of the Tween.  This maps to 0.
/// @param final   The final value of the Tween. This maps to 1.
/// @param easing_function The easing function that generates the Tween values.
///                        See https://easings.net/ for list of easing functions.
///                        You can create and use your own custom functions as well.
///                        If you leave this as NULL and default value is assigned.
/// @param property Property is any field or data the user wants to be updated by
///                 the Tween.  This parameter is required by @ref Tw_Update 
///                 and @ref Tw_GetValue
/// @param property_updater The Tween needs to be told how to update the property.
///                         This is a user defined function that updates the @ref property.
///                         If the property is a simple float field then you can use
///                         the built-in @ref TW_FLOAT_UPDATER.  This parameter is required
///                         by @ref Tw_Update and @ref Tw_GetValue
/// @return Pointer to Tween Instance allocated on the heap
TW_EXPORT Tw_Instance* Tw_CreateInstance(
    Tw_Float           initial,
    Tw_Float           final,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater
);

/// @brief Destroys an allocated Tween Instance that is no longer in use.
/// @param i Tween Instance
TW_EXPORT void Tw_DestroyInstance(Tw_Instance* i);

/// @brief Gets the current value of the Tween.
///        This via is generated via property_updater and the easing_function.
/// @param i Tween Instance.
TW_EXPORT Tw_Float Tw_GetValue(Tw_Instance* i);

/// @brief Update the Tween value via property_updater and the easing_function.
///        The Tween value is not updated unless this function is called.
/// @param i Tween Instance
/// @param step Input Value that is added to the property value via 
///             processing by property_updater and easing_function.
TW_EXPORT void Tw_Update(Tw_Instance* i, Tw_Float step);

/// @brief Tells when the Tween has completed.  The Tween is completed
///        when it's current value is greater than or equal to the 
///        final value passed when creating a Tween.
/// @param i 
/// @return True if the Tween has completed.
TW_EXPORT Tw_Bool Tw_IsDone(Tw_Instance* i);

/// @brief Reset the Tween current value to allow the reuse of the Tween
///        after it has completed.
/// @param i Tween Instance
TW_EXPORT void Tw_Reset(Tw_Instance* i);

/// @brief Change the direction of the Tween value update by swapping
///        the Tween's inital and final value.  Tween automatically assigns
///        a direction based on the initial and final values.
/// @param i Tween Instance.
TW_EXPORT void Tw_Flip(Tw_Instance* i);

/// @brief Default property_updater for a single float value.
/// @param property Pointer to the property (in this case is a pointer to a float)
/// @param value The value to assign the property
TW_EXPORT void Tw_FloatUpdater(Tw_Ptr property, Tw_Float value);

/// @brief Default property_updater for a single float value.
#define TW_FLOAT_UPDATER Tw_FloatUpdater





#ifdef __cplusplus
}
#endif

#endif //TW_INSTANCE_H










