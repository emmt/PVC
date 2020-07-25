/*
 * pvc.h -
 *
 * Definition for the PVC library.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PVC_H
#define _PVC_H 1

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
#  define _PVC_EXTERN_C_BEGIN extern "C" {
#  define _PVC_EXTERN_C_END   }
#  if defined(__GNUC__) || defined(__clang__)
#    define restrict __restrict__
#  elif defined(_MSC_VER)
#    define restrict __restrict
#  else
#    define restrict
#  endif
#else
#  define _PVC_EXTERN_C_BEGIN
#  define _PVC_EXTERN_C_END
#endif

/**
 * @def PVC_STRINGIFY(x)
 *
 * @brief Convert argument to a literal string.
 *
 * This macro yields a literal string made after macro expansion of
 * its argument.
 */
#define  PVC_STRINGIFY(x) _PVC_STRINGIFY(x)
#define _PVC_STRINGIFY(x) #x

/**
 * @def PVC_VERSION_STRING(major,minor,micro)
 *
 * @brief Build version string from major, minor and micro version
 *        tokens.
 *
 * This macro yields a literal string made afeter macro expansion of
 * its arguments.
 *
 * @see PVC_STRINGIFY, PVC_COMPILER_VERSION.
 */
#define PVC_VERSION_STRING(major,minor,micro) \
  PVC_STRINGIFY(major)"."PVC_STRINGIFY(minor)"."PVC_STRINGIFY(micro)

/**
 * @def PVC_COMPILER_NAME
 *
 * @brief Name of compiler.
 *
 * This macro expands as a literal string with the name of the
 * compiler or `"unknown-compiler"` if the compiler cannot be
 * determined.
 *
 * @see PVC_COMPILER_VERSION.
 */

/**
 * @def PVC_COMPILER_VERSION
 *
 * @brief Version of compiler.
 *
 * This macro expands as a literal string with the version of the
 * compiler or `"unknown-compiler-version"` if the compiler cannot be
 * determined.
 *
 * @see PVC_COMPILER_NAME, PVC_COMPILER_VERSION.
 */
#if defined(__clang__)
#  define PVC_COMPILER_NAME    "CLang"
#  define PVC_COMPILER_VERSION PVC_VERSION_STRING(__clang_major__,      \
                                                  __clang_minor__,      \
                                                  __clang_patchlevel__)
#elif defined(__GNUC__)
#  define PVC_COMPILER_NAME    "GCC"
#  define PVC_COMPILER_VERSION PVC_VERSION_STRING(__GNUC__,             \
                                                  __GNUC_MINOR__,       \
                                                  __GNUC_PATCHLEVEL__)
#elif defined(__INTEL_COMPILER)
#  define PVC_COMPILER_NAME    "ICC"
#  define PVC_COMPILER_VERSION __INTEL_COMPILER
#else
#  define PVC_COMPILER         "unknown-compiler"
#  define PVC_COMPILER_VERSION "unknown-compiler-version"
#endif

/**
 * @def PVC_SUFFIX_TO_CTYPE(sfx)
 *
 * @brief Get C type associated with suffix.
 *
 * This macro yields the C type associated with the suffix @a sfx as
 * summarized by the following table:
 *
 * | Suffix | C Type               |
 * |-------:|:---------------------|
 * |    `c` | `char`               |
 * |   `sc` | `signed char`        |
 * |   `uc` | `unsigned char`      |
 * |    `s` | `short`              |
 * |   `us` | `unsigned short`     |
 * |    `i` | `int`                |
 * |   `ui` | `unsigned int`       |
 * |    `l` | `long`               |
 * |   `ul` | `unsigned long`      |
 * |   `ll` | `long long`          |
 * |  `ull` | `unsigned long long` |
 * |    `f` | `float`              |
 * |    `d` | `double`             |
 * |    `q` | `long double`        |
 *
 * Note that `char`, `signed char` and `unsigned char` are distinct
 * types in C.  Macro expansion is performed on argument @a sfx, call
 * `_PVC_SUFFIX_TO_CTYPE_(sfx)` instead if you do not want to expand
 * argument.
 *
 * Other suffixes, say `x`, may be inserted by defining a macro
 * `_PVC_SUFFIX_TO_CTYPE_x` which expands to the corresponding C type.
 */
#define PVC_SUFFIX_TO_CTYPE(sfx)  _PVC_SUFFIX_TO_CTYPE_(sfx)

/* The trick is to define macro `_PVC_SUFFIX_TO_CTYPE_(sfx)` such that
   it uses 2 tokens `_PVC_SUFFIX_TO_CTYPE_` which is not expanded as
   it is the name of the macro and `sfx` which is just replaced by its
   value.  In that way there are less risks that macro expansion yield
   unpredictable result (the compiler will complain if the macor is
   redefined). */
#define _PVC_SUFFIX_TO_CTYPE_(sfx) _PVC_SUFFIX_TO_CTYPE_##sfx
#define _PVC_SUFFIX_TO_CTYPE_c     char
#define _PVC_SUFFIX_TO_CTYPE_sc    signed char
#define _PVC_SUFFIX_TO_CTYPE_uc    unsigned char
#define _PVC_SUFFIX_TO_CTYPE_s     short
#define _PVC_SUFFIX_TO_CTYPE_us    unsigned short
#define _PVC_SUFFIX_TO_CTYPE_i     int
#define _PVC_SUFFIX_TO_CTYPE_ui    unsigned int
#define _PVC_SUFFIX_TO_CTYPE_l     long
#define _PVC_SUFFIX_TO_CTYPE_ul    unsigned long
#define _PVC_SUFFIX_TO_CTYPE_ll    long long
#define _PVC_SUFFIX_TO_CTYPE_ull   unsigned long long
#define _PVC_SUFFIX_TO_CTYPE_f     float
#define _PVC_SUFFIX_TO_CTYPE_d     double
#define _PVC_SUFFIX_TO_CTYPE_q     long double

