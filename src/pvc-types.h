/*
 * pvc-types.h -
 *
 * Definitions for basic types in PVC library.
 *
 *-----------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PVC_TYPES_H
#define _PVC_TYPES_H 1

#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <pvc.h>

/**
 * @addtogroup types Basic numerical types.
 *
 * Basic types are the 15 basic numerical types implemented by the C
 * language: `bool`, `char`, `signed char`, `unsigned char`, `short`,
 * `unsigned short`, `int`, `unsigned int`, `long`, `unsigned long`, `long
 * long`, `unsigned long long`, `float`, `double` and `long double`.
 *
 * In standard C, `char`, `signed char` and `unsigned char` are distinct
 * types.  For other integer types `signed` is implicit if neither `signed`
 * nor `unsigned` is specified.
 *
 * To each basic type, PVC associate a unique numerical identifier (see
 * PVC_TYPE_ID()) and a unique suffix (see PVC_SUFFIX_TO_TYPE()) which can
 * both be determined at compile-time.  These can be used for simple
 * type-oriented meta-programming.  For instance, the identifier may be
 * used to build a type-indexed table while the suffix may be used to name
 * type-specific functions and to allow for simple type dispatching (like
 * the functions in `<math.h>` since C99).
 *
 * @{
 */

/**
 * @def PVC_ZERO(T)
 *
 * @brief Get the zero of a given type.
 *
 * This macro expands to a compile-time constant expression whose value is
 * a zero of type @a T.  Call pvc_zero() to get the zero of the same type
 * of a given argument.
 *
 * @see PVC_ONE(), pvc_one(), pvc_zero().
 */
#define PVC_ZERO(T) ((T)0)

/**
 * @def PVC_ONE(T)
 *
 * @brief Get the "one" value of a given type.
 *
 * This macro expands to a compile-time constant expression whose value is
 * the multiplicative identity of type @a T.  Call pvc_one() to get the
 * "one" value of the same type of a given argument.
 *
 * @see PVC_ZERO(), pvc_one(), pvc_zero().
 */
#define PVC_ONE(T) (pvc_one(PVC_ZERO(T)))

/**
 * @def pvc_zero(x)
 *
 * @brief Get the zero of the same type of given argument.
 *
 * This macro expands to a compile-time constant expression whose value is
 * the "zero" of the same type as @a x.
 *
 * In C++, pvc_zero() is implemented as an inlined function.
 *
 * @see PVC_ZERO(), PVC_ZERO(), pvc_one().
 */
/**
 * @def pvc_one(x)
 *
 * @brief Get the "one" value of the same type of given argument.
 *
 * This macro expands to a compile-time constant expression whose value is
 * the multiplicative identity of the same type as @a x.
 *
 * In C++, pvc_one() is implemented as an inlined function.
 *
 * @see PVC_ZERO(), PVC_ZERO(), pvc_zero().
 */
#ifdef _PVC_DOXYGEN_PARSING

#define pvc_zero(T) ...
#define pvc_one(T) ...

#elif defined (__cplusplus)

static inline bool pvc_zero(bool _pvc_arg) { return false; }
static inline bool pvc_one(bool _pvc_arg) { return true; }
#define _PVC_ENCODE(T)                                  \
    static inline T pvc_zero(T _pvc_arg) { return 0; }  \
    static inline T pvc_one(T _pvc_arg) { return 1; }
_PVC_ENCODE(char);
_PVC_ENCODE(signed char);
_PVC_ENCODE(unsigned char);
_PVC_ENCODE(short);
_PVC_ENCODE(unsigned short);
_PVC_ENCODE(int);
_PVC_ENCODE(unsigned int);
_PVC_ENCODE(long);
_PVC_ENCODE(unsigned long);
_PVC_ENCODE(long long);
_PVC_ENCODE(unsigned long long);
_PVC_ENCODE(float);
_PVC_ENCODE(double);
_PVC_ENCODE(long double);
#undef _PVC_ENCODE

#else /* not C++ */

#define pvc_zero(x)                                     \
    _Generic((x),                                       \
             bool:                               false, \
             char:                             (char)0, \
             signed char:               (signed char)0, \
             unsigned char:           (unsigned char)0, \
             short:                           (short)0, \
             unsigned short:         (unsigned short)0, \
             int:                               (int)0, \
             unsigned int:             (unsigned int)0, \
             long:                             (long)0, \
             unsigned long:           (unsigned long)0, \
             long long:                   (long long)0, \
             unsigned long long: (unsigned long long)0, \
             float:                           (float)0, \
             double:                         (double)0, \
             long double:               (long double)0)

#define pvc_one(x)                                      \
    _Generic((x),                                       \
             bool:                                true, \
             char:                             (char)1, \
             signed char:               (signed char)1, \
             unsigned char:           (unsigned char)1, \
             short:                           (short)1, \
             unsigned short:         (unsigned short)1, \
             int:                               (int)1, \
             unsigned int:             (unsigned int)1, \
             long:                             (long)1, \
             unsigned long:           (unsigned long)1, \
             long long:                   (long long)1, \
             unsigned long long: (unsigned long long)1, \
             float:                           (float)1, \
             double:                         (double)1, \
             long double:               (long double)1)

#endif /* C or C++ */

