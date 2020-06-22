#ifndef FDCORE_MACROS_H
#define FDCORE_MACROS_H

#define FD_EXPORT __attribute__((visibility("default")))

#ifndef FD_NOINLINE
    #define FD_INLINE inline
#else
    #define FD_INLINE
#endif

#endif // FDCORE_MACROS_H
