/*
 * vdot.c -
 *
 * Implementation of dot product.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PVC_VDOT_C
#define _PVC_VDOT_C 1

#include <stdio.h>

// Loop unrolling is needed for reduction operations because of the
// augmented latency due to "loop-carried dependency chain".
#ifndef VDOT_UNROLL
#  define VDOT_UNROLL 4
#endif
#ifndef VDOT3_UNROLL
#  define VDOT3_UNROLL 2
#endif

#include "pvc.h"
#include "pvc-meta.h"

// Macro to indicate 64 bit mode
#if defined(__x86_64__)
#  define PVC_X86_64 __x86_64__
#elif (defined(_M_AMD64) || defined(_M_X64) || defined(__amd64))
#  define PVC_X86_64 1
#endif


#define TYPE float
#include __FILE__

#define TYPE double
#include __FILE__

#else /* _PVC_VDOT_C */

#define IS_SINGLE PVC_IS_SINGLE(TYPE)
#if IS_SINGLE
#  define SUFFIX            f
#  define PTR_TO_NELEM(ptr) (PVC_POINTER_TO_INTEGER(ptr) >> 2)
#else
#  define SUFFIX            d
#  define PTR_TO_NELEM(ptr) (PVC_POINTER_TO_INTEGER(ptr) >> 3)
#endif

#ifdef DISPATCH

/* Code for reference implementation and dispatcher. */

#undef  VECT

#define DISPATCH_DOT_FUNC  PVC_PASTE(dispatch_dot_,SUFFIX)
#define DOT_FUNC           PVC_PASTE(pvc_dot_,SUFFIX)
#define VDOT               PVC_PASTE(pvc_dot_,SUFFIX,_ref)

static TYPE DISPATCH_DOT_FUNC(size_t n,
                              TYPE const* restrict x,
                              TYPE const* restrict y);

TYPE (*DOT_FUNC)(size_t n,
                 TYPE const* restrict x,
                 TYPE const* restrict y) = DISPATCH_DOT_FUNC;

static TYPE DISPATCH_DOT_FUNC(size_t n,
                              TYPE const* restrict x,
                              TYPE const* restrict y)
{

    int instrset = pvc_instrset();
    fprintf(stderr, "Instruction set: %d\n", instrset);
    switch (instrset) {
#define CASE(lvl) case lvl: DOT_FUNC = PVC_PASTE(DOT_FUNC,_,lvl); break
        CASE(2);
        CASE(3);
        CASE(4);
        CASE(5);
        CASE(6);
        CASE(7);
        CASE(8);
        CASE(9);
        CASE(10);
#undef CASE
    default:
        DOT_FUNC = VDOT;
    }
    return DOT_FUNC(n, x, y);
}

#undef DISPATCH_DOT_FUNC
#undef DOT_FUNC

#define DISPATCH_DOT3_FUNC PVC_PASTE(dispatch_dot3_,SUFFIX)
#define DOT3_FUNC          PVC_PASTE(pvc_dot3_,SUFFIX)
#define VDOT3              PVC_PASTE(pvc_dot3_,SUFFIX,_ref)

static TYPE DISPATCH_DOT3_FUNC(size_t n,
                               TYPE const* restrict w,
                               TYPE const* restrict x,
                               TYPE const* restrict y);

TYPE (*DOT3_FUNC)(size_t n,
                  TYPE const* restrict w,
                  TYPE const* restrict x,
                  TYPE const* restrict y) = DISPATCH_DOT3_FUNC;

static TYPE DISPATCH_DOT3_FUNC(size_t n,
                               TYPE const* restrict w,
                               TYPE const* restrict x,
                               TYPE const* restrict y)
{

    int instrset = pvc_instrset();
    fprintf(stderr, "Instruction set: %d\n", instrset);
    switch (instrset) {
#define CASE(lvl) case lvl: DOT3_FUNC = PVC_PASTE(DOT3_FUNC,_,lvl); break
        CASE(2);
        CASE(3);
        CASE(4);
        CASE(5);
        CASE(6);
        CASE(7);
        CASE(8);
        CASE(9);
        CASE(10);
#undef CASE
    default:
        DOT3_FUNC = VDOT3;
    }
    return DOT3_FUNC(n, w, x, y);
}

