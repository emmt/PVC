/*
 * pvc-math.h -
 *
 * Inline version of simple math functions.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PVC_MATH_H
#define _PVC_MATH_H 1

#include <pvc-types.h>

/**
 * @addtogroup math Simple math functions.
 *
 * PVC provides in-lined code simple math functions like pvc_min(),
 * pvc_max() or pvc_clamp().
 *
 * @{
 */

/* Protect against someone else defining private symbols. */
#if defined(_pvc_arg1) || defined(_pvc_arg2) || defined(_pvc_arg3)
#  error "Macros _pvc_argN (with N integer) must not be defined."
#endif

#ifndef _PVC_DOXYGEN_PARSING

#define _PVC_GENERIC_MATH_1(pfx, x)             \
    _Generic((x),                               \
             _Bool:              pfx##_b,       \
             char:               pfx##_c,       \
             signed char:        pfx##_sc,      \
             unsigned char:      pfx##_uc,      \
             short:              pfx##_s,       \
             unsigned short:     pfx##_us,      \
             int:                pfx##_i,       \
             unsigned int:       pfx##_ui,      \
             long:               pfx##_l,       \
             unsigned long:      pfx##_ul,      \
             long long:          pfx##_ll,      \
             unsigned long long: pfx##_ull,     \
             float:              pfx##_f,       \
             double:             pfx##_d,       \
             long double:        pfx##_q)(x)

#define _PVC_GENERIC_MATH_2(pfx, x, y)          \
    _Generic((x) + (y),                         \
             _Bool:              pfx##_b,       \
             char:               pfx##_c,       \
             signed char:        pfx##_sc,      \
             unsigned char:      pfx##_uc,      \
             short:              pfx##_s,       \
             unsigned short:     pfx##_us,      \
             int:                pfx##_i,       \
             unsigned int:       pfx##_ui,      \
             long:               pfx##_l,       \
             unsigned long:      pfx##_ul,      \
             long long:          pfx##_ll,      \
             unsigned long long: pfx##_ull,     \
             float:              pfx##_f,       \
             double:             pfx##_d,       \
             long double:        pfx##_q)(x, y)

#define _PVC_GENERIC_MATH_3(pfx, x, y, z)               \
    _Generic((x) + (y) + (z),                           \
             _Bool:              pfx##_b,               \
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
             long double:        pfx##_q)(x, y, z)

#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @def pvc_min(x, y)
 *
 * @brief Get minimum value.
 *
 * The macro `pvc_min` yields the smallest value of its arguments.
 *
 * This macro expands as inlined code which is intended to be as fast
 * as possible.  Arguments are evaluated once and must have numerical
 * values.  NaN are ignored.
 *
 * @see pvc_max, pvc_clamp.
 */
#ifdef _PVC_DOXYGEN_PARSING

#define pvc_min(x, y) ...

#else /* _PVC_DOXYGEN_PARSING not defined */

#define pvc_min(x, y) _PVC_GENERIC_MATH_2(_pvc_min2, x, y)


static inline _pvc_min2_b(_Bool _pvc_arg1, _Bool _pvc_arg2)
{
    return _pvc_arg1 & _pvc_arg2;
}

/* Define a bunch of (temporary and private) macros to encode the
   variants of the function. */
#define __PVC_STATIC_INLINE(T, func)                            \
    static inline T func(T _pvc_arg1, T _pvc_arg2)              \
    {                                                           \
        return _pvc_arg1 < _pvc_arg2 ? _pvc_arg1 : _pvc_arg2;   \
    }
#define  _PVC_STATIC_INLINE(sfx) \
    __PVC_STATIC_INLINE(PVC_SUFFIX_TO_TYPE(sfx), _pvc_min2_##sfx)

/* Encode all versions. */
_PVC_STATIC_INLINE(c)
_PVC_STATIC_INLINE(sc)
_PVC_STATIC_INLINE(uc)
_PVC_STATIC_INLINE(s)
_PVC_STATIC_INLINE(us)
_PVC_STATIC_INLINE(i)
_PVC_STATIC_INLINE(ui)
_PVC_STATIC_INLINE(l)
_PVC_STATIC_INLINE(ul)
_PVC_STATIC_INLINE(ll)
_PVC_STATIC_INLINE(ull)
_PVC_STATIC_INLINE(f)
_PVC_STATIC_INLINE(d)
_PVC_STATIC_INLINE(q)

/* Undefine temporary private macros. */
#undef  _PVC_STATIC_INLINE
#undef __PVC_STATIC_INLINE

#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @def pvc_max(x, y)
 *
 * @brief Get maximum value.
 *
 * The macro `pvc_max` yields the largest value of its arguments.
 *
 * This macro expands as inlined code which is intended to be as fast
 * as possible.  Arguments are evaluated once and must have numerical
 * values.  NaN are ignored.
 *
 * @see pvc_min, pvc_clamp.
 */
#ifdef _PVC_DOXYGEN_PARSING

#define pvc_max(x, y) ...

#else /* _PVC_DOXYGEN_PARSING not defined */

#define pvc_max(x, y) _PVC_GENERIC_MATH_2(_pvc_max2, x, y)

static inline _pvc_max2_b(_Bool _pvc_arg1, _Bool _pvc_arg2)
{
    return _pvc_arg1 | _pvc_arg2;
}

/* Define a bunch of (temporary and private) macros to encode the
   variants of the function. */
#define __PVC_STATIC_INLINE(T, func)                            \
    static inline T func(T _pvc_arg1, T _pvc_arg2)              \
    {                                                           \
        return _pvc_arg1 > _pvc_arg2 ? _pvc_arg1 : _pvc_arg2;   \
    }
#define  _PVC_STATIC_INLINE(sfx) \
    __PVC_STATIC_INLINE(PVC_SUFFIX_TO_TYPE(sfx), _pvc_max2_##sfx)

/* Encode all versions. */
_PVC_STATIC_INLINE(c)
_PVC_STATIC_INLINE(sc)
_PVC_STATIC_INLINE(uc)
_PVC_STATIC_INLINE(s)
_PVC_STATIC_INLINE(us)
_PVC_STATIC_INLINE(i)
_PVC_STATIC_INLINE(ui)
_PVC_STATIC_INLINE(l)
_PVC_STATIC_INLINE(ul)
_PVC_STATIC_INLINE(ll)
_PVC_STATIC_INLINE(ull)
_PVC_STATIC_INLINE(f)
_PVC_STATIC_INLINE(d)
_PVC_STATIC_INLINE(q)

/* Undefine temporary private macros. */
#undef  _PVC_STATIC_INLINE
#undef __PVC_STATIC_INLINE

#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @def pvc_clamp(x, lo, hi)
 *
 * @brief Clamp a value within given bounds.
 *
 * This macro yields `min(max(x, lo), hi)` that is `lo` if `x ≤ lo`,
 * `hi` if `x ≥ hi` and `x` otherwise.
 *
 * This macro expands as inlined code which is intended to be as fast
 * as possible.  Arguments are evaluated once and must have numerical
 * values.  Arguments are not checked (@a hi should be greater or
 * equal @a lo) and NaN may not propagate properly.
 *
 * @see pvc_min, pvc_max.
 */
#ifdef _PVC_DOXYGEN_PARSING

#define pvc_clamp(x, lo, hi) ...

#else /* _PVC_DOXYGEN_PARSING not defined */

#define pvc_clamp(x, lo, hi) _PVC_GENERIC_MATH_3(_pvc_clamp, x, lo, hi)

static inline _pvc_clamp_b(_Bool _pvc_arg1, _Bool _pvc_arg2, _Bool _pvc_arg3)
{
    /* Cannot be just arg1 because arg2 and arg3 may be the same. */
    return (_pvc_arg1 | _pvc_arg2) & _pvc_arg3;
}

/* Define a bunch of temporary and private macros to encode the
   variants of the function. */
#define __PVC_STATIC_INLINE(T, clamp, min, max)                         \
    static inline T clamp(T _pvc_arg1, T _pvc_arg2, T _pvc_arg3)        \
    {                                                                   \
        return min(max(_pvc_arg1, _pvc_arg2), _pvc_arg3);               \
    }
#define  _PVC_STATIC_INLINE(sfx)                        \
    __PVC_STATIC_INLINE(PVC_SUFFIX_TO_TYPE(sfx),        \
                        _pvc_clamp_##sfx,               \
                        _pvc_min2_##sfx,                \
                        _pvc_max2_##sfx)

/* Encode all versions. */
_PVC_STATIC_INLINE(c)
_PVC_STATIC_INLINE(sc)
_PVC_STATIC_INLINE(uc)
_PVC_STATIC_INLINE(s)
_PVC_STATIC_INLINE(us)
_PVC_STATIC_INLINE(i)
_PVC_STATIC_INLINE(ui)
_PVC_STATIC_INLINE(l)
_PVC_STATIC_INLINE(ul)
_PVC_STATIC_INLINE(ll)
_PVC_STATIC_INLINE(ull)
_PVC_STATIC_INLINE(f)
_PVC_STATIC_INLINE(d)
_PVC_STATIC_INLINE(q)

/* Undefine temporary private macros. */
#undef  _PVC_STATIC_INLINE
#undef __PVC_STATIC_INLINE

#endif /* _PVC_DOXYGEN_PARSING */

/**
 * @}
 */

#endif /* _PVC_MATH_H */
