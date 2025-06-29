#ifndef TW_UTILS_INL
#define TW_UTILS_INL

#define TW_MIN(a,b) (((a)<(b))?(a):(b))
#define TW_MAX(a,b) (((a)>(b))?(a):(b))
#define TW_CLAMP(x, lower, upper) (TW_MIN((upper), TW_MAX((x), (lower))))
#define TW_DIRECTION(i, f) (((i)<=(f))?(+1):(-1))
#define TW_SIZE(i, f) ((f)-(i))

#endif//TW_UTILS_INL