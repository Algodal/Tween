//Copyright (C) 2023 Alrick Grandison, Algodal™

#ifndef TW_INSTANCE_INL
#define TW_INSTANCE_INL

#include "tw-types.h"
#include "tw-thread-types.h"
#include "tw-functions.h"
#include "tw-thread.inl"

#ifdef DEBUG
#define TW_ASSERT_INSTANCE(i) \
    Tw_Assert(NULL!=i, "Instance can not be null"); \
    Tw_Assert(NULL!=i->property, "Property can not be NULL"); \
    Tw_Assert(NULL!=i->property_updater, "Property Updater can not be NULL"); \
    (void)0
#else
#define TW_ASSERT_INSTANCE(i)
#endif

struct Tw_Instance
{
    Tw_Float           initial;
    Tw_Float           final;
    Tw_Float           duration;
    Tw_Float           current;
    Tw_Ptr             property;
    Tw_PropertyUpdater property_updater;
    Tw_EasingFunction  easing_function;
    Tw_Thread          thread;
};

Tw_Instance* Tw_InitializeInstance(
    Tw_Instance* i,
    Tw_Float           initial,
    Tw_Float           final,
    Tw_EasingFunction  easing_function,
    Tw_Ptr             property,
    Tw_PropertyUpdater property_updater
);

#endif//TW_INSTANCE_INL




