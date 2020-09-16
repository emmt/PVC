/*
 * pvc.h -
 *
 * Definitions for the PVC library.
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
  PVC_STRINGIFY(major) "." PVC_STRINGIFY(minor) "." PVC_STRINGIFY(micro)

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

/* Protect against someone else defining private symbols. */
#if defined(_pvc_field1) || defined(_pvc__pvc_field2)
#  error "Macros _pvc_fieldN (with N integer) must not be defined."
#endif

/**
 * @def PVC_ENDIAN_BOM
 *
 * @brief Get byte-order-mark of the host machine.
 *
 * This macro expands to a compile-time constant expression which is a
 * 32-bit byte-order-mark (BOM) indicating the native byte order of the
 * host machine.  A BOM of `0x01020304` indicates a big-endian machine,
 * while a BOM of `0x04030201` indicates a little-endian machine.
 *
 * @see PVC_IS_BIG_ENDIAN, PVC_IS_LITTLE_ENDIAN.
 */
#define PVC_ENDIAN_BOM                                  \
    (((union {  uint32_t _pvc_field1;                   \
                uint8_t  _pvc_field2[4];                \
    }){ ._pvc_field2 = {1,2,3,4} })._pvc_field1)

/**
 * @def PVC_IS_BIG_ENDIAN
 *
 * @brief Check whether host machine is big endian.
 *
 * This macro expands to a boolean compile-time constant expression
 * indicating whether the host machine has *big endian* storage order, that
 * is with most significant byte first.
 *
 * @see PVC_IS_LITTLE_ENDIAN, PVC_ENDIAN_BOM.
 */
#define PVC_IS_BIG_ENDIAN (PVC_ENDIAN_BOM == 0x01020304)

/**
 * @def PVC_IS_LITTLE_ENDIAN
 *
 * @brief Check whether host machine is little endian.
 *
 * This macro expands to a boolean compile-time constant expression
 * indicating whether the host machine has *little endian* storage order,
 * that is with least significant byte first.
 *
 * @see PVC_IS_BIG_ENDIAN, PVC_ENDIAN_BOM.
 */
#define PVC_IS_LITTLE_ENDIAN (PVC_ENDIAN_BOM == 0x04030201)

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