/**
 * @def PVC_SUFFIX_TO_TYPE(sfx)
 *
 * @brief Get C type associated with suffix.
 *
 * This macro yields the C type associated with the suffix @a sfx as
 * summarized by the following table:
 *
 * | Suffix | C Type               |
 * |-------:|:---------------------|
 * |    `b` | `bool` or `_Bool`    |
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
 * |   `ld` | `long double`        |
 * |   `i8` | `int8_t`             |
 * |   `u8` | `uint8_t`            |
 * |  `i16` | `int16_t`            |
 * |  `u16` | `uint16_t`           |
 * |  `i32` | `int32_t`            |
 * |  `u32` | `uint32_t`           |
 * |  `i64` | `int64_t`            |
 * |  `u64` | `uint64_t`           |
 *
 * Note that `char`, `signed char` and `unsigned char` are distinct types
 * in C.  Macro expansion is performed on argument @a sfx, call
 * `_PVC_SUFFIX_TO_TYPE_(sfx)` instead if you do not want to expand
 * argument.
 *
 * Other suffixes, say `x`, may be inserted by defining a macro
 * `_PVC_SUFFIX_TO_TYPE_x` which expands to the corresponding C type.
 */
/* The trick is to define macro `_PVC_SUFFIX_TO_TYPE_(sfx)` such that it
   uses 2 tokens `_PVC_SUFFIX_TO_TYPE_` which is not expanded as it is the
   name of the macro itself and `sfx` which is just replaced by its value.
   In that way, there are less risks that macro expansion yields
   unpredictable result (the compiler will complain if the macro is
   redefined). */
#define PVC_SUFFIX_TO_TYPE(sfx)  _PVC_SUFFIX_TO_TYPE_(sfx)
#ifndef _PVC_DOXYGEN_PARSING
#  define _PVC_SUFFIX_TO_TYPE_(sfx) _PVC_SUFFIX_TO_TYPE_##sfx
#  define _PVC_SUFFIX_TO_TYPE_b     bool
#  define _PVC_SUFFIX_TO_TYPE_c     char
#  define _PVC_SUFFIX_TO_TYPE_sc    signed char
#  define _PVC_SUFFIX_TO_TYPE_uc    unsigned char
#  define _PVC_SUFFIX_TO_TYPE_s     short
#  define _PVC_SUFFIX_TO_TYPE_us    unsigned short
#  define _PVC_SUFFIX_TO_TYPE_i     int
#  define _PVC_SUFFIX_TO_TYPE_ui    unsigned int
#  define _PVC_SUFFIX_TO_TYPE_l     long
#  define _PVC_SUFFIX_TO_TYPE_ul    unsigned long
#  define _PVC_SUFFIX_TO_TYPE_ll    long long
#  define _PVC_SUFFIX_TO_TYPE_ull   unsigned long long
#  define _PVC_SUFFIX_TO_TYPE_f     float
#  define _PVC_SUFFIX_TO_TYPE_d     double
#  define _PVC_SUFFIX_TO_TYPE_ld    long double
#  define _PVC_SUFFIX_TO_TYPE_i8    int8_t
#  define _PVC_SUFFIX_TO_TYPE_u8    uint8_t
#  define _PVC_SUFFIX_TO_TYPE_i16   int16_t
#  define _PVC_SUFFIX_TO_TYPE_u16   uint16_t
#  define _PVC_SUFFIX_TO_TYPE_i32   int32_t
#  define _PVC_SUFFIX_TO_TYPE_u32   uint32_t
#  define _PVC_SUFFIX_TO_TYPE_i64   int64_t
#  define _PVC_SUFFIX_TO_TYPE_u64   uint64_t
#endif /* not Doxygen */

/**
 * @def pvc_type_id(x)
 *
 * @brief Unique basic numerical type identifier.
 *
 * The statement `pvc_type_id(x)` yields an integer compile-time constant
 * expression with the unique identifier of the basic numerical type of @a
 * x or `PVC_TYPE_ID_OTHER` (that is 0) if @a x is not a value with a basic
 * numerical type.  Type qualifiers are irrelevant.
 *
 * | C Type               | Macro                                                   | Value |
 * |:---------------------|:--------------------------------------------------------|------:|
 * | default              | `PVC_TYPE_ID_OTHER`                                     |     0 |
 * | `bool`               | `PVC_TYPE_ID_BOOL`                                      |     1 |
 * | `char`               | `PVC_TYPE_ID_CHAR`                                      |     2 |
 * | `signed char`        | `PVC_TYPE_ID_SIGNED_CHAR`                               |     3 |
 * | `unsigned char`      | `PVC_TYPE_ID_UNSIGNED_CHAR`                             |     4 |
 * | `(signed) short`     | `PVC_TYPE_ID_SHORT`, `PVC_TYPE_ID_SIGNED_SHORT`         |     5 |
 * | `unsigned short`     | `PVC_TYPE_ID_UNSIGNED_SHORT`                            |     6 |
 * | `(signed) lint`      | `PVC_TYPE_ID_INT`, `PVC_TYPE_ID_SIGNED_INT`             |     7 |
 * | `unsigned int`       | `PVC_TYPE_ID_UNSIGNED_INT`                              |     8 |
 * | `(signed) llong`     | `PVC_TYPE_ID_LONG`, `PVC_TYPE_ID_SIGNED_LONG`           |     9 |
 * | `unsigned long`      | `PVC_TYPE_ID_UNSIGNED_LONG`                             |    10 |
 * | `(signed) long long` | `PVC_TYPE_ID_LONG_LONG`, `PVC_TYPE_ID_SIGNED_LONG_LONG` |    11 |
 * | `unsigned long long` | `PVC_TYPE_ID_UNSIGNED_LONG_LONG`                        |    12 |
 * | `float`              | `PVC_TYPE_ID_FLOAT`                                     |    13 |
 * | `double`             | `PVC_TYPE_ID_DOUBLE`                                    |    14 |
 * | `long double`        | `PVC_TYPE_ID_LONG_DOUBLE`                               |    15 |
 *
 * @see PVC_TYPE_ID().
 */
