#ifndef TW_UTILS_INL
#define TW_UTILS_INL

#define TW_MAX(a,b) (((a)>(b))?(a):(b))

// Debug
#ifndef NDEBUG
    #define TW_LOG(F, ...) if(F) printf(__VA_ARGS__)
#else
    #define TW_LOG(F, ...)
#endif

#endif//TW_UTILS_INL