#undef DISPATCH_DOT3_FUNC
#undef DOT3_FUNC

#else /* not DISPATCH */

/* Code for reference implementation and dispatcher. */

//#define VCL_NAMESPACE vcl
#include "vectorclass.h"

// Number of SIMD registers.
#if INSTRSET == 2
#  define NREGS 8
#elif INSTRSET >= 3 && INSTRSET <= 6
#  if !defined(PVC_X86_64) || PVC_X86_64 == 0
#    define NREGS 8
#  else
#    define NREGS 16
#  endif
#else
#  define NREGS 16
#endif

// NBITS = number of bits per SIMD vector
// NELEM = number of elements per SIMD vector
#if 2 <= INSTRSET && INSTRSET <= 6
#  define NBITS     128
#  if IS_SINGLE
#    define NELEM     4
#  else
#    define NELEM     2
#  endif
#elif 7 <= INSTRSET && INSTRSET <= 8
#  define NBITS     256
#  if IS_SINGLE
#    define NELEM     8
#  else
#    define NELEM     4
#  endif
#elif 9 <= INSTRSET && INSTRSET <= 10
#  define NBITS     512
#  if IS_SINGLE
#    define NELEM    16
#  else
#    define NELEM     8
#  endif
#else
#  error Invalid value for INSTRSET
#endif

#define VECT   PVC_PASTE(Vec,NELEM,SUFFIX)
#define VDOT   PVC_PASTE(pvc_dot_,SUFFIX,_,INSTRSET)
#define VDOT3  PVC_PASTE(pvc_dot3_,SUFFIX,_,INSTRSET)
#define NBYTES    (NBITS >> 3)

#endif  /* not DISPATCH */

#if VDOT_UNROLL < 1 || VDOT_UNROLL > 6
#  error "Invalid value for macro VDOT_UNROLL (should be between 1 and 6)."
#endif

#define VDOT_INIT(j,load)                       \
    x##j.load(X + i);                           \
    y##j.load(Y + i);                           \
    sum##j = x##j*y##j; /* sumj = xj*yj */      \
    i += NELEM

#define VDOT_INCR(j,load)                                       \
    x##j.load(X + i);                                           \
    y##j.load(Y + i);                                           \
    sum##j = mul_add(x##j, y##j, sum##j); /* sumj += xj*yj */   \
    i += NELEM