#ifdef _PVC_DOXYGEN_PARSING
#define pvc_type_id(x) ...
#endif

#define PVC_TYPE_ID_OTHER               (0)
#define PVC_TYPE_ID_BOOL                (1)
#define PVC_TYPE_ID_CHAR                (2)
#define PVC_TYPE_ID_SIGNED_CHAR         (3)
#define PVC_TYPE_ID_UNSIGNED_CHAR       (4)
#define PVC_TYPE_ID_SHORT               (5)
#define PVC_TYPE_ID_SIGNED_SHORT        PVC_TYPE_ID_SHORT
#define PVC_TYPE_ID_UNSIGNED_SHORT      (6)
#define PVC_TYPE_ID_INT                 (7)
#define PVC_TYPE_ID_SIGNED_INT          PVC_TYPE_ID_INT
#define PVC_TYPE_ID_UNSIGNED_INT        (8)
#define PVC_TYPE_ID_LONG                (9)
#define PVC_TYPE_ID_SIGNED_LONG         PVC_TYPE_ID_LONG
#define PVC_TYPE_ID_UNSIGNED_LONG       (10)
#define PVC_TYPE_ID_LONG_LONG           (11)
#define PVC_TYPE_ID_SIGNED_LONG_LONG    PVC_TYPE_ID_LONG_LONG
#define PVC_TYPE_ID_UNSIGNED_LONG_LONG  (12)
#define PVC_TYPE_ID_FLOAT               (13)
#define PVC_TYPE_ID_DOUBLE              (14)
#define PVC_TYPE_ID_LONG_DOUBLE         (15)

/* Range of identifiers for valid basic numerical types. */
#define _PVC_TYPE_ID_MIN  PVC_TYPE_ID_BOOL
#define _PVC_TYPE_ID_MAX  PVC_TYPE_ID_LONG_DOUBLE

/*
 * Check that two type identifiers are the same, treating non-basic
 * numerical types as NaNs.
 */
static inline bool _pvc_same_numerical_type_id(int a, int b)
{
    return (a == b && _PVC_TYPE_ID_MIN <= a && a <= _PVC_TYPE_ID_MAX);
}

/**
 * @def PVC_TYPE_ID(T)
 *
 * @brief Unique basic numerical type identifier.
 *
 * This macro expands to an integer compile-time constant expression with
 * the unique identifier of the basic numerical type @a T or
 * `PVC_TYPE_ID_OTHER` (that is 0) if @a T is not a C basic numerical type.
 * Type qualifiers are irrelevant.
 *
 * @see pvc_type_id().
 */
#define PVC_TYPE_ID(T) (pvc_type_id(PVC_ZERO(T)))

#ifndef _PVC_DOXYGEN_PARSING
#ifdef __cplusplus

/*
 * We use templates because we want `PVC_TYPE_ID_OTHER` to be returned for
 * non basic numerical types.  We rely on the C++ compiler to automatically
 * determine the template type to simplify the code.
 */
template <class T>
inline int pvc_type_id(T _pvc_arg)
{
    return PVC_TYPE_ID_OTHER;
}

#define _PVC_ENCODE(T, expr) \
    template <> inline int pvc_type_id<T>(T _pvc_arg) { return expr; }
_PVC_ENCODE(bool,               PVC_TYPE_ID_BOOL);
_PVC_ENCODE(char,               PVC_TYPE_ID_CHAR);
_PVC_ENCODE(signed char,        PVC_TYPE_ID_SIGNED_CHAR);
_PVC_ENCODE(unsigned char,      PVC_TYPE_ID_UNSIGNED_CHAR);
_PVC_ENCODE(short,              PVC_TYPE_ID_SHORT);
_PVC_ENCODE(unsigned short,     PVC_TYPE_ID_UNSIGNED_SHORT);
_PVC_ENCODE(int,                PVC_TYPE_ID_INT);
_PVC_ENCODE(unsigned int,       PVC_TYPE_ID_UNSIGNED_INT);
_PVC_ENCODE(long,               PVC_TYPE_ID_LONG);
_PVC_ENCODE(unsigned long,      PVC_TYPE_ID_UNSIGNED_LONG);
_PVC_ENCODE(long long,          PVC_TYPE_ID_LONG_LONG);
_PVC_ENCODE(unsigned long long, PVC_TYPE_ID_UNSIGNED_LONG_LONG);
_PVC_ENCODE(float,              PVC_TYPE_ID_FLOAT);
_PVC_ENCODE(double,             PVC_TYPE_ID_DOUBLE);
_PVC_ENCODE(long double,        PVC_TYPE_ID_LONG_DOUBLE);
#undef _PVC_ENCODE

#define PVC_TYPE_ID(T) (pvc_type_id(PVC_ZERO(T)))

#else /* not C++ */

/*
 * We rely on the fact that type qualifiers such as `const or `volatile` of
 * values (not pointers) are irrelevant in a type generic expression.
 */
