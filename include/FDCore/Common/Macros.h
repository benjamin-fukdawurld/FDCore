#ifndef FDCORE_MACROS_H
#define FDCORE_MACROS_H

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__)
    #define FD_HAS_DECLSPEC
    #define FD_EXPORT __attribute__((__dllexport__))
    #define FD_IMPORT __attribute__((__dllimport__))
#else
    #define FD_EXPORT __attribute__((__visibility__("default")))
    #define FD_IMPORT
#endif

#ifndef FD_NOINLINE
    #define FD_INLINE inline
#else
    #define FD_INLINE
#endif

#endif // FDCORE_MACROS_H
