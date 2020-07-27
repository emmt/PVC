/*
 * pvc-types.h -
 *
 * Definitions for basic types in PVC library.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PVC_TYPES_H
#define _PVC_TYPES_H 1

#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <pvc.h>

/**
 * @addtogroup types Basic types.
 *
 * Basic types are the 15 basic numerical types implemented by the C
 * language: `bool`, `char`, `signed char`, `unsigned char`, `short`,
 * `unsigned short`, `int`, `unsigned int`, `long`, `unsigned long`,
 * `long long`, `unsigned long long`, `float`, `double` and `long
 * double`.
 *
 * In standard C, `char`, `signed char` and `unsigned char` are
 * distinct types.  For other integer types `signed` is implicit if
 * neither `signed` nor `unsigned` is specified.
 *
 * To each basic type, PVC associate a unique numerical identifier
 * (see PVC_TYPE_ID()) and a unique suffix (see PVC_SUFFIX_TO_TYPE())
 * which can both be determined at compile-time.  These can be used
 * for simple type-oriented meta-programming.  For instannce, The
 * identifier may be used to build a type-indexed table while the
 * suffix may be used to name type-specific functions and to allow for
 * simple type dispatching (like the functions in `<math.h>` since
 * C99).
 *
 * @{
 */

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
 * |    `q` | `long double`        |
 *
 * Note that `char`, `signed char` and `unsigned char` are distinct
 * types in C.  Macro expansion is performed on argument @a sfx, call
 * `_PVC_SUFFIX_TO_TYPE_(sfx)` instead if you do not want to expand
 * argument.
 *
 * Other suffixes, say `x`, may be inserted by defining a macro
 * `_PVC_SUFFIX_TO_TYPE_x` which expands to the corresponding C type.
 */
/* The trick is to define macro `_PVC_SUFFIX_TO_TYPE_(sfx)` such that
   it uses 2 tokens `_PVC_SUFFIX_TO_TYPE_` which is not expanded as it
   is the name of the macro and `sfx` which is just replaced by its
   value.  In that way there are less risks that macro expansion yield
   unpredictable result (the compiler will complain if the macor is
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
#  define _PVC_SUFFIX_TO_TYPE_q     long double
#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @def PVC_TYPE_ID(T)
 *
 * @brief Unique basic type identifier.
 *
 * This macro expands to an integer compile-time constant expression
 * with the unique identifier of the basic type @ T or
 * `PVC_TYPE_ID_OTHER` (that is 0) if @a T is not a basic type.  Type
 * qualifiers are irrelevant.
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
 */
#ifdef _PVC_DOXYGEN_PARSING

#  define PVC_TYPE_ID(T) ...

#else /* _PVC_DOXYGEN_PARSING not defined */

/* To discard any type qualifiers such as `const or `volatile`, the
   trick used in `PVC_TYPE_ID` and similar macros using type generic
   expression is to use the type of dereferencing a null pointer to
   the considered type.  This is allowed because the controlling
   expression in a type generic construction is not evaluated by the
   compiler, only its type is relevant. */
