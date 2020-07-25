/*
 * preprocessing.c -
 *
 * Implementation of image pre-processing methods.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PREPROCESSING_C
#define _PREPROCESSING_C 1

#include <stdlib.h>
#include <stdint.h>
#include "preprocessing.h"

/*---------------------------------------------------------------------------*/
/* MIN, MAX, NONNEGATIVE */

#define _MIN_2(x,y) ((x) < (y) ? (x) : (y))
#define _MAX_2(x,y) ((x) > (y) ? (x) : (y))

#if 1
#  include "pvc-min.h"
#  include "pvc-max.h"
#  define min(x,y) pvc_min(x,y)
#  define max(x,y) pvc_max(x,y)
#else

/**
 * @def min(x, y)
 *
 * @brief Get the smaller of two values.
 *
 * The call `min(x,y)` yields the smallest value between `x` and `y`.
 * NaN are ignored, `x` and `y` should be floating-point values.
 */
#define min(x, y)                               \
    _Generic((x) + (y),                         \
             float:  min2_f,                    \
             double: min2_d)((x), (y))

/**
 * @def max(x, y)
 *
 * @brief Get the greater of two values.
 *
 * The call `max(x,y)` yields the greater of `x` and `y`.  NaN are
 * ignored, `x` and `y` should be floating-point values.
 */
#define max(x, y)                               \
    _Generic((x) + (y),                         \
             float:  max2_f,                    \
             double: max2_d)((x), (y))

static inline float min2_f(float x, float y) {
    return _MIN_2(x, y);
}

static inline double min2_d(double x, double y) {
    return _MIN_2(x, y);
}

static inline float max2_f(float x, float y) {
    return _MAX_2(x, y);
}

static inline double max2_d(double x, double y) {
    return _MAX_2(x, y);
}

#endif

/**
 * @def nonnegative(x)
 *
 * @brief Get a nonnegative value.
 *
 * The call `nonnegative(x)` yields the greater of `x` and zero.  NaN
 * are ignored and `x` should be a floating-point value.
 */
#define nonnegative(x)                          \
    _Generic((x),                               \
             float:  nonnegative_f,             \
             double: nonnegative_d)(x)

static inline float nonnegative_f(float x) {
    float const zero = 0.0f;
    return _MAX_2(x, zero);
}

static inline float nonnegative_d(double x) {
    double const zero = 0.0;
    return _MAX_2(x, zero);
}

/*---------------------------------------------------------------------------*/
/* AFFINE PIXEL CORRECTION */

/**
 * @def apply_correction_std(u, a, b)
 *
 * @brief Apply affine correction (standard version).
 *
 * The call `apply_correction_std(u,a,b)` yields `(u - b)*a`.
 */
#define apply_correction_std(u, a, b)                           \
    _Generic((u) + (a) + (b),                                   \
             float:  apply_correction_std_f,                    \
             double: apply_correction_std_d)((u), (a), (b))

/**
 * @def apply_correction_fma(u, a, b)
 *
 * @brief Apply affine correction (FMA version).
 *
 * The call `apply_correction_fma(u,a,b)` yields `u*a + b`.  This
 * version is intended to exploit *fused multiply-add* (FMA)
 * instructions of the processor.
 */
#define apply_correction_fma(u, a, b)                           \
    _Generic((u) + (a) + (b),                                   \
             float:  apply_correction_fma_f,                    \
             double: apply_correction_fma_d)((u), (a), (b))

#define _APPLY_CORRECTION_STD(u, a, b) (((u) - (b))*(a))

#define _APPLY_CORRECTION_FMA(u, a, b) ((u)*(a) + (b))

static inline float apply_correction_std_f(float u, float a, float b) {
    return _APPLY_CORRECTION_STD(u, a, b);
}

static inline double apply_correction_std_d(double u, double a, double b) {
    return _APPLY_CORRECTION_STD(u, a, b);
}