#define pvc_type_id(x)                                                  \
    _Generic((x),                                                       \
             bool:               PVC_TYPE_ID_BOOL,                      \
             char:               PVC_TYPE_ID_CHAR,                      \
             signed char:        PVC_TYPE_ID_SIGNED_CHAR,               \
             unsigned char:      PVC_TYPE_ID_UNSIGNED_CHAR,             \
             short:              PVC_TYPE_ID_SHORT,                     \
             unsigned short:     PVC_TYPE_ID_UNSIGNED_SHORT,            \
             int:                PVC_TYPE_ID_INT,                       \
             unsigned int:       PVC_TYPE_ID_UNSIGNED_INT,              \
             long:               PVC_TYPE_ID_LONG,                      \
             unsigned long:      PVC_TYPE_ID_UNSIGNED_LONG,             \
             long long:          PVC_TYPE_ID_LONG_LONG,                 \
             unsigned long long: PVC_TYPE_ID_UNSIGNED_LONG_LONG,        \
             float:              PVC_TYPE_ID_FLOAT,                     \
             double:             PVC_TYPE_ID_DOUBLE,                    \
             long double:        PVC_TYPE_ID_LONG_DOUBLE,               \
             default:            PVC_TYPE_ID_OTHER)

#endif /* C or C++ */
#endif /* Doxygen */

#if INT8_MIN == SCHAR_MIN && INT8_MAX == SCHAR_MAX
#  define PVC_TYPE_ID_INT8     PVC_TYPE_ID_SIGNED_CHAR
#endif

#if UINT8_MAX == UCHAR_MAX
#  define PVC_TYPE_ID_UINT8    PVC_TYPE_ID_UNSIGNED_CHAR
#endif

#if INT16_MIN == SHRT_MIN && INT16_MAX == SHRT_MAX
#  define PVC_TYPE_ID_INT16    PVC_TYPE_ID_SHORT
#elif INT16_MIN == INT_MIN && INT16_MAX == INT_MAX
#  define PVC_TYPE_ID_INT16    PVC_TYPE_ID_INT
#endif

#if UINT16_MAX == USHRT_MAX
#  define PVC_TYPE_ID_UINT16   PVC_TYPE_ID_UNSIGNED_SHORT
#elif UINT16_MAX == UINT_MAX
#  define PVC_TYPE_ID_UINT16   PVC_TYPE_ID_UNSIGNED_INT
#endif

#if INT32_MIN == SHRT_MIN && INT32_MAX == SHRT_MAX
#  define PVC_TYPE_ID_INT32    PVC_TYPE_ID_SHORT
#elif INT32_MIN == INT_MIN && INT32_MAX == INT_MAX
#  define PVC_TYPE_ID_INT32    PVC_TYPE_ID_INT
#elif INT32_MIN == LONG_MIN && INT32_MAX == LONG_MAX
#  define PVC_TYPE_ID_INT32    PVC_TYPE_ID_LONG
#endif

#if UINT32_MAX == USHRT_MAX
#  define PVC_TYPE_ID_UINT32   PVC_TYPE_ID_UNSIGNED_SHORT
#elif UINT32_MAX == UINT_MAX
#  define PVC_TYPE_ID_UINT32   PVC_TYPE_ID_UNSIGNED_INT
#elif UINT32_MAX == ULONG_MAX
#  define PVC_TYPE_ID_UINT32   PVC_TYPE_ID_UNSIGNED_LONG
#endif

#if INT64_MIN == SHRT_MIN && INT64_MAX == SHRT_MAX
#  define PVC_TYPE_ID_INT64    PVC_TYPE_ID_SHORT
#elif INT64_MIN == INT_MIN && INT64_MAX == INT_MAX
#  define PVC_TYPE_ID_INT64    PVC_TYPE_ID_INT
#elif INT64_MIN == LONG_MIN && INT64_MAX == LONG_MAX
#  define PVC_TYPE_ID_INT64    PVC_TYPE_ID_LONG
#elif INT64_MIN == LLONG_MIN && INT64_MAX == LLONG_MAX
#  define PVC_TYPE_ID_INT64    PVC_TYPE_ID_LLONG
#endif

#if UINT64_MAX == USHRT_MAX
#  define PVC_TYPE_ID_UINT64   PVC_TYPE_ID_UNSIGNED_SHORT
#elif UINT64_MAX == UINT_MAX
#  define PVC_TYPE_ID_UINT64   PVC_TYPE_ID_UNSIGNED_INT
#elif UINT64_MAX == ULONG_MAX
#  define PVC_TYPE_ID_UINT64   PVC_TYPE_ID_UNSIGNED_LONG
#elif UINT64_MAX == ULLONG_MAX
#  define PVC_TYPE_ID_UINT64   PVC_TYPE_ID_UNSIGNED_LLONG
#endif

/**
 * @def PVC_SAME_NUMERICAL_TYPE(S,T)
 *
 * @brief Checking for equality of basic numerical types.
 *
 * The statement `PVC_IS_SAME_NUMERICAL_TYPE(S,T)` yields a boolean
 * compile-time constant expression indicating whether types @a S and @a T
 * are the same basic numerical type and without considering qualifiers
 * such as `const` or `volatile`.
 *
 * @see PVC_TYPE_ID, pvc_type_id.
 */
#define PVC_SAME_NUMERICAL_TYPE(S, T)                                 \
    _pvc_same_numerical_type_id(PVC_TYPE_ID(S), PVC_TYPE_ID(T))...

