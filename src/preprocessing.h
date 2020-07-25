/*
 * preprocessing.h -
 *
 * Declarations of image pre-processing methods.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PREPROCESSING_H
#define _PREPROCESSING_H 1

#include <pvc.h>

_PVC_EXTERN_C_BEGIN

#define EXTERN(FUNC,PIXEL,FLOAT,INTEGER)                                \
    extern void FUNC(INTEGER width, INTEGER height, INTEGER stride,     \
                     FLOAT* restrict wgt, FLOAT* restrict dat,          \
                     PIXEL const* restrict img,                         \
                     FLOAT const* restrict a, FLOAT const* restrict b,  \
                     FLOAT const* restrict q, FLOAT const* restrict r)

EXTERN(preprocess_v11_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v12_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v13_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v14_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v15_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v16_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v17_uc_f, uint8_t, float, size_t);

EXTERN(preprocess_v21_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v22_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v23_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v24_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v25_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v26_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v27_uc_f, uint8_t, float, size_t);

EXTERN(preprocess_v31_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v32_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v33_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v34_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v35_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v36_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v37_uc_f, uint8_t, float, size_t);

EXTERN(preprocess_v41_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v42_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v43_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v44_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v45_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v46_uc_f, uint8_t, float, size_t);
EXTERN(preprocess_v47_uc_f, uint8_t, float, size_t);

EXTERN(preprocess_v11_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v12_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v13_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v14_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v15_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v16_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v17_uc_d, uint8_t, double, size_t);

EXTERN(preprocess_v21_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v22_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v23_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v24_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v25_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v26_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v27_uc_d, uint8_t, double, size_t);

EXTERN(preprocess_v31_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v32_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v33_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v34_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v35_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v36_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v37_uc_d, uint8_t, double, size_t);

EXTERN(preprocess_v41_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v42_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v43_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v44_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v45_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v46_uc_d, uint8_t, double, size_t);
EXTERN(preprocess_v47_uc_d, uint8_t, double, size_t);

#undef EXTERN

_PVC_EXTERN_C_END

#endif /* _PREPROCESSING_H */