static inline float apply_correction_fma_f(float u, float a, float b) {
    return _APPLY_CORRECTION_FMA(u, a, b);
}

static inline double apply_correction_fma_d(double u, double a, double b) {
    return _APPLY_CORRECTION_FMA(u, a, b);
}

/*---------------------------------------------------------------------------*/
/* COMPUTATION OF WEIGHTS */

/**
 * @def compute_weight_std(v, q, r)
 *
 * @brief Apply affine correction (standard version).
 *
 * The call `compute_weight_std(v,q,r)` yields `q/(max(v,0) + r)`.
 */
#define compute_weight_std(v, q, r)                             \
    _Generic((v) + (q) + (r),                                   \
             float:  compute_weight_std_f,                      \
             double: compute_weight_std_d)((v), (q), (r))

static inline float compute_weight_std_f(float v, float q, float r) {
    float const zero = 0;
    return q/(max(v, zero) + r);
}

static inline double compute_weight_std_d(double v, double q, double r) {
    double const zero = 0;
    return q/(max(v, zero) + r);
}

/**
 * @def compute_weight_alt(v, q, r)
 *
 * @brief Apply affine correction (alternative version).
 *
 * The call `compute_weight_alt(v,q,r)` yields `q/max(r + v, r)`.
 */
#define compute_weight_alt(v, q, r)                             \
    _Generic((v) + (q) + (r),                                   \
             float:  compute_weight_alt_f,                      \
             double: compute_weight_alt_d)((v), (q), (r))

static inline float compute_weight_alt_f(float v, float q, float r) {
    return q/max(r + v, r);
}

static inline double compute_weight_alt_d(double v, double q, double r) {
    return q/max(r + v, r);
}

/*---------------------------------------------------------------------------*/

#ifndef FLOAT
#  define FLOAT float
#endif
#ifndef PIXEL
#  define PIXEL uint8_t
#endif
#ifndef INTEGER
#  define INTEGER size_t
#endif

#define apply_correction apply_correction_std
#define compute_weight   compute_weight_std
#define preprocess_v1    preprocess_v11_uc_f
#define preprocess_v2    preprocess_v12_uc_f
#define preprocess_v3    preprocess_v13_uc_f
#define preprocess_v4    preprocess_v14_uc_f
#define preprocess_v5    preprocess_v15_uc_f
#define preprocess_v6    preprocess_v16_uc_f
#define preprocess_v7    preprocess_v17_uc_f
#include __FILE__
#undef apply_correction
#undef compute_weight
#undef preprocess_v1
#undef preprocess_v2
#undef preprocess_v3
#undef preprocess_v4
#undef preprocess_v5
#undef preprocess_v6
#undef preprocess_v7

#define apply_correction apply_correction_fma
#define compute_weight   compute_weight_std
#define preprocess_v1    preprocess_v21_uc_f
#define preprocess_v2	 preprocess_v22_uc_f
#define preprocess_v3	 preprocess_v23_uc_f
#define preprocess_v4	 preprocess_v24_uc_f
#define preprocess_v5	 preprocess_v25_uc_f
#define preprocess_v6	 preprocess_v26_uc_f
#define preprocess_v7	 preprocess_v27_uc_f
#include __FILE__
#undef apply_correction
#undef compute_weight
#undef preprocess_v1
#undef preprocess_v2
#undef preprocess_v3
#undef preprocess_v4
#undef preprocess_v5
#undef preprocess_v6
#undef preprocess_v7

#define apply_correction apply_correction_std
#define compute_weight   compute_weight_alt
#define preprocess_v1    preprocess_v31_uc_f
#define preprocess_v2	 preprocess_v32_uc_f
#define preprocess_v3	 preprocess_v33_uc_f
#define preprocess_v4	 preprocess_v34_uc_f
#define preprocess_v5	 preprocess_v35_uc_f
#define preprocess_v6	 preprocess_v36_uc_f
#define preprocess_v7	 preprocess_v37_uc_f
#include __FILE__
#undef apply_correction
#undef compute_weight
#undef preprocess_v1
#undef preprocess_v2
#undef preprocess_v3
#undef preprocess_v4
#undef preprocess_v5
#undef preprocess_v6
#undef preprocess_v7

