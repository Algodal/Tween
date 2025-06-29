#ifndef TW_UTILS_INL
#define TW_UTILS_INL

#define TW_MIN(a,b) (((a)<(b))?(a):(b))
#define TW_MAX(a,b) (((a)>(b))?(a):(b))
#define TW_CLAMP(x, lower, upper) (TW_MIN((upper), TW_MAX((x), (lower))))

// Debug
#ifndef NDEBUG
    #define TW_LOG(F, ...) if(F) printf(__VA_ARGS__)
#else
    #define TW_LOG(F, ...)
#endif

#endif//TW_UTILS_INL