TYPE
VDOT(size_t n,
     TYPE const* restrict X,
     TYPE const* restrict Y)
{
#ifndef VECT
    /* Non-vectorized (reference) code. */
    TYPE res = 0;
    for (size_t i = 0; i < n; ++i) {
        res += X[i]*Y[i];
    }
    return res;
#else /* VECT */
    /* Vectorized code. */
    if (n <= NELEM) {
        /* Keep code simple for very small arrays but do not write simple
           loops to avoid optimizer vectorization. */
        int p = n;
        switch (p) {
        case 0:
            return (TYPE)0;
        case 1:
            return X[0]*Y[0];
#  if NELEM > 2
        case 2:
            return X[0]*Y[0] + X[1]*Y[1];
#  endif
        case NELEM:
            return horizontal_add(VECT().load(X)*
                                  VECT().load(Y));
        default:
            return horizontal_add(VECT().load_partial(p, X)*
                                  VECT().load_partial(p, Y));
        }
#  if VDOT_UNROLL > 1
    } else if (n >= VDOT_UNROLL*NELEM) {
        /* Vectorized code with loop unrolling. */
        VECT sum1, x1, y1;
#    if VDOT_UNROLL >= 2
        VECT sum2, x2, y2;
#    endif
#    if VDOT_UNROLL >= 3
        VECT sum3, x3, y3;
#    endif
#    if VDOT_UNROLL >= 4
        VECT sum4, x4, y4;
#    endif
#    if VDOT_UNROLL >= 5
        VECT sum5, x5, y5;
#    endif
#    if VDOT_UNROLL >= 6
        VECT sum6, x6, y6;
#    endif
        size_t imax = n - NELEM;
        size_t i;
        size_t ix = PTR_TO_NELEM(X) & (NELEM - 1);
        size_t iy = PTR_TO_NELEM(Y) & (NELEM - 1);
        if (ix == iy) {
            /* Arrays can be aligned. */
            if (ix == 0) {
                x1.load_a(X);
                y1.load_a(Y);
                i = NELEM;
            } else {
                int p = ix;
                x1.load_partial(p, X);
                y1.load_partial(p, Y);
                i = ix;
            }
            sum1 = x1*y1;
#    if VDOT_UNROLL >= 2
            VDOT_INIT(2, load_a);
#    endif
#    if VDOT_UNROLL >= 3
            VDOT_INIT(3, load_a);
#    endif
#    if VDOT_UNROLL >= 4
            VDOT_INIT(4, load_a);
#    endif
#    if VDOT_UNROLL >= 5
            VDOT_INIT(5, load_a);
#    endif
#    if VDOT_UNROLL >= 6
            VDOT_INIT(6, load_a);
#    endif
            while (i <= imax) {
                VDOT_INCR(1, load_a);
#    if VDOT_UNROLL >= 2
                if (i > imax) break;
                VDOT_INCR(2, load_a);
#    endif
#    if VDOT_UNROLL >= 3
                if (i > imax) break;
                VDOT_INCR(3, load_a);
#    endif
#    if VDOT_UNROLL >= 4
                if (i > imax) break;
                VDOT_INCR(4, load_a);
#    endif
#    if VDOT_UNROLL >= 5
                if (i > imax) break;
                VDOT_INCR(5, load_a);
#    endif
#    if VDOT_UNROLL >= 6
                if (i > imax) break;
                VDOT_INCR(6, load_a);
#    endif
            }
        } else {
            /* Array cannot be aligned. */
            i = 0;
            VDOT_INIT(1, load);
#    if VDOT_UNROLL >= 2
            VDOT_INIT(2, load);
#    endif
#    if VDOT_UNROLL >= 3
            VDOT_INIT(3, load);
#    endif
#    if VDOT_UNROLL >= 4
            VDOT_INIT(4, load);
#    endif
#    if VDOT_UNROLL >= 5
            VDOT_INIT(5, load);
#    endif
#    if VDOT_UNROLL >= 6
            VDOT_INIT(6, load);
#    endif
            while (i <= imax) {
                VDOT_INCR(1, load);
#    if VDOT_UNROLL >= 2
                if (i > imax) break;
                VDOT_INCR(2, load);
#    endif
#    if VDOT_UNROLL >= 3
                if (i > imax) break;
                VDOT_INCR(3, load);
#    endif
#    if VDOT_UNROLL >= 4
                if (i > imax) break;
                VDOT_INCR(4, load);
#    endif
#    if VDOT_UNROLL >= 5
                if (i > imax) break;
                VDOT_INCR(5, load);
#    endif
#    if VDOT_UNROLL >= 6
                if (i > imax) break;
                VDOT_INCR(6, load);
#    endif
            }
        }
        if (i < n) {
            /* Remaining elements. */
            int p = n - i;
            x1.load_partial(p, X + i);
            y1.load_partial(p, Y + i);
            sum1 = mul_add(x1, y1, sum1); /* sum1 += x1*y1 */
        }
#    if VDOT_UNROLL >= 6
        return horizontal_add((sum1 + sum2) + (sum3 + sum4) + (sum5 + sum6));
#    elif VDOT_UNROLL >= 5
        return horizontal_add((sum1 + sum2) + (sum3 + sum4) + sum5);
#    elif VDOT_UNROLL >= 4
        return horizontal_add((sum1 + sum2) + (sum3 + sum4));
#    elif VDOT_UNROLL >= 3
        return horizontal_add(sum1 + sum2 + sum3);
#    elif VDOT_UNROLL >= 2
        return horizontal_add(sum1 + sum2);
#    else
        return horizontal_add(sum1);
#    endif
#  endif /* VDOT_UNROLL > 1 */
    } else {
        /* Vectorized code for small arrays or without loop unrolling. */
        VECT sum(0), x, y;
        size_t imax = n - NELEM;
        size_t i = 0;
        while (i <= imax) {
            x.load(X + i);
            y.load(Y + i);
            sum += x*y;
            i += NELEM;
        }
        if (i < n) {
            int p = n - i;
            x.load_partial(p, X + i);
            y.load_partial(p, Y + i);
            sum = mul_add(x, y, sum); /* sum += x*y */
        }
        return horizontal_add(sum);
    }
#endif /* VECT */
}