#define PVC_IS_BOOL(T)               (PVC_TYPE_ID(T) == PVC_TYPE_ID_BOOL)
#define PVC_IS_CHAR(T)               (PVC_TYPE_ID(T) == PVC_TYPE_ID_CHAR)
#define PVC_IS_SIGNED_CHAR(T)        (PVC_TYPE_ID(T) == PVC_TYPE_ID_SIGNED_CHAR)
#define PVC_IS_UNSIGNED_CHAR(T)      (PVC_TYPE_ID(T) == PVC_TYPE_ID_UNSIGNED_CHAR)
#define PVC_IS_SHORT(T)              (PVC_TYPE_ID(T) == PVC_TYPE_ID_SHORT)
#define PVC_IS_SIGNED_SHORT(T)       (PVC_TYPE_ID(T) == PVC_TYPE_ID_SIGNED_SHORT)
#define PVC_IS_UNSIGNED_SHORT(T)     (PVC_TYPE_ID(T) == PVC_TYPE_ID_UNSIGNED_SHORT)
#define PVC_IS_INT(T)                (PVC_TYPE_ID(T) == PVC_TYPE_ID_INT)
#define PVC_IS_SIGNED_INT(T)         (PVC_TYPE_ID(T) == PVC_TYPE_ID_SIGNED_INT)
#define PVC_IS_UNSIGNED_INT(T)       (PVC_TYPE_ID(T) == PVC_TYPE_ID_UNSIGNED_INT)
#define PVC_IS_LONG(T)               (PVC_TYPE_ID(T) == PVC_TYPE_ID_LONG)
#define PVC_IS_SIGNED_LONG(T)        (PVC_TYPE_ID(T) == PVC_TYPE_ID_SIGNED_LONG)
#define PVC_IS_UNSIGNED_LONG(T)      (PVC_TYPE_ID(T) == PVC_TYPE_ID_UNSIGNED_LONG)
#define PVC_IS_LONG_LONG(T)          (PVC_TYPE_ID(T) == PVC_TYPE_ID_LONG_LONG)
#define PVC_IS_SIGNED_LONG_LONG(T)   (PVC_TYPE_ID(T) == PVC_TYPE_ID_SIGNED_LONG_LONG)
#define PVC_IS_UNSIGNED_LONG_LONG(T) (PVC_TYPE_ID(T) == PVC_TYPE_ID_UNSIGNED_LONG_LONG)
#define PVC_IS_FLOAT(T)              (PVC_TYPE_ID(T) == PVC_TYPE_ID_FLOAT)
#define PVC_IS_DOUBLE(T)             (PVC_TYPE_ID(T) == PVC_TYPE_ID_DOUBLE)
#define PVC_IS_LONG_DOUBLE(T)        (PVC_TYPE_ID(T) == PVC_TYPE_ID_LONG_DOUBLE)

/**
 * @def pvc_is_signed(x)
 *
 * @brief Checking for signed numerical value.
 *
 * The statement `pvc_is_signed(x)` yields a boolean compile-time constant
 * expression indicating whether the value of `x` has a signed numerical
 * type.  Such a statement should always compile, yielding false for an
 * unsigned numerical value or a non-numerical value.  Note that
 * floating-point expressions are assumed to be signed.
 *
 * @see PVC_IS_SIGNED, pvc_is_unsigned, pvc_is_integer,
 * pvc_is_floatingpoint.
 */
#ifdef _PVC_DOXYGEN_PARSING
#define pvc_is_signed(x) ...
#endif

/**
 * @def pvc_is_unsigned(x)
 *
 * @brief Checking for unsigned numerical value.
 *
 * The statement `pvc_is_unsigned(x)` yields a boolean compile-time
 * constant expression indicating whether the value of `x` has an unsigned
 * numerical type.  Such a statement should always compile, yielding false
 * for a signed numerical value or a non-numerical value.  Note that
 * floating-point expressions are assumed to be signed.
 *
 * @see PVC_IS_UNSIGNED, pvc_is_signed, pvc_is_integer,
 * pvc_is_floatingpoint.
 */
#ifdef _PVC_DOXYGEN_PARSING
#define pvc_is_unsigned(x) ...
#endif

/**
 * @def pvc_is_integer(x)
 *
 * @brief Checking for integer numerical value.
 *
 * The statement `pvc_is_integer(x)` yields a boolean compile-time constant
 * expression indicating whether `x` has an integer numerical value.  Such
 * a statement should always compile, yielding false for a non-integer
 * numerical value or a non-numerical value.
 *
 * @see PVC_IS_INTEGER, pvc_is_unsigned, pvc_is_signed, pvc_is_floatingpoint.
 */
#ifdef _PVC_DOXYGEN_PARSING
#define pvc_is_integer(x) ...
#endif

/**
 * @def pvc_is_floatingpoint(x)
 *
 * @brief Checking for floating point value.
 *
 * The statement `pvc_is_floatingpoint(x)` yields a boolean compile-time
 * constant expression indicating whether `x` has a floating-point value.
 * Such a statement should always compile, yielding false for a non
 * floating-point numerical value or a non-numerical value.
 *
 * @see PVC_IS_FLOATINGPOINT, pvc_is_unsigned, pvc_is_signed, pvc_is_integer.
 */
#ifdef _PVC_DOXYGEN_PARSING
#define pvc_is_floatingpoint(x) ...
#endif

/**
 * @def PVC_IS_SIGNED(T)
 *
 * @brief Checking for signed numerical type.
 *
 * The statement `PVC_IS_SIGNED(T)` yields a boolean compile-time constant
 * expression indicating whether its argument is a signed numerical type.
 * This macro should always compile, yielding false for an unsigned
 * numerical type or a non-numerical type.  Note that floating-point types
 * are assumed to be signed.
 *
 * @see PVC_IS_UNSIGNED, PVC_IS_INTEGER, PVC_IS_FLOATINGPOINT.
 */
#define PVC_IS_SIGNED(T) (pvc_is_signed(PVC_ZERO(T)))