#define _PVC_GENERIC_NUMERICAL_CALL_1(pfx, x)           \
    _Generic((x),                                       \
             char:               pfx##_c,               \
             signed char:        pfx##_sc,              \
             unsigned char:      pfx##_uc,              \
             short:              pfx##_s,               \
             unsigned short:     pfx##_us,              \
             int:                pfx##_i,               \
             unsigned int:       pfx##_ui,              \
             long:               pfx##_l,               \
             unsigned long:      pfx##_ul,              \
             long long:          pfx##_ll,              \
             unsigned long long: pfx##_ull,             \
             float:              pfx##_f,               \
             double:             pfx##_d,               \
             long double:        pfx##_q)(x)
#define _PVC_GENERIC_NUMERICAL_CALL_2(pfx, x, y)        \
    _Generic((x) + (y),                                 \
             char:               pfx##_c,               \
             signed char:        pfx##_sc,              \
             unsigned char:      pfx##_uc,              \
             short:              pfx##_s,               \
             unsigned short:     pfx##_us,              \
             int:                pfx##_i,               \
             unsigned int:       pfx##_ui,              \
             long:               pfx##_l,               \
             unsigned long:      pfx##_ul,              \
             long long:          pfx##_ll,              \
             unsigned long long: pfx##_ull,             \
             float:              pfx##_f,               \
             double:             pfx##_d,               \
             long double:        pfx##_q)((x), (y))
#define _PVC_GENERIC_NUMERICAL_CALL_3(pfx, x, y, z)     \
    _Generic((x) + (y) + (z),                           \
             char:               pfx##_c,               \
             signed char:        pfx##_sc,              \
             unsigned char:      pfx##_uc,              \
             short:              pfx##_s,               \
             unsigned short:     pfx##_us,              \
             int:                pfx##_i,               \
             unsigned int:       pfx##_ui,              \
             long:               pfx##_l,               \
             unsigned long:      pfx##_ul,              \
             long long:          pfx##_ll,              \
             unsigned long long: pfx##_ull,             \
             float:              pfx##_f,               \
             double:             pfx##_d,               \
             long double:        pfx##_q)((x), (y), (z))

/**
 * @def PVC_POINTER_TO_INTEGER(ptr)
 *
 * Yields address `ptr` as an integer.
 */
#define PVC_POINTER_TO_INTEGER(ptr) ((char const*)(ptr) - (char const*)0)

/**
 * @def PVC_IS_ALIGNED(ptr, siz)
 *
 * Yields whether address `ptr` is properly aligned on a multiple of `siz`
 * bytes.  `siz` must be at least 1 and a power of 2.
 */
#define PVC_IS_ALIGNED(ptr, siz) \
    ((PVC_POINTER_TO_INTEGER(ptr)&((siz) - 1)) == 0)


_PVC_EXTERN_C_BEGIN

typedef struct PVC_TimeStatData PVC_TimeStatData;
struct PVC_TimeStatData {
    double min, max, sum1, sum2;
    size_t numb;
};

typedef struct PVC_TimeStat PVC_TimeStat;
struct PVC_TimeStat {
    double min, max, avg, std;
    size_t numb;
};

extern void pvc_time_stat_init(PVC_TimeStatData* tsd);
extern void pvc_time_stat_update(PVC_TimeStatData* tsd, double t);
extern PVC_TimeStat* pvc_time_stat_compute(PVC_TimeStat* ts,
                                           PVC_TimeStatData const* tsd);
extern void pvc_time_stat_print(FILE* output,
				char const* pfx,
				PVC_TimeStat const* ts);
extern double pvc_elapsed_seconds(struct timespec const* t,
				  struct timespec const* t0);

extern int pvc_instrset(void);

extern float (*pvc_dot_f)(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_2(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_3(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_4(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_5(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_6(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_7(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_8(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_9(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_10(size_t n, float const* restrict x, float const* restrict y);
extern float pvc_dot_f_ref(size_t n, float const* restrict x, float const* restrict y);

extern double (*pvc_dot_d)(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_2(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_3(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_4(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_5(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_6(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_7(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_8(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_9(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_10(size_t n, double const* restrict x, double const* restrict y);
extern double pvc_dot_d_ref(size_t n, double const* restrict x, double const* restrict y);

extern float (*pvc_dot3_f)(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_2(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_3(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_4(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_5(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_6(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_7(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_8(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_9(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_10(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);
extern float pvc_dot3_f_ref(size_t n, float const* restrict w, float const* restrict x, float const* restrict y);

extern double (*pvc_dot3_d)(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_2(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_3(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_4(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_5(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_6(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_7(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_8(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_9(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_10(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);
extern double pvc_dot3_d_ref(size_t n, double const* restrict w, double const* restrict x, double const* restrict y);

_PVC_EXTERN_C_END

#endif /* _PVC_H */