#if VDOT3_UNROLL < 1 || VDOT3_UNROLL > 6
#  error "Invalid value for macro VDOT3_UNROLL (should be between 1 and 6)."
#endif

#define VDOT3_INIT(j,load)                              \
    w##j.load(W + i);                                   \
    x##j.load(X + i);                                   \
    y##j.load(Y + i);                                   \
    sum##j = w##j*x##j*y##j; /* sumj = wj*xj*yj */      \
    i += NELEM

#define VDOT3_INCR(j,load)                                              \
    w##j.load(W + i);                                                   \
    x##j.load(X + i);                                                   \
    y##j.load(Y + i);                                                   \
    sum##j = mul_add(x##j*x##j, y##j, sum##j); /* sumj += wj*xj*yj */   \
    i += NELEM

TYPE
VDOT3(size_t n,
     TYPE const* restrict W,
     TYPE const* restrict X,
     TYPE const* restrict Y)
{
#ifndef VECT
    /* Non-vectorized (reference) code. */
    TYPE res = 0;
    for (size_t i = 0; i < n; ++i) {
        res += W[i]*X[i]*Y[i];
    }
    return res;
#else /* VECT */
    /* Vectorized code. */
    if (n <= NELEM) {
        /* Keep code simple for very small arrays but do not write simple
           loops to avoid optimizer vectorization. */
        int p = n;
        switch (p) {
        case 0:
            return (TYPE)0;
        case 1:
            return W[0]*X[0]*Y[0];
#  if NELEM > 2
        case 2:
            return W[0]*X[0]*Y[0] + W[1]*X[1]*Y[1];
#  endif
        case NELEM:
            return horizontal_add(VECT().load(W)*
                                  VECT().load(X)*
                                  VECT().load(Y));
        default:
            return horizontal_add(VECT().load_partial(p, W)*
                                  VECT().load_partial(p, X)*
                                  VECT().load_partial(p, Y));
        }
#  if VDOT3_UNROLL > 1
    } else if (n >= VDOT3_UNROLL*NELEM) {
        /* Vectorized code with loop unrolling. */
        VECT sum1, w1, x1, y1;
#    if VDOT3_UNROLL >= 2
        VECT sum2, w2, x2, y2;
#    endif
#    if VDOT3_UNROLL >= 3
        VECT sum3, w3, x3, y3;
#    endif
#    if VDOT3_UNROLL >= 4
        VECT sum4, w4, x4, y4;
#    endif
#    if VDOT3_UNROLL >= 5
        VECT sum5, w5, x5, y5;
#    endif
#    if VDOT3_UNROLL >= 6
        VECT sum6, w6, x6, y6;
#    endif
        size_t imax = n - NELEM;
        size_t i;
        size_t iw = PTR_TO_NELEM(W) & (NELEM - 1);
        size_t ix = PTR_TO_NELEM(X) & (NELEM - 1);
        size_t iy = PTR_TO_NELEM(Y) & (NELEM - 1);
        if (iw == ix && ix == iy) {
            /* Arrays can be aligned. */
            if (ix == 0) {
                w1.load_a(W);
                x1.load_a(X);
                y1.load_a(Y);
                i = NELEM;
            } else {
                int p = ix;
                w1.load_partial(p, W);
                x1.load_partial(p, X);
                y1.load_partial(p, Y);
                i = ix;
            }
            sum1 = w1*x1*y1;
#    if VDOT3_UNROLL >= 2
            VDOT3_INIT(2, load_a);
#    endif
#    if VDOT3_UNROLL >= 3
            VDOT3_INIT(3, load_a);
#    endif
#    if VDOT3_UNROLL >= 4
            VDOT3_INIT(4, load_a);
#    endif
#    if VDOT3_UNROLL >= 5
            VDOT3_INIT(5, load_a);
#    endif
#    if VDOT3_UNROLL >= 6
            VDOT3_INIT(6, load_a);
#    endif
            while (i <= imax) {
                VDOT3_INCR(1, load_a);
#    if VDOT3_UNROLL >= 2
                if (i > imax) break;
                VDOT3_INCR(2, load_a);
#    endif
#    if VDOT3_UNROLL >= 3
                if (i > imax) break;
                VDOT3_INCR(3, load_a);
#    endif
#    if VDOT3_UNROLL >= 4
                if (i > imax) break;
                VDOT3_INCR(4, load_a);
#    endif
#    if VDOT3_UNROLL >= 5
                if (i > imax) break;
                VDOT3_INCR(5, load_a);
#    endif
#    if VDOT3_UNROLL >= 6
                if (i > imax) break;
                VDOT3_INCR(6, load_a);
#    endif
            }
        } else {
            /* Array cannot be aligned. */
            i = 0;
            VDOT3_INIT(1, load);
#    if VDOT3_UNROLL >= 2
            VDOT3_INIT(2, load);
#    endif
#    if VDOT3_UNROLL >= 3
            VDOT3_INIT(3, load);
#    endif
#    if VDOT3_UNROLL >= 4
            VDOT3_INIT(4, load);
#    endif
#    if VDOT3_UNROLL >= 5
            VDOT3_INIT(5, load);
#    endif
#    if VDOT3_UNROLL >= 6
            VDOT3_INIT(6, load);
#    endif
            while (i <= imax) {
                VDOT3_INCR(1, load);
#    if VDOT3_UNROLL >= 2
                if (i > imax) break;
                VDOT3_INCR(2, load);
#    endif
#    if VDOT3_UNROLL >= 3
                if (i > imax) break;
                VDOT3_INCR(3, load);
#    endif
#    if VDOT3_UNROLL >= 4
                if (i > imax) break;
                VDOT3_INCR(4, load);
#    endif
#    if VDOT3_UNROLL >= 5
                if (i > imax) break;
                VDOT3_INCR(5, load);
#    endif
#    if VDOT3_UNROLL >= 6
                if (i > imax) break;
                VDOT3_INCR(6, load);
#    endif
            }
        }
        if (i < n) {
            /* Remaining elements. */
            int p = n - i;
            w1.load_partial(p, W + i);
            x1.load_partial(p, X + i);
            y1.load_partial(p, Y + i);
            sum1 = mul_add(w1*x1, y1, sum1); /* sum1 += x1*y1 */
        }
#    if VDOT3_UNROLL >= 6
        return horizontal_add((sum1 + sum2) + (sum3 + sum4) + (sum5 + sum6));
#    elif VDOT3_UNROLL >= 5
        return horizontal_add((sum1 + sum2) + (sum3 + sum4) + sum5);
#    elif VDOT3_UNROLL >= 4
        return horizontal_add((sum1 + sum2) + (sum3 + sum4));
#    elif VDOT3_UNROLL >= 3
        return horizontal_add(sum1 + sum2 + sum3);
#    elif VDOT3_UNROLL >= 2
        return horizontal_add(sum1 + sum2);
#    else
        return horizontal_add(sum1);
#    endif
#  endif /* VDOT3_UNROLL > 1 */
    } else {
        /* Vectorized code for small arrays or without loop unrolling. */
        VECT sum(0), w, x, y;
        size_t imax = n - NELEM;
        size_t i = 0;
        while (i <= imax) {
            w.load(W + i);
            x.load(X + i);
            y.load(Y + i);
            sum = mul_add(w*x, y, sum); /* sum += w*x*y */
            i += NELEM;
        }
        if (i < n) {
            int p = n - i;
            w.load_partial(p, W + i);
            x.load_partial(p, X + i);
            y.load_partial(p, Y + i);
            sum += x*y;
        }
        return horizontal_add(sum);
    }
#endif /* VECT */
}

#undef TYPE
#undef VDOT
#undef VDOT_INIT
#undef VDOT_INCR
#undef VDOT3
#undef VDOT3_INIT
#undef VDOT3_INCR
#undef VECT
#undef NELEM
#undef PTR_TO_NELEM
#undef NBITS
#undef NREGS
#undef SUFFIX
#undef IS_SINGLE

#endif /* _PVC_VDOT_C */