#define apply_correction apply_correction_fma
#define compute_weight   compute_weight_alt
#define preprocess_v1    preprocess_v41_uc_f
#define preprocess_v2	 preprocess_v42_uc_f
#define preprocess_v3	 preprocess_v43_uc_f
#define preprocess_v4	 preprocess_v44_uc_f
#define preprocess_v5	 preprocess_v45_uc_f
#define preprocess_v6	 preprocess_v46_uc_f
#define preprocess_v7	 preprocess_v47_uc_f
#include __FILE__
#undef apply_correction
#undef compute_weight
#undef preprocess_v1
#undef preprocess_v2
#undef preprocess_v3
#undef preprocess_v4
#undef preprocess_v5
#undef preprocess_v6
#undef preprocess_v7

#else /* _PREPROCESSING_C defined */

#ifdef preprocess_v1
// Version 1.  Apply all operations to each pixel in turn.
void preprocess_v1(INTEGER width, INTEGER height, INTEGER stride,
                   FLOAT* restrict wgt, FLOAT* restrict dat,
                   PIXEL const* restrict img,
                   FLOAT const* restrict a, FLOAT const* restrict b,
                   FLOAT const* restrict q, FLOAT const* restrict r)
{
    for (INTEGER j = 0; j < height; ++j) {
        for (INTEGER i = 0, k = j*width, l = j*stride; i < width; ++i) {
            FLOAT val = apply_correction((FLOAT)img[l+i], a[k+i], b[k+i]);
            dat[k+i] = val;
            wgt[k+i] = compute_weight(val, q[k+i], r[k+i]);
        }
    }
}
#endif /* preprocess_v2 */

#ifdef preprocess_v2
// Version 2.  Convert and apply correction to a row of pixels, then
//             compute weights for this row of pixels.
void preprocess_v2(INTEGER width, INTEGER height, INTEGER stride,
                   FLOAT* restrict wgt, FLOAT* restrict dat,
                   PIXEL const* restrict img,
                   FLOAT const* restrict a, FLOAT const* restrict b,
                   FLOAT const* restrict q, FLOAT const* restrict r)
{
    for (INTEGER j = 0; j < height; ++j) {
        for (INTEGER i = 0, k = j*width, l = j*stride; i < width; ++i) {
            dat[k+i] = apply_correction((FLOAT)img[l+i], a[k+i], b[k+i]);
        }
        for (INTEGER i = j*width, n = i + width; i < n; ++i) {
            wgt[i] = compute_weight(dat[i], q[i], r[i]);
        }
    }
}
#endif /* preprocess_v2 */

#ifdef preprocess_v3
// Version 3.  Convert a row of pixels, then apply correction and
//             compute weights for this row of pixels.
void preprocess_v3(INTEGER width, INTEGER height, INTEGER stride,
                   FLOAT* restrict wgt, FLOAT* restrict dat,
                   PIXEL const* restrict img,
                   FLOAT const* restrict a, FLOAT const* restrict b,
                   FLOAT const* restrict q, FLOAT const* restrict r)
{
    for (INTEGER j = 0; j < height; ++j) {
        for (INTEGER i = 0, k = j*width, l = j*stride; i < width; ++i) {
            dat[k+i] = img[l+i];
        }
        for (INTEGER i = j*width, n = i + width; i < n; ++i) {
            FLOAT val = apply_correction(dat[i], a[i], b[i]);
            dat[i] = val;
            wgt[i] = compute_weight(val, q[i], r[i]);
        }
    }
}
#endif /* preprocess_v3 */

