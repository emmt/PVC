/*
 * pvc-clamp.h -
 *
 * Inline version of the clamp function.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PVC_CLAMP_H
#define _PVC_CLAMP_H 1

#include <pvc.h>
#include <pvc-min.h>
#include <pvc-max.h>

/* Protect against someone else defining private symbols. */
#if defined(_pvc_arg1) || defined(_pvc_arg2) || defined(_pvc_arg3)
#  error "Macros _pvc_argN (with N integer) must not be defined."
#endif

/**
 * @def pvc_clamp(x, lo, hi)
 *
 * @brief Clamp a value within given bounds.
 *
 * This macro yields `min(max(x, lo), hi)` that is `lo` if `x ≤ lo`,
 * `hi` if `x ≥ hi` and `x` otherwise.
 *
 * This macro uses inlined code and is intended to be as fast as
 * possible.  Arguments are evaluated once and must have numerical
 * values.  Arguments are not checked (@a hi should be greater or
 * equal @a lo) and NaN may not propagate properly.
 *
 * @see pcv_min, pvc_max.
 */
#define pvc_clamp(x, lo, hi) \
    _PVC_GENERIC_NUMERICAL_CALL_3(_pvc_clamp, x, lo, hi)

/* Define a bunch of temporary and private macros to encode the
   variants of the function. */
#define __PVC_STATIC_INLINE(T, clamp, min, max)                         \
    static inline T clamp(T _pvc_arg1, T _pvc_arg2, T _pvc_arg3) {      \
        return min(max(_pvc_arg1, _pvc_arg2),  _pvc_arg3);              \
    }
#define  _PVC_STATIC_INLINE(sfx)                        \
    __PVC_STATIC_INLINE(PVC_SUFFIX_TO_CTYPE(sfx),       \
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

#endif /* _PVC_CLAMP_H */