/**
 * @def PVC_IS_UNSIGNED(T)
 *
 * @brief Checking for unsigned numerical type.
 *
 * The statement `PVC_IS_UNSIGNED(T)` yields a boolean compile-time
 * constant expression indicating whether its argument is an unsigned
 * numerical type.  This macro should always compile, yielding false for a
 * signed numerical type and a non-numerical type.  Note that
 * floating-point types are assumed to be signed.
 *
 * @see PVC_IS_SIGNED, PVC_IS_INTEGER, PVC_IS_FLOATINGPOINT.
 */
#define PVC_IS_UNSIGNED(T) (pvc_is_unsigned(PVC_ZERO(T)))

/**
 * @def PVC_IS_INTEGER(T)
 *
 * @brief Checking for integer numerical type.
 *
 * The statement `PVC_IS_INTEGER(T)` yields a boolean compile-time constant
 * expression indicating whether its argument is an integer numerical type.
 * This macro should always compile, yielding false for a non-integer
 * numerical type or a non-numerical type.
 *
 * @see PVC_IS_UNSIGNED, PVC_IS_SIGNED, PVC_IS_FLOATINGPOINT.
 */
#define PVC_IS_INTEGER(T) (pvc_is_integer(PVC_ZERO(T)))

/**
 * @def PVC_IS_FLOATINGPOINT(T)
 *
 * @brief Checking for floating point type.
 *
 * The statement `PVC_IS_FLOATINGPOINT(T)` yields a boolean compile-time
 * constant expression indicating whether its argument is a floating-point
 * type.  This macro should always compile, yielding false for a non
 * floating-point numerical type or a non-numerical type.
 *
 * @see PVC_IS_UNSIGNED, PVC_IS_SIGNED, PVC_IS_INTEGER.
 */
#define PVC_IS_FLOATINGPOINT(T) (pvc_is_floatingpoint(PVC_ZERO(T)))

#ifndef _PVC_DOXYGEN_PARSING
#ifdef __cplusplus

/*
 * Functions for predicates.  We use the same tricks as for `pvc_type_id`
 * (see comments there for explanations).
 */

template <class T>
inline bool pvc_is_signed(T _pvc_arg)
{
    return false;
}

template <class T>
inline bool pvc_is_unsigned(T _pvc_arg)
{
    return false;
}

template <class T>
inline bool pvc_is_integer(T _pvc_arg)
{
    return false;
}

template <class T>
inline bool pvc_is_floatingpoint(T _pvc_arg)
{
    return false;
}

#define _PVC_ENCODE(func, T, expr) \
    template <> inline bool pvc_##func<T>(T _pvc_arg) { return expr; }

_PVC_ENCODE(is_signed, char, ((char)-1) < 0);
_PVC_ENCODE(is_signed, signed char,    true);
_PVC_ENCODE(is_signed, short,          true);
_PVC_ENCODE(is_signed, int,            true);
_PVC_ENCODE(is_signed, long,           true);
_PVC_ENCODE(is_signed, long long,      true);
_PVC_ENCODE(is_signed, float,          true);
_PVC_ENCODE(is_signed, double,         true);
_PVC_ENCODE(is_signed, long double,    true);

_PVC_ENCODE(is_unsigned, bool,               true);
_PVC_ENCODE(is_unsigned, char,     ((char)-1) > 0);
_PVC_ENCODE(is_unsigned, unsigned char,      true);
_PVC_ENCODE(is_unsigned, unsigned short,     true);
_PVC_ENCODE(is_unsigned, unsigned int,       true);
_PVC_ENCODE(is_unsigned, unsigned long,      true);
_PVC_ENCODE(is_unsigned, unsigned long long, true);

_PVC_ENCODE(is_integer, bool,               true);
_PVC_ENCODE(is_integer, char,               true);
_PVC_ENCODE(is_integer, signed char,        true);
_PVC_ENCODE(is_integer, unsigned char,      true);
_PVC_ENCODE(is_integer, short,              true);
_PVC_ENCODE(is_integer, unsigned short,     true);
_PVC_ENCODE(is_integer, int,                true);
_PVC_ENCODE(is_integer, unsigned int,       true);
_PVC_ENCODE(is_integer, long,               true);
_PVC_ENCODE(is_integer, unsigned long,      true);
_PVC_ENCODE(is_integer, long long,          true);
_PVC_ENCODE(is_integer, unsigned long long, true);

_PVC_ENCODE(is_floatingpoint, float,       true);
_PVC_ENCODE(is_floatingpoint, double,      true);
_PVC_ENCODE(is_floatingpoint, long double, true);

#undef _PVC_ENCODE

#else /* not C++ */

#define pvc_is_signed(x)                        \
    _Generic((x),                               \
             char: ((char)-1) < 0,              \
             signed char:    true,              \
             short:          true,              \
             int:            true,              \
             long:           true,              \
             long long:      true,              \
             float:          true,              \
             double:         true,              \
             long double:    true,              \
             default:       false)

#define pvc_is_unsigned(x)                      \
    _Generic((x),                               \
             bool:               true,          \
             char:     ((char)-1) > 0,          \
             unsigned char:      true,          \
             unsigned short:     true,          \
             unsigned int:       true,          \
             unsigned long:      true,          \
             unsigned long long: true,          \
             default:           false)

#define pvc_is_integer(x)                       \
    _Generic((x),                               \
             bool:               true,          \
             char:               true,          \
             signed char:        true,          \
             unsigned char:      true,          \
             short:              true,          \
             unsigned short:     true,          \
             int:                true,          \
             unsigned int:       true,          \
             long:               true,          \
             unsigned long:      true,          \
             long long:          true,          \
             unsigned long long: true,          \
             default:            false)