#ifdef preprocess_v4
// Version 4.  Convert a row of pixels, then apply correction for this
//             row of pixels, finally compute weights for this row of
//             pixels.
void preprocess_v4(INTEGER width, INTEGER height, INTEGER stride,
                   FLOAT* restrict wgt, FLOAT* restrict dat,
                   PIXEL const* restrict img,
                   FLOAT const* restrict a, FLOAT const* restrict b,
                   FLOAT const* restrict q, FLOAT const* restrict r)
{
    for (INTEGER j = 0; j < height; ++j) {
        for (INTEGER i = 0, k = j*width, l = j*stride; i < width; ++i) {
            dat[k+i] = img[l+i];
        }
        for (INTEGER i = j*width, n = i + width; i < n; ++i) {
            dat[i] = apply_correction(dat[i], a[i], b[i]);
        }
        for (INTEGER i = j*width, n = i + width; i < n; ++i) {
            wgt[i] = compute_weight(dat[i], q[i], r[i]);
        }
    }
}
#endif /* preprocess_v4 */

#ifdef preprocess_v5
// Version 5.  Convert and apply correction to the full image, then
//             compute the weights for the image.
void preprocess_v5(INTEGER width, INTEGER height, INTEGER stride,
                   FLOAT* restrict wgt, FLOAT* restrict dat,
                   PIXEL const* restrict img,
                   FLOAT const* restrict a, FLOAT const* restrict b,
                   FLOAT const* restrict q, FLOAT const* restrict r)
{
    for (INTEGER j = 0; j < height; ++j) {
        for (INTEGER i = 0, k = j*width, l = j*stride; i < width; ++i) {
            dat[k+i] = apply_correction((FLOAT)img[l+i], a[k+i], b[k+i]);
        }
    }
    INTEGER const n = width*height;
    for (INTEGER i = 0; i < n; ++i) {
        wgt[i] = compute_weight(dat[i], q[i], r[i]);
    }
}
#endif /* preprocess_v5 */

#ifdef preprocess_v6
// Version 6.  Convert the full image to floating-point, then apply
//             the correction and compute the weights for the image.
void preprocess_v6(INTEGER width, INTEGER height, INTEGER stride,
                   FLOAT* restrict wgt, FLOAT* restrict dat,
                   PIXEL const* restrict img,
                   FLOAT const* restrict a, FLOAT const* restrict b,
                   FLOAT const* restrict q, FLOAT const* restrict r)
{
    for (INTEGER j = 0; j < height; ++j) {
        for (INTEGER i = 0, k = j*width, l = j*stride; i < width; ++i) {
            dat[k+i] = img[l+i];
        }
    }
    INTEGER const n = width*height;
    for (INTEGER i = 0; i < n; ++i) {
        FLOAT val = apply_correction(dat[i], a[i], b[i]);
        dat[i] = val;
        wgt[i] = compute_weight(val, q[i], r[i]);
    }
}
#endif /* preprocess_v6 */

#ifdef preprocess_v7
// Version 7.  Convert the full image to floating-point, then apply
//             the correction to the image and finally compute the
//             weights for the image.
void preprocess_v7(INTEGER width, INTEGER height, INTEGER stride,
                   FLOAT* restrict wgt, FLOAT* restrict dat,
                   PIXEL const* restrict img,
                   FLOAT const* restrict a, FLOAT const* restrict b,
                   FLOAT const* restrict q, FLOAT const* restrict r)
{
    for (INTEGER j = 0; j < height; ++j) {
        for (INTEGER i = 0, k = j*width, l = j*stride; i < width; ++i) {
            dat[k+i] = img[l+i];
        }
    }
    INTEGER const n = width*height;
    for (INTEGER i = 0; i < n; ++i) {
        dat[i] = apply_correction(dat[i], a[i], b[i]);
    }
    for (INTEGER i = 0; i < n; ++i) {
        wgt[i] = compute_weight(dat[i], q[i], r[i]);
    }
}
#endif /* preprocess_v7 */

#endif /* _PREPROCESS_C */
