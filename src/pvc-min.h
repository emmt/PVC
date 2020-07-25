/*
 * pvc-min.h -
 *
 * Inline version of the min function.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PVC_MIN_H
#define _PVC_MIN_H 1

#include <pvc.h>

/* Protect against someone else defining private symbols. */
#if defined(_pvc_arg1) || defined(_pvc_arg2)
#  error "Macros _pvc_argN (with N integer) must not be defined."
#endif

/**
 * @def pvc_min(x, y)
 *
 * @brief Get minimum value.
 *
 * The macro `pvc_min` yields the smallest value of its arguments.
 *
 * This macro uses inlined code and is intended to be as fast as
 * possible.  Arguments are evaluated once and must have numerical
 * values.  NaN are ignored.
 *
 * @see pvc_max, pcv_clamp.
 */
#define pvc_min(x, y) _PVC_GENERIC_NUMERICAL_CALL_2(_pvc_min2, x, y)

/* Define a bunch of (temporary and private) macros to encode the
   variants of the function. */
#define __PVC_STATIC_INLINE(T, func)                            \
    static inline T func(T _pvc_arg1, T _pvc_arg2) {            \
        return _pvc_arg1 < _pvc_arg2 ? _pvc_arg1 : _pvc_arg2;   \
    }
#define  _PVC_STATIC_INLINE(sfx) \
    __PVC_STATIC_INLINE(PVC_SUFFIX_TO_CTYPE(sfx), _pvc_min2_##sfx)

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

#endif /* _PVC_MIN_H */