#define pvc_is_floatingpoint(x)                 \
    _Generic((x),                               \
             float:       true,                 \
             double:      true,                 \
             long double: true,                 \
             default:     false)

#endif /* C or C++ */
#endif /* not Doxygen */

/**
 * @def PVC_FLT_INF
 *
 * @brief Single precision infinity.
 *
 * This macro expands to a compile-time constant expression of type
 * `float` which evaluates to infinity.
 *
 * @see PVC_DBL_INF, PVC_LDBL_INF.
 */
#ifdef _PVC_DOXYGEN_PARSING
#  define PVC_FLT_INF  ...
#endif

/**
 * @def PVC_DBL_INF
 *
 * @brief Double precision infinity.
 *
 * This macro expands to a compile-time constant expression of type
 * `double` which evaluates to infinity.
 *
 * @see PVC_FLT_INF, PVC_LDBL_INF.
 */
#ifdef _PVC_DOXYGEN_PARSING
#  define PVC_DBL_INF  ...
#endif

/**
 * @def PVC_LDBL_INF
 *
 * @brief Quadruple precision infinity.
 *
 * This macro expands to a compile-time constant expression of type
 * `long double` which evaluates to infinity.
 *
 * @see PVC_FLT_INF, PVC_DBL_INF.
 */
#ifdef _PVC_DOXYGEN_PARSING
#  define PVC_LDBL_INF  ...
#endif

/*
 * Since C99, the macro `INFINITY`, defined in `<math.h>`, expands to a
 * constant expression of type float which evaluates to positive or
 * unsigned infinity.
 *
 * Since C99, the macros `HUGE_VALF`, `HUGE_VAL` and `HUGE_VALL`, defined
 * in `<math.h>`, expand to positive floating point constant expressions
 * which compare equal to the values returned by floating-point functions
 * and operators in case of overflow.
 *
 * See <https://en.cppreference.com/w/c>.
 */
#ifndef _PVC_DOXYGEN_PARSING
#  if defined(HUGE_VALF)
#    define PVC_FLT_INF  (HUGE_VALF)
#  elif defined(INFINITY)
#    define PVC_FLT_INF  ((float)INFINITY)
#  else /* use literal constant that certainly  overflows */
#    define PVC_FLT_INF  (1e10000f)
#  endif
#  if defined(HUGE_VAL)
#    define PVC_DBL_INF  (HUGE_VAL)
#  elif defined(INFINITY)
#    define PVC_DBL_INF  ((double)INFINITY)
#  else /* use literal constant that certainly  overflows */
#    define PVC_DBL_INF  (1e10000)
#  endif
#  if defined(HUGE_VALL)
#    define PVC_LDBL_INF  (HUGE_VALL)
#  elif defined(INFINITY)
#    define PVC_LDBL_INF  ((long double)INFINITY)
#  else /* use literal constant that certainly  overflows */
#    define PVC_LDBL_INF  (1e10000L)
#  endif
#endif /* C or C++ */

/**
 * @def PVC_FLT_NAN
 *
 * @brief Single precision quiet not-a-number.
 *
 * If defined, this macro expands to a compile-time constant expression of
 * type `float` which evaluates to a quiet not-a-number (QNaN).
 *
 * @see PVC_DBL_NAN, PVC_LDBL_NAN.
 */
#ifdef _PVC_DOXYGEN_PARSING
#  define PVC_FLT_NAN  ...
#endif

/**
 * @def PVC_DBL_NAN
 *
 * @brief Double precision quiet not-a-number.
 *
 * If defined, this macro expands to a compile-time constant expression of
 * type `double` which evaluates to a quiet not-a-number (QNaN).
 *
 * @see PVC_FLT_NAN, PVC_LDBL_NAN.
 */
#ifdef _PVC_DOXYGEN_PARSING
#  define PVC_DBL_NAN  ...
#endif

/**
 * @def PVC_LDBL_NAN
 *
 * @brief Quadruple precision quiet not-a-number.
 *
 * If defined, this macro expands to a compile-time constant expression of
 * type `long double` which evaluates to a quiet not-a-number (QNaN).
 *
 * @see PVC_FLT_NAN, PVC_DBL_NAN.
 */
#ifdef _PVC_DOXYGEN_PARSING
#  define PVC_LDBL_NAN ...
#endif

/*
 * Since C99, the macro `NAN`, defined in `<math.h>`, expands a to constant
 * expression of type float which evaluates to a quiet not-a-number (QNaN)
 * value.  If the implementation does not support QNaNs, this macro
 * constant is not defined.
 *
 * See <https://en.cppreference.com/w/c>.
 */
#ifndef _PVC_DOXYGEN_PARSING
#  ifdef NAN
#    define PVC_FLT_NAN  ((float)NAN)
#    define PVC_DBL_NAN  ((double)NAN)
#    define PVC_LDBL_NAN ((long double)NAN)
#  else
#    define PVC_FLT_NAN  (1.0f/0.0f)
#    define PVC_DBL_NAN  (1.0/0.0)
#    define PVC_LDBL_NAN (1.0L/0.0L)
#  endif
#endif /* C or C++ */

/**
 * @def pvc_type_min(x)
 *
 * @brief Minimum value of the same type as given argument.
 *
 * The statement `pvc_type_min(x)` yields a compile-time constant
 * expression of the same type as @a x which evaluates to the minimal
 * representable value of this type, that is plus infinity for
 * floating-point types.
 *
 * @see PVC_TYPE_MIN, pvc_type_max.
 */
#ifdef _PVC_DOXYGEN_PARSING
#define pvc_type_min(x) ...
#endif

