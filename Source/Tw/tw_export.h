
#ifndef TW_EXPORT_H
#define TW_EXPORT_H

#ifdef TW_STATIC_DEFINE
#  define TW_EXPORT
#  define TW_NO_EXPORT
#else
#  ifndef TW_EXPORT
#    ifdef tw_EXPORTS
        /* We are building this library */
#      define TW_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define TW_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef TW_NO_EXPORT
#    define TW_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef TW_DEPRECATED
#  define TW_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef TW_DEPRECATED_EXPORT
#  define TW_DEPRECATED_EXPORT TW_EXPORT TW_DEPRECATED
#endif

#ifndef TW_DEPRECATED_NO_EXPORT
#  define TW_DEPRECATED_NO_EXPORT TW_NO_EXPORT TW_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TW_NO_DEPRECATED
#    define TW_NO_DEPRECATED
#  endif
#endif

#endif /* TW_EXPORT_H */