#  define PVC_TYPE_ID(T)                                                \
    _Generic(*(T*)0,                                                    \
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

#endif /* _PVC_DOXYGEN_PARSING */

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
#define PVC_TYPE_ID_MIN                 PVC_TYPE_ID_OTHER
#define PVC_TYPE_ID_MAX                 PVC_TYPE_ID_LONG_DOUBLE

/**
 * @def PVC_IS_SIGNED(T)
 *
 * @brief Checking for signed numerical type.
 *
 * This macro expands to a boolean compile-time constant expression
 * indicating whether its argument is a signed numerical type.  This macro
 * should always compile, yielding false for unsigned numerical types or
 * non-numerical type.
 *
 * @see PVC_IS_UNSIGNED, PVC_IS_INTEGER, PVC_IS_FLOATINGPOINT.
 */
/**
 * @def PVC_IS_UNSIGNED(T)
 *
 * @brief Checking for unsigned numerical type.
 *
 * This macro expands to a boolean compile-time constant expression
 * indicating whether its argument is an unsigned numerical type.  This
 * macro should always compile, yielding false for signed numerical types
 * and non-numerical types.
 *
 * @see PVC_IS_SIGNED, PVC_IS_INTEGER, PVC_IS_FLOATINGPOINT.
 */
#ifdef _PVC_DOXYGEN_PARSING

#  define PVC_IS_SIGNED(T) ...
#  define PVC_IS_UNSIGNED(T) ...

#else /* _PVC_DOXYGEN_PARSING not defined */

#  define PVC_IS_SIGNED(T)                      \
    _Generic(*(T*)0,                            \
             char:        (char)-1 < 0,         \
             signed char: true,                 \
             short:       true,                 \
             int:         true,                 \
             long:        true,                 \
             long long:   true,                 \
             float:       true,                 \
             double:      true,                 \
             long double: true,                 \
             default:     false)

#  define PVC_IS_UNSIGNED(T)                    \
    _Generic(*(T*)0,                            \
             bool:               true,          \
             char:               (char)-1 > 0,  \
             unsigned char:      true,          \
             unsigned short:     true,          \
             unsigned int:       true,          \
             unsigned long:      true,          \
             unsigned long long: true,          \
             default:            false)

#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @def PVC_IS_INTEGER(T)
 *
 * @brief Checking for integer numerical type.
 *
 * This macro expands to a boolean compile-time constant expression
 * indicating whether its argument is an integer numerical type.  This
 * macro should always compile, yielding false for non-integer numerical
 * types or non-numerical type.
 *
 * @see PVC_IS_UNSIGNED, PVC_IS_SIGNED, PVC_IS_FLOATINGPOINT.
 */
/**
 * @def PVC_IS_FLOATINGPOINT(T)
 *
 * @brief Checking for floating point type.
 *
 * This macro expands to a boolean compile-time constant expression
 * indicating whether its argument is a floating-point type.  This macro
 * should always compile, yielding false for non floating-point numerical
 * types or non-numerical type.
 *
 * @see PVC_IS_UNSIGNED, PVC_IS_SIGNED, PVC_IS_INTEGER.
 */
#ifdef _PVC_DOXYGEN_PARSING

#  define PVC_IS_INTEGER(T) ...
#  define PVC_IS_FLOATINGPOINT(T) ...

#else /* _PVC_DOXYGEN_PARSING not defined */

#  define PVC_IS_INTEGER(T)                     \
    _Generic(*(T*)0,                            \
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

#  define PVC_IS_FLOATINGPOINT(T)               \
    _Generic(*(T*)0,                            \
             float:       true,                 \
             double:      true,                 \
             long double: true,                 \
             default:     false)

#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @def PVC_QUALIFIED_TYPE_IS(T, Q)
 *
 * @brief Checking for qualified type equality.
 *
 * This macro expands to a boolean compile-time constant expression
 * indicating whether qualified types @a T and @a Q are the same.
 *
 * Note that type equality is actually checked for the types of the
 * pointers `(T*)0` and `(Q*)0`.  As a consequece, type qualifiers
 * such as `const` and `volatile` are significant.  Use
 * PVC_UNQUALIFIED_TYPE_IS() if you want to check the unqualified
 * type.
 *
 * @see PVC_IS_FLOATINGPOINT, PVC_IS_INTEGER, PVC_UNQUALIFIED_TYPE_IS.
 */
#define PVC_QUALIFIED_TYPE_IS(T, Q)  _Generic((T*)0, Q*: true, default: false)

/**
 * @def PVC_UNQUALIFIED_TYPE_IS(T, U)
 *
 * @brief Checking for unqualifed type equality.
 *
 * This macro expands to a boolean compile-time constant expression
 * indicating whether unqualified type @a T is the same as @a B.
 * Argument @a T may have type qualifiers, argument @a U should be
 * unqualified.
 *
 * Use PVC_QUALIFIED_TYPE_IS() if you want to check the qualified type.
 *
 * @see PVC_IS_FLOATINGPOINT, PVC_IS_INTEGER, PVC_QUALIFIED_TYPE_IS.
 */
#define PVC_UNQUALIFIED_TYPE_IS(T, U) _Generic(*(T*)0, U: true, default: false)

#define PVC_IS_BOOL(T) PVC_UNQUALIFIED_TYPE_IS(T, bool)

#define PVC_IS_CHAR(T)          PVC_UNQUALIFIED_TYPE_IS(T, char)
#define PVC_IS_SIGNED_CHAR(T)   PVC_UNQUALIFIED_TYPE_IS(T, signed char)
#define PVC_IS_UNSIGNED_CHAR(T) PVC_UNQUALIFIED_TYPE_IS(T, unsigned char)

#define PVC_IS_SHORT(T)          PVC_UNQUALIFIED_TYPE_IS(T, short)
#define PVC_IS_SIGNED_SHORT(T)   PVC_UNQUALIFIED_TYPE_IS(T, signed short)
#define PVC_IS_UNSIGNED_SHORT(T) PVC_UNQUALIFIED_TYPE_IS(T, unsigned short)

#define PVC_IS_INT(T)          PVC_UNQUALIFIED_TYPE_IS(T, int)
#define PVC_IS_SIGNED_INT(T)   PVC_UNQUALIFIED_TYPE_IS(T, signed int)
#define PVC_IS_UNSIGNED_INT(T) PVC_UNQUALIFIED_TYPE_IS(T, unsigned int)

#define PVC_IS_LONG(T)           PVC_UNQUALIFIED_TYPE_IS(T, long)
#define PVC_IS_SIGNED_LONG(T)    PVC_UNQUALIFIED_TYPE_IS(T, signed long)
#define PVC_IS_UNSIGNED_LONG(T)  PVC_UNQUALIFIED_TYPE_IS(T, unsigned long)

#define PVC_IS_LONG_LONG(T)          PVC_UNQUALIFIED_TYPE_IS(T, long long)
#define PVC_IS_SIGNED_LONG_LONG(T)   PVC_UNQUALIFIED_TYPE_IS(T, signed long long)
#define PVC_IS_UNSIGNED_LONG_LONG(T) PVC_UNQUALIFIED_TYPE_IS(T, unsigned long long)

#define PVC_IS_FLOAT(T)       PVC_UNQUALIFIED_TYPE_IS(T, float)
#define PVC_IS_DOUBLE(T)      PVC_UNQUALIFIED_TYPE_IS(T, double)
#define PVC_IS_LONG_DOUBLE(T) PVC_UNQUALIFIED_TYPE_IS(T, long double)

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
/* Since C99, the macro `INFINITY`, defined in `<math.h>`, expands to
   a constant expression of type float which evaluates to positive or
   unsigned infinity.

   Since C99, the macros `HUGE_VALF`, `HUGE_VAL` and `HUGE_VALL`,
   defined in `<math.h>`, expand to positive floating point constant
   expressions which compare equal to the values returned by
   floating-point functions and operators in case of overflow.

   See <https://en.cppreference.com/w/c>.
 */
#ifdef _PVC_DOXYGEN_PARSING
#  define PVC_FLT_INF  ...
#  define PVC_LDBL_INF ...
#  define PVC_DBL_INF  ...
#else /* _PVC_DOXYGEN_PARSING not defined */
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
#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @def PVC_FLT_NAN
 *
 * @brief Single precision quiet not-a-number.
 *
 * If defined, this macro expands to a compile-time constant
 * expression of type `float` which evaluates to a quiet not-a-number
 * (QNaN).
 *
 * @see PVC_DBL_NAN, PVC_LDBL_NAN.
 */
/**
 * @def PVC_DBL_NAN
 *
 * @brief Double precision quiet not-a-number.
 *
 * If defined, this macro expands to a compile-time constant
 * expression of type `double` which evaluates to a quiet not-a-number
 * (QNaN).
 *
 * @see PVC_FLT_NAN, PVC_LDBL_NAN.
 */
/**
 * @def PVC_LDBL_NAN
 *
 * @brief Quadruple precision quiet not-a-number.
 *
 * If defined, this macro expands to a compile-time constant
 * expression of type `long double` which evaluates to a quiet
 * not-a-number (QNaN).
 *
 * @see PVC_FLT_NAN, PVC_DBL_NAN.
 */
#ifdef _PVC_DOXYGEN_PARSING
#  define PVC_FLT_NAN  ...
#  define PVC_DBL_NAN  ...
#  define PVC_LDBL_NAN ...
#else /* _PVC_DOXYGEN_PARSING not defined */
/* Since C99, the macro `NAN`, defined in `<math.h>`, expands a to
   constant expression of type float which evaluates to a quiet
   not-a-number (QNaN) value.  If the implementation does not support
   QNaNs, this macro constant is not defined.

   See <https://en.cppreference.com/w/c>.
 */
#  ifdef NAN
#    define PVC_FLT_NAN  ((float)NAN)
#    define PVC_DBL_NAN  ((double)NAN)
#    define PVC_LDBL_NAN ((long double)NAN)
#  else
#    define PVC_FLT_NAN  (1.0f/0.0f)
#    define PVC_DBL_NAN  (1.0/0.0)
#    define PVC_LDBL_NAN (1.0L/0.0L)
#  endif
#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @def PVC_TYPE_MIN(T)
 *
 * @brief Minimum value of given type.
 *
 * This macro expands to a compile-time constant expression of type
 * @a T which evaluates to the minimal representable value for type
 * @a T, that is minus infinity for floating-point types.
 *
 * @see PVC_TYPE_MAX.
 */
/**
 * @def PVC_TYPE_MAX(T)
 *
 * @brief Maximum value of given type.
 *
 * This macro expands to a compile-time constant expression of type
 * @a T which evaluates to the maximal representable value for type
 * @a T, that is plus infinity for floating-point types.
 *
 * @see PVC_TYPE_MIN.
 */
#ifdef _PVC_DOXYGEN_PARSING

#  define PVC_TYPE_MIN(T) ...
#  define PVC_TYPE_MAX(T) ...

#else /* _PVC_DOXYGEN_PARSING not defined */

#  define PVC_TYPE_MIN(T)                                       \
    _Generic(*(T*)0,                                            \
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

#  define PVC_TYPE_MAX(T)                                               \
    _Generic(*(T*)0,                                                    \
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

#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @}
 */

#endif /* _PVC_TYPES_H */