/**
 * @def pvc_type_max(x)
 *
 * @brief Maximum value of the same type as given argument.
 *
 * The statement `pvc_type_max(x)` yields a compile-time constant
 * expression of the same type as @a x which evaluates to the maximal
 * representable value of this type, that is plus infinity for
 * floating-point types.
 *
 * @see PVC_TYPE_MAX, pvc_type_min.
 */
#ifdef _PVC_DOXYGEN_PARSING
#define pvc_type_max(x) ...
#endif

/**
 * @def PVC_TYPE_MIN(T)
 *
 * @brief Minimum value of given type.
 *
 * The statement `PVC_TYPE_MIN(T)` yields a compile-time constant
 * expression of type @a T which evaluates to the minimal representable
 * value of this type, that is minus infinity for floating-point types.
 *
 * @see PVC_TYPE_MAXN, pvc_type_min.
 */
#define PVC_TYPE_MIN(T) (pvc_type_min(PVC_ZERO(T)))

/**
 * @def PVC_TYPE_MAX(T)
 *
 * @brief Maximum value of given type.
 *
 * The statement `PVC_TYPE_MAX(T)` yields a compile-time constant
 * expression of type @a T which evaluates to the maximal representable
 * value of this type, that is plus infinity for floating-point types.
 *
 * @see PVC_TYPE_MIN, pvc_type_max.
 */
#define PVC_TYPE_MAX(T) (pvc_type_max(PVC_ZERO(T)))

#ifndef _PVC_DOXYGEN_PARSING
#ifdef __cplusplus

#define _PVC_ENCODE(op, T, expr) \
    static inline T pvc_type_##op(T _pvc_arg) { return expr; }

_PVC_ENCODE(min, bool,                    false);
_PVC_ENCODE(min, char,                 CHAR_MIN);
_PVC_ENCODE(min, signed char,         SCHAR_MIN);
_PVC_ENCODE(min, unsigned char,               0);
_PVC_ENCODE(min, short,                SHRT_MIN);
_PVC_ENCODE(min, unsigned short,              0);
_PVC_ENCODE(min, int,                   INT_MIN);
_PVC_ENCODE(min, unsigned int,                0);
_PVC_ENCODE(min, long,                 LONG_MIN);
_PVC_ENCODE(min, unsigned long,               0);
_PVC_ENCODE(min, long long,           LLONG_MIN);
_PVC_ENCODE(min, unsigned long long,          0);
_PVC_ENCODE(min, float,            -PVC_FLT_INF);
_PVC_ENCODE(min, double,           -PVC_DBL_INF);
_PVC_ENCODE(min, long double,     -PVC_LDBL_INF);

_PVC_ENCODE(max, bool,                     true);
_PVC_ENCODE(max, char,                 CHAR_MAX);
_PVC_ENCODE(max, signed char,         SCHAR_MAX);
_PVC_ENCODE(max, unsigned char,       UCHAR_MAX);
_PVC_ENCODE(max, short,                SHRT_MAX);
_PVC_ENCODE(max, unsigned short,      USHRT_MAX);
_PVC_ENCODE(max, int,                   INT_MAX);
_PVC_ENCODE(max, unsigned int,         UINT_MAX);
_PVC_ENCODE(max, long,                 LONG_MAX);
_PVC_ENCODE(max, unsigned long,       ULONG_MAX);
_PVC_ENCODE(max, long long,           LLONG_MAX);
_PVC_ENCODE(max, unsigned long long, ULLONG_MAX);
_PVC_ENCODE(max, float,             PVC_FLT_INF);
_PVC_ENCODE(max, double,            PVC_DBL_INF);
_PVC_ENCODE(max, long double,      PVC_LDBL_INF);

#undef _PVC_ENCODE

#else /* not C++ */

#define pvc_type_min(x)                                         \
    _Generic((x),                                               \
             bool:               false,                         \
             char:               (char)CHAR_MIN,                \
             signed char:        (signed char)SCHAR_MIN,        \
             unsigned char:      (unsigned char)0,              \
             short:              (short)SHRT_MIN,               \
             unsigned short:     (unsigned short)0,             \
             int:                (int)INT_MIN,                  \
             unsigned int:       (unsigned int)0,               \
             long:               (long)LONG_MIN,                \
             unsigned long:      (unsigned long)0,              \
             long long:          (long long)LLONG_MIN,          \
             unsigned long long: (unsigned long long)0,         \
             float:              -PVC_FLT_INF,                  \
             double:             -PVC_DBL_INF,                  \
             long double:        -PVC_LDBL_INF)

#define pvc_type_max(x)                                                 \
    _Generic((x),                                                       \
             bool:               true,                                  \
             char:               (char)CHAR_MAX,                        \
             signed char:        (signed char)SCHAR_MAX,                \
             unsigned char:      (unsigned char)UCHAR_MAX,              \
             short:              (short)SHRT_MAX,                       \
             unsigned short:     (unsigned short)USHRT_MAX,             \
             int:                (int)INT_MAX,                          \
             unsigned int:       (unsigned int)UINT_MAX,                \
             long:               (long)LONG_MAX,                        \
             unsigned long:      (unsigned long)ULONG_MAX,              \
             long long:          (long long)LLONG_MAX,                  \
             unsigned long long: (unsigned long long)ULLONG_MAX,        \
             float:              PVC_FLT_INF,                           \
             double:             PVC_DBL_INF,                           \
             long double:        PVC_LDBL_INF)

#endif /* C or C++ */
#endif /* not Doxygen */

/**
 * @}
 */

#endif /* _PVC_TYPES_H */
