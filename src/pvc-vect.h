/*
 * pvc-vec.h -
 *
 * Definitions for SIMD vectors in PVC library.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */
#ifndef _PVC_VECT_H
#define _PVC_VECT_H 1

#include <stdalign.h>
#include <immintrin.h>

/**
 * @addtogroup vect Packed vector types and operations.
 *
 * PVC provides the following types:
 *
 * Note that suffixes are not quite the same as those considered in the
 * meta-programming part.  The reason is to keep readable short type
 * names.
 *
 * @{
 */

/**
 * Vector of 16 8-bit floating-point values.
 */
typedef union PVC_Vect16c PVC_Vect16c;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect16c {
# ifdef __SSE2__
    __m128i _pvc_xmm;
# endif
    alignas(16) int8_t _pvc_val[16];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 32 8-bit floating-point values.
 */
typedef union PVC_Vect32c PVC_Vect32c;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect32c {
# ifdef __AVX__
    __m256i _pvc_ymm;
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[2];
# endif
    alignas(32) int8_t _pvc_val[32];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 64 8-bit floating-point values.
 */
typedef union PVC_Vect64c PVC_Vect64c;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect64c {
# ifdef __AVX512F__
    __m512i _pvc_zmm;
# endif
# ifdef __AVX__
    __m256i _pvc_ymm[2];
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[4];
# endif
    alignas(64) int8_t _pvc_val[64];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 16 8-bit unsigned integers.
 */
typedef union PVC_Vect16uc PVC_Vect16uc;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect16uc {
# ifdef __SSE2__
    __m128i _pvc_xmm;
# endif
    alignas(16) uint8_t _pvc_val[16];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 32 8-bit unsigned integers.
 */
typedef union PVC_Vect32uc PVC_Vect32uc;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect32uc {
# ifdef __AVX__
    __m256i _pvc_ymm;
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[2];
# endif
    alignas(32) uint8_t _pvc_val[32];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 64 8-bit unsigned integers.
 */
typedef union PVC_Vect64uc PVC_Vect64uc;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect64uc {
# ifdef __AVX512F__
    __m512i _pvc_zmm;
# endif
# ifdef __AVX__
    __m256i _pvc_ymm[2];
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[4];
# endif
    alignas(64) uint8_t _pvc_val[64];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 8 16-bit floating-point values.
 */
typedef union PVC_Vect8s PVC_Vect8s;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect8s {
# ifdef __SSE2__
    __m128i _pvc_xmm;
# endif
    alignas(16) int16_t _pvc_val[8];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 16 16-bit floating-point values.
 */
typedef union PVC_Vect16s PVC_Vect16s;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect16s {
# ifdef __AVX__
    __m256i _pvc_ymm;
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[2];
# endif
    alignas(32) int16_t _pvc_val[16];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 32 16-bit floating-point values.
 */
typedef union PVC_Vect32s PVC_Vect32s;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect32s {
# ifdef __AVX512F__
    __m512i _pvc_zmm;
# endif
# ifdef __AVX__
    __m256i _pvc_ymm[2];
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[4];
# endif
    alignas(64) int16_t _pvc_val[32];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 8 16-bit unsigned integers.
 */
typedef union PVC_Vect8us PVC_Vect8us;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect8us {
# ifdef __SSE2__
    __m128i _pvc_xmm;
# endif
    alignas(16) uint16_t _pvc_val[8];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 16 16-bit unsigned integers.
 */
typedef union PVC_Vect16us PVC_Vect16us;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect16us {
# ifdef __AVX__
    __m256i _pvc_ymm;
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[2];
# endif
    alignas(32) uint16_t _pvc_val[16];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 32 16-bit unsigned integers.
 */
typedef union PVC_Vect32us PVC_Vect32us;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect32us {
# ifdef __AVX512F__
    __m512i _pvc_zmm;
# endif
# ifdef __AVX__
    __m256i _pvc_ymm[2];
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[4];
# endif
    alignas(64) uint16_t _pvc_val[32];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 4 32-bit floating-point values.
 */
typedef union PVC_Vect4i PVC_Vect4i;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect4i {
# ifdef __SSE2__
    __m128i _pvc_xmm;
# endif
    alignas(16) int32_t _pvc_val[4];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 8 32-bit floating-point values.
 */
typedef union PVC_Vect8i PVC_Vect8i;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect8i {
# ifdef __AVX__
    __m256i _pvc_ymm;
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[2];
# endif
    alignas(32) int32_t _pvc_val[8];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 16 32-bit floating-point values.
 */
typedef union PVC_Vect16i PVC_Vect16i;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect16i {
# ifdef __AVX512F__
    __m512i _pvc_zmm;
# endif
# ifdef __AVX__
    __m256i _pvc_ymm[2];
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[4];
# endif
    alignas(64) int32_t _pvc_val[16];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 4 32-bit unsigned integers.
 */
typedef union PVC_Vect4ui PVC_Vect4ui;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect4ui {
# ifdef __SSE2__
    __m128i _pvc_xmm;
# endif
    alignas(16) uint32_t _pvc_val[4];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 8 32-bit unsigned integers.
 */
typedef union PVC_Vect8ui PVC_Vect8ui;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect8ui {
# ifdef __AVX__
    __m256i _pvc_ymm;
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[2];
# endif
    alignas(32) uint32_t _pvc_val[8];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 16 32-bit unsigned integers.
 */
typedef union PVC_Vect16ui PVC_Vect16ui;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect16ui {
# ifdef __AVX512F__
    __m512i _pvc_zmm;
# endif
# ifdef __AVX__
    __m256i _pvc_ymm[2];
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[4];
# endif
    alignas(64) uint32_t _pvc_val[16];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 2 64-bit floating-point values.
 */
typedef union PVC_Vect2l PVC_Vect2l;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect2l {
# ifdef __SSE2__
    __m128i _pvc_xmm;
# endif
    alignas(16) int64_t _pvc_val[2];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 4 64-bit floating-point values.
 */
typedef union PVC_Vect4l PVC_Vect4l;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect4l {
# ifdef __AVX__
    __m256i _pvc_ymm;
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[2];
# endif
    alignas(32) int64_t _pvc_val[4];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 8 64-bit floating-point values.
 */
typedef union PVC_Vect8l PVC_Vect8l;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect8l {
# ifdef __AVX512F__
    __m512i _pvc_zmm;
# endif
# ifdef __AVX__
    __m256i _pvc_ymm[2];
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[4];
# endif
    alignas(64) int64_t _pvc_val[8];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 2 64-bit unsigned integers.
 */
typedef union PVC_Vect2ul PVC_Vect2ul;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect2ul {
# ifdef __SSE2__
    __m128i _pvc_xmm;
# endif
    alignas(16) uint64_t _pvc_val[2];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 4 64-bit unsigned integers.
 */
typedef union PVC_Vect4ul PVC_Vect4ul;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect4ul {
# ifdef __AVX__
    __m256i _pvc_ymm;
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[2];
# endif
    alignas(32) uint64_t _pvc_val[4];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 8 64-bit unsigned integers.
 */
typedef union PVC_Vect8ul PVC_Vect8ul;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect8ul {
# ifdef __AVX512F__
    __m512i _pvc_zmm;
# endif
# ifdef __AVX__
    __m256i _pvc_ymm[2];
# endif
# ifdef __SSE2__
    __m128i _pvc_xmm[4];
# endif
    alignas(64) uint64_t _pvc_val[8];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 4 32-bit floating-point values.
 */
typedef union PVC_Vect4f PVC_Vect4f;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect4f {
# ifdef __SSE__
    __m128 _pvc_xmm;
# endif
    alignas(16) float _pvc_val[4];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 8 32-bit floating-point values.
 */
typedef union PVC_Vect8f PVC_Vect8f;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect8f {
# ifdef __AVX__
    __m256 _pvc_ymm;
# endif
# ifdef __SSE__
    __m128 _pvc_xmm[2];
# endif
    alignas(32) float _pvc_val[8];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 16 32-bit floating-point values.
 */
typedef union PVC_Vect16f PVC_Vect16f;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect16f {
# ifdef __AVX512F__
    __m512 _pvc_zmm;
# endif
# ifdef __AVX__
    __m256 _pvc_ymm[2];
# endif
# ifdef __SSE__
    __m128 _pvc_xmm[4];
# endif
    alignas(64) float _pvc_val[16];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 2 64-bit floating-point values.
 */
typedef union PVC_Vect2d PVC_Vect2d;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect2d {
# ifdef __SSE2__
    __m128d _pvc_xmm;
# endif
    alignas(16) double _pvc_val[2];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 4 64-bit floating-point values.
 */
typedef union PVC_Vect4d PVC_Vect4d;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect4d {
# ifdef __AVX__
    __m256d _pvc_ymm;
# endif
# ifdef __SSE2__
    __m128d _pvc_xmm[2];
# endif
    alignas(32) double _pvc_val[4];
};
#endif /* PVC_DOXYGEN_PARSING */
/**
 * Vector of 8 64-bit floating-point values.
 */
typedef union PVC_Vect8d PVC_Vect8d;
#ifndef PVC_DOXYGEN_PARSING
union PVC_Vect8d {
# ifdef __AVX512F__
    __m512d _pvc_zmm;
# endif
# ifdef __AVX__
    __m256d _pvc_ymm[2];
# endif
# ifdef __SSE2__
    __m128d _pvc_xmm[4];
# endif
    alignas(64) double _pvc_val[8];
};
#endif /* PVC_DOXYGEN_PARSING */

/**
 * @def pvc_zero(T)
 *
 * @brief Get a zero-filled vector of given type.
 */
#define pvc_zero(T)                       \
    _Generic(*(T)0,                       \
             PVC_Vect16c:  pvc_zero_16c,  \
             PVC_Vect32c:  pvc_zero_32c,  \
             PVC_Vect64c:  pvc_zero_64c,  \
             PVC_Vect16uc: pvc_zero_16uc, \
             PVC_Vect32uc: pvc_zero_32uc, \
             PVC_Vect64uc: pvc_zero_64uc, \
             PVC_Vect8s:   pvc_zero_8s,   \
             PVC_Vect16s:  pvc_zero_16s,  \
             PVC_Vect32s:  pvc_zero_32s,  \
             PVC_Vect8us:  pvc_zero_8us,  \
             PVC_Vect16us: pvc_zero_16us, \
             PVC_Vect32us: pvc_zero_32us, \
             PVC_Vect4i:   pvc_zero_4i,   \
             PVC_Vect8i:   pvc_zero_8i,   \
             PVC_Vect16i:  pvc_zero_16i,  \
             PVC_Vect4ui:  pvc_zero_4ui,  \
             PVC_Vect8ui:  pvc_zero_8ui,  \
             PVC_Vect16ui: pvc_zero_16ui, \
             PVC_Vect2l:   pvc_zero_2l,   \
             PVC_Vect4l:   pvc_zero_4l,   \
             PVC_Vect8l:   pvc_zero_8l,   \
             PVC_Vect2ul:  pvc_zero_2ul,  \
             PVC_Vect4ul:  pvc_zero_4ul,  \
             PVC_Vect8ul:  pvc_zero_8ul,  \
             PVC_Vect4f:   pvc_zero_4f,   \
             PVC_Vect8f:   pvc_zero_8f,   \
             PVC_Vect16f:  pvc_zero_16f,  \
             PVC_Vect2d:   pvc_zero_2d,   \
             PVC_Vect4d:   pvc_zero_4d,   \
             PVC_Vect8d:   pvc_zero_8d)()

static inline
PVC_Vect16c pvc_zero_16c(void)
{
    return (PVC_Vect16c){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
#endif
    };
}

static inline
PVC_Vect32c pvc_zero_32c(void)
{
    return (PVC_Vect32c){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
        ._pvc_val[16] = 0,
        ._pvc_val[17] = 0,
        ._pvc_val[18] = 0,
        ._pvc_val[19] = 0,
        ._pvc_val[20] = 0,
        ._pvc_val[21] = 0,
        ._pvc_val[22] = 0,
        ._pvc_val[23] = 0,
        ._pvc_val[24] = 0,
        ._pvc_val[25] = 0,
        ._pvc_val[26] = 0,
        ._pvc_val[27] = 0,
        ._pvc_val[28] = 0,
        ._pvc_val[29] = 0,
        ._pvc_val[30] = 0,
        ._pvc_val[31] = 0,
#endif
    };
}

static inline
PVC_Vect64c pvc_zero_64c(void)
{
    return (PVC_Vect64c){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_si512(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_si256(),
        ._pvc_ymm[1] = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
        ._pvc_xmm[2] = _mm_setzero_si128(),
        ._pvc_xmm[3] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
        ._pvc_val[16] = 0,
        ._pvc_val[17] = 0,
        ._pvc_val[18] = 0,
        ._pvc_val[19] = 0,
        ._pvc_val[20] = 0,
        ._pvc_val[21] = 0,
        ._pvc_val[22] = 0,
        ._pvc_val[23] = 0,
        ._pvc_val[24] = 0,
        ._pvc_val[25] = 0,
        ._pvc_val[26] = 0,
        ._pvc_val[27] = 0,
        ._pvc_val[28] = 0,
        ._pvc_val[29] = 0,
        ._pvc_val[30] = 0,
        ._pvc_val[31] = 0,
        ._pvc_val[32] = 0,
        ._pvc_val[33] = 0,
        ._pvc_val[34] = 0,
        ._pvc_val[35] = 0,
        ._pvc_val[36] = 0,
        ._pvc_val[37] = 0,
        ._pvc_val[38] = 0,
        ._pvc_val[39] = 0,
        ._pvc_val[40] = 0,
        ._pvc_val[41] = 0,
        ._pvc_val[42] = 0,
        ._pvc_val[43] = 0,
        ._pvc_val[44] = 0,
        ._pvc_val[45] = 0,
        ._pvc_val[46] = 0,
        ._pvc_val[47] = 0,
        ._pvc_val[48] = 0,
        ._pvc_val[49] = 0,
        ._pvc_val[50] = 0,
        ._pvc_val[51] = 0,
        ._pvc_val[52] = 0,
        ._pvc_val[53] = 0,
        ._pvc_val[54] = 0,
        ._pvc_val[55] = 0,
        ._pvc_val[56] = 0,
        ._pvc_val[57] = 0,
        ._pvc_val[58] = 0,
        ._pvc_val[59] = 0,
        ._pvc_val[60] = 0,
        ._pvc_val[61] = 0,
        ._pvc_val[62] = 0,
        ._pvc_val[63] = 0,
#endif
    };
}

static inline
PVC_Vect16uc pvc_zero_16uc(void)
{
    return (PVC_Vect16uc){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
#endif
    };
}

static inline
PVC_Vect32uc pvc_zero_32uc(void)
{
    return (PVC_Vect32uc){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
        ._pvc_val[16] = 0,
        ._pvc_val[17] = 0,
        ._pvc_val[18] = 0,
        ._pvc_val[19] = 0,
        ._pvc_val[20] = 0,
        ._pvc_val[21] = 0,
        ._pvc_val[22] = 0,
        ._pvc_val[23] = 0,
        ._pvc_val[24] = 0,
        ._pvc_val[25] = 0,
        ._pvc_val[26] = 0,
        ._pvc_val[27] = 0,
        ._pvc_val[28] = 0,
        ._pvc_val[29] = 0,
        ._pvc_val[30] = 0,
        ._pvc_val[31] = 0,
#endif
    };
}

static inline
PVC_Vect64uc pvc_zero_64uc(void)
{
    return (PVC_Vect64uc){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_si512(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_si256(),
        ._pvc_ymm[1] = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
        ._pvc_xmm[2] = _mm_setzero_si128(),
        ._pvc_xmm[3] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
        ._pvc_val[16] = 0,
        ._pvc_val[17] = 0,
        ._pvc_val[18] = 0,
        ._pvc_val[19] = 0,
        ._pvc_val[20] = 0,
        ._pvc_val[21] = 0,
        ._pvc_val[22] = 0,
        ._pvc_val[23] = 0,
        ._pvc_val[24] = 0,
        ._pvc_val[25] = 0,
        ._pvc_val[26] = 0,
        ._pvc_val[27] = 0,
        ._pvc_val[28] = 0,
        ._pvc_val[29] = 0,
        ._pvc_val[30] = 0,
        ._pvc_val[31] = 0,
        ._pvc_val[32] = 0,
        ._pvc_val[33] = 0,
        ._pvc_val[34] = 0,
        ._pvc_val[35] = 0,
        ._pvc_val[36] = 0,
        ._pvc_val[37] = 0,
        ._pvc_val[38] = 0,
        ._pvc_val[39] = 0,
        ._pvc_val[40] = 0,
        ._pvc_val[41] = 0,
        ._pvc_val[42] = 0,
        ._pvc_val[43] = 0,
        ._pvc_val[44] = 0,
        ._pvc_val[45] = 0,
        ._pvc_val[46] = 0,
        ._pvc_val[47] = 0,
        ._pvc_val[48] = 0,
        ._pvc_val[49] = 0,
        ._pvc_val[50] = 0,
        ._pvc_val[51] = 0,
        ._pvc_val[52] = 0,
        ._pvc_val[53] = 0,
        ._pvc_val[54] = 0,
        ._pvc_val[55] = 0,
        ._pvc_val[56] = 0,
        ._pvc_val[57] = 0,
        ._pvc_val[58] = 0,
        ._pvc_val[59] = 0,
        ._pvc_val[60] = 0,
        ._pvc_val[61] = 0,
        ._pvc_val[62] = 0,
        ._pvc_val[63] = 0,
#endif
    };
}

static inline
PVC_Vect8s pvc_zero_8s(void)
{
    return (PVC_Vect8s){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
#endif
    };
}

static inline
PVC_Vect16s pvc_zero_16s(void)
{
    return (PVC_Vect16s){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
#endif
    };
}

static inline
PVC_Vect32s pvc_zero_32s(void)
{
    return (PVC_Vect32s){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_si512(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_si256(),
        ._pvc_ymm[1] = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
        ._pvc_xmm[2] = _mm_setzero_si128(),
        ._pvc_xmm[3] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
        ._pvc_val[16] = 0,
        ._pvc_val[17] = 0,
        ._pvc_val[18] = 0,
        ._pvc_val[19] = 0,
        ._pvc_val[20] = 0,
        ._pvc_val[21] = 0,
        ._pvc_val[22] = 0,
        ._pvc_val[23] = 0,
        ._pvc_val[24] = 0,
        ._pvc_val[25] = 0,
        ._pvc_val[26] = 0,
        ._pvc_val[27] = 0,
        ._pvc_val[28] = 0,
        ._pvc_val[29] = 0,
        ._pvc_val[30] = 0,
        ._pvc_val[31] = 0,
#endif
    };
}

static inline
PVC_Vect8us pvc_zero_8us(void)
{
    return (PVC_Vect8us){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
#endif
    };
}

static inline
PVC_Vect16us pvc_zero_16us(void)
{
    return (PVC_Vect16us){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
#endif
    };
}

static inline
PVC_Vect32us pvc_zero_32us(void)
{
    return (PVC_Vect32us){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_si512(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_si256(),
        ._pvc_ymm[1] = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
        ._pvc_xmm[2] = _mm_setzero_si128(),
        ._pvc_xmm[3] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
        ._pvc_val[16] = 0,
        ._pvc_val[17] = 0,
        ._pvc_val[18] = 0,
        ._pvc_val[19] = 0,
        ._pvc_val[20] = 0,
        ._pvc_val[21] = 0,
        ._pvc_val[22] = 0,
        ._pvc_val[23] = 0,
        ._pvc_val[24] = 0,
        ._pvc_val[25] = 0,
        ._pvc_val[26] = 0,
        ._pvc_val[27] = 0,
        ._pvc_val[28] = 0,
        ._pvc_val[29] = 0,
        ._pvc_val[30] = 0,
        ._pvc_val[31] = 0,
#endif
    };
}

static inline
PVC_Vect4i pvc_zero_4i(void)
{
    return (PVC_Vect4i){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
#endif
    };
}

static inline
PVC_Vect8i pvc_zero_8i(void)
{
    return (PVC_Vect8i){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
#endif
    };
}

static inline
PVC_Vect16i pvc_zero_16i(void)
{
    return (PVC_Vect16i){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_si512(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_si256(),
        ._pvc_ymm[1] = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
        ._pvc_xmm[2] = _mm_setzero_si128(),
        ._pvc_xmm[3] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
#endif
    };
}

static inline
PVC_Vect4ui pvc_zero_4ui(void)
{
    return (PVC_Vect4ui){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
#endif
    };
}

static inline
PVC_Vect8ui pvc_zero_8ui(void)
{
    return (PVC_Vect8ui){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
#endif
    };
}

static inline
PVC_Vect16ui pvc_zero_16ui(void)
{
    return (PVC_Vect16ui){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_si512(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_si256(),
        ._pvc_ymm[1] = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
        ._pvc_xmm[2] = _mm_setzero_si128(),
        ._pvc_xmm[3] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
#endif
    };
}

static inline
PVC_Vect2l pvc_zero_2l(void)
{
    return (PVC_Vect2l){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
#endif
    };
}

static inline
PVC_Vect4l pvc_zero_4l(void)
{
    return (PVC_Vect4l){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
#endif
    };
}

static inline
PVC_Vect8l pvc_zero_8l(void)
{
    return (PVC_Vect8l){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_si512(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_si256(),
        ._pvc_ymm[1] = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
        ._pvc_xmm[2] = _mm_setzero_si128(),
        ._pvc_xmm[3] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
#endif
    };
}

static inline
PVC_Vect2ul pvc_zero_2ul(void)
{
    return (PVC_Vect2ul){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
#endif
    };
}

static inline
PVC_Vect4ul pvc_zero_4ul(void)
{
    return (PVC_Vect4ul){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
#endif
    };
}

static inline
PVC_Vect8ul pvc_zero_8ul(void)
{
    return (PVC_Vect8ul){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_si512(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_si256(),
        ._pvc_ymm[1] = _mm256_setzero_si256(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_si128(),
        ._pvc_xmm[1] = _mm_setzero_si128(),
        ._pvc_xmm[2] = _mm_setzero_si128(),
        ._pvc_xmm[3] = _mm_setzero_si128(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
#endif
    };
}

static inline
PVC_Vect4f pvc_zero_4f(void)
{
    return (PVC_Vect4f){
#if defined(__SSE__)
        ._pvc_xmm = _mm_setzero_ps(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
#endif
    };
}

static inline
PVC_Vect8f pvc_zero_8f(void)
{
    return (PVC_Vect8f){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_ps(),
#elif defined(__SSE__)
        ._pvc_xmm[0] = _mm_setzero_ps(),
        ._pvc_xmm[1] = _mm_setzero_ps(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
#endif
    };
}

static inline
PVC_Vect16f pvc_zero_16f(void)
{
    return (PVC_Vect16f){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_ps(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_ps(),
        ._pvc_ymm[1] = _mm256_setzero_ps(),
#elif defined(__SSE__)
        ._pvc_xmm[0] = _mm_setzero_ps(),
        ._pvc_xmm[1] = _mm_setzero_ps(),
        ._pvc_xmm[2] = _mm_setzero_ps(),
        ._pvc_xmm[3] = _mm_setzero_ps(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
        ._pvc_val[8] = 0,
        ._pvc_val[9] = 0,
        ._pvc_val[10] = 0,
        ._pvc_val[11] = 0,
        ._pvc_val[12] = 0,
        ._pvc_val[13] = 0,
        ._pvc_val[14] = 0,
        ._pvc_val[15] = 0,
#endif
    };
}

static inline
PVC_Vect2d pvc_zero_2d(void)
{
    return (PVC_Vect2d){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_setzero_pd(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
#endif
    };
}

static inline
PVC_Vect4d pvc_zero_4d(void)
{
    return (PVC_Vect4d){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_setzero_pd(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_pd(),
        ._pvc_xmm[1] = _mm_setzero_pd(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
#endif
    };
}

static inline
PVC_Vect8d pvc_zero_8d(void)
{
    return (PVC_Vect8d){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_setzero_pd(),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_setzero_pd(),
        ._pvc_ymm[1] = _mm256_setzero_pd(),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_setzero_pd(),
        ._pvc_xmm[1] = _mm_setzero_pd(),
        ._pvc_xmm[2] = _mm_setzero_pd(),
        ._pvc_xmm[3] = _mm_setzero_pd(),
#else
        ._pvc_val[0] = 0,
        ._pvc_val[1] = 0,
        ._pvc_val[2] = 0,
        ._pvc_val[3] = 0,
        ._pvc_val[4] = 0,
        ._pvc_val[5] = 0,
        ._pvc_val[6] = 0,
        ._pvc_val[7] = 0,
#endif
    };
}

/**
 * @def pvc_load(T, addr)
 *
 * @brief Load packed values from memory.
 *
 * Load packed values of type @a T from address @a addr which may not be
 * aligned.
 */
#define pvc_load(T, addr)                 \
    _Generic(*(T)0,                       \
             PVC_Vect16c:  pvc_load_16c,  \
             PVC_Vect32c:  pvc_load_32c,  \
             PVC_Vect64c:  pvc_load_64c,  \
             PVC_Vect16uc: pvc_load_16uc, \
             PVC_Vect32uc: pvc_load_32uc, \
             PVC_Vect64uc: pvc_load_64uc, \
             PVC_Vect8s:   pvc_load_8s,   \
             PVC_Vect16s:  pvc_load_16s,  \
             PVC_Vect32s:  pvc_load_32s,  \
             PVC_Vect8us:  pvc_load_8us,  \
             PVC_Vect16us: pvc_load_16us, \
             PVC_Vect32us: pvc_load_32us, \
             PVC_Vect4i:   pvc_load_4i,   \
             PVC_Vect8i:   pvc_load_8i,   \
             PVC_Vect16i:  pvc_load_16i,  \
             PVC_Vect4ui:  pvc_load_4ui,  \
             PVC_Vect8ui:  pvc_load_8ui,  \
             PVC_Vect16ui: pvc_load_16ui, \
             PVC_Vect2l:   pvc_load_2l,   \
             PVC_Vect4l:   pvc_load_4l,   \
             PVC_Vect8l:   pvc_load_8l,   \
             PVC_Vect2ul:  pvc_load_2ul,  \
             PVC_Vect4ul:  pvc_load_4ul,  \
             PVC_Vect8ul:  pvc_load_8ul,  \
             PVC_Vect4f:   pvc_load_4f,   \
             PVC_Vect8f:   pvc_load_8f,   \
             PVC_Vect16f:  pvc_load_16f,  \
             PVC_Vect2d:   pvc_load_2d,   \
             PVC_Vect4d:   pvc_load_4d,   \
             PVC_Vect8d:   pvc_load_8d)(addr)

static inline PVC_Vect16c
pvc_load_16c(int8_t const* addr)
{
     return (PVC_Vect16c){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_load_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect32c
pvc_load_32c(int8_t const* addr)
{
     return (PVC_Vect32c){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[16]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
#endif
    };
}

static inline PVC_Vect64c
pvc_load_64c(int8_t const* addr)
{
     return (PVC_Vect64c){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_si256(&addr[32]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[16]),
        ._pvc_xmm[2] = _mm_load_si128(&addr[32]),
        ._pvc_xmm[3] = _mm_load_si128(&addr[48]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
        ._pvc_val[32] = addr[32],
        ._pvc_val[33] = addr[33],
        ._pvc_val[34] = addr[34],
        ._pvc_val[35] = addr[35],
        ._pvc_val[36] = addr[36],
        ._pvc_val[37] = addr[37],
        ._pvc_val[38] = addr[38],
        ._pvc_val[39] = addr[39],
        ._pvc_val[40] = addr[40],
        ._pvc_val[41] = addr[41],
        ._pvc_val[42] = addr[42],
        ._pvc_val[43] = addr[43],
        ._pvc_val[44] = addr[44],
        ._pvc_val[45] = addr[45],
        ._pvc_val[46] = addr[46],
        ._pvc_val[47] = addr[47],
        ._pvc_val[48] = addr[48],
        ._pvc_val[49] = addr[49],
        ._pvc_val[50] = addr[50],
        ._pvc_val[51] = addr[51],
        ._pvc_val[52] = addr[52],
        ._pvc_val[53] = addr[53],
        ._pvc_val[54] = addr[54],
        ._pvc_val[55] = addr[55],
        ._pvc_val[56] = addr[56],
        ._pvc_val[57] = addr[57],
        ._pvc_val[58] = addr[58],
        ._pvc_val[59] = addr[59],
        ._pvc_val[60] = addr[60],
        ._pvc_val[61] = addr[61],
        ._pvc_val[62] = addr[62],
        ._pvc_val[63] = addr[63],
#endif
    };
}

static inline PVC_Vect16uc
pvc_load_16uc(uint8_t const* addr)
{
     return (PVC_Vect16uc){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_load_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect32uc
pvc_load_32uc(uint8_t const* addr)
{
     return (PVC_Vect32uc){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[16]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
#endif
    };
}

static inline PVC_Vect64uc
pvc_load_64uc(uint8_t const* addr)
{
     return (PVC_Vect64uc){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_si256(&addr[32]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[16]),
        ._pvc_xmm[2] = _mm_load_si128(&addr[32]),
        ._pvc_xmm[3] = _mm_load_si128(&addr[48]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
        ._pvc_val[32] = addr[32],
        ._pvc_val[33] = addr[33],
        ._pvc_val[34] = addr[34],
        ._pvc_val[35] = addr[35],
        ._pvc_val[36] = addr[36],
        ._pvc_val[37] = addr[37],
        ._pvc_val[38] = addr[38],
        ._pvc_val[39] = addr[39],
        ._pvc_val[40] = addr[40],
        ._pvc_val[41] = addr[41],
        ._pvc_val[42] = addr[42],
        ._pvc_val[43] = addr[43],
        ._pvc_val[44] = addr[44],
        ._pvc_val[45] = addr[45],
        ._pvc_val[46] = addr[46],
        ._pvc_val[47] = addr[47],
        ._pvc_val[48] = addr[48],
        ._pvc_val[49] = addr[49],
        ._pvc_val[50] = addr[50],
        ._pvc_val[51] = addr[51],
        ._pvc_val[52] = addr[52],
        ._pvc_val[53] = addr[53],
        ._pvc_val[54] = addr[54],
        ._pvc_val[55] = addr[55],
        ._pvc_val[56] = addr[56],
        ._pvc_val[57] = addr[57],
        ._pvc_val[58] = addr[58],
        ._pvc_val[59] = addr[59],
        ._pvc_val[60] = addr[60],
        ._pvc_val[61] = addr[61],
        ._pvc_val[62] = addr[62],
        ._pvc_val[63] = addr[63],
#endif
    };
}

static inline PVC_Vect8s
pvc_load_8s(int16_t const* addr)
{
     return (PVC_Vect8s){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_load_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16s
pvc_load_16s(int16_t const* addr)
{
     return (PVC_Vect16s){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[8]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect32s
pvc_load_32s(int16_t const* addr)
{
     return (PVC_Vect32s){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_si256(&addr[16]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[8]),
        ._pvc_xmm[2] = _mm_load_si128(&addr[16]),
        ._pvc_xmm[3] = _mm_load_si128(&addr[24]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
#endif
    };
}

static inline PVC_Vect8us
pvc_load_8us(uint16_t const* addr)
{
     return (PVC_Vect8us){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_load_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16us
pvc_load_16us(uint16_t const* addr)
{
     return (PVC_Vect16us){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[8]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect32us
pvc_load_32us(uint16_t const* addr)
{
     return (PVC_Vect32us){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_si256(&addr[16]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[8]),
        ._pvc_xmm[2] = _mm_load_si128(&addr[16]),
        ._pvc_xmm[3] = _mm_load_si128(&addr[24]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
#endif
    };
}

static inline PVC_Vect4i
pvc_load_4i(int32_t const* addr)
{
     return (PVC_Vect4i){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_load_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8i
pvc_load_8i(int32_t const* addr)
{
     return (PVC_Vect8i){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[4]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16i
pvc_load_16i(int32_t const* addr)
{
     return (PVC_Vect16i){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_si256(&addr[8]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[4]),
        ._pvc_xmm[2] = _mm_load_si128(&addr[8]),
        ._pvc_xmm[3] = _mm_load_si128(&addr[12]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect4ui
pvc_load_4ui(uint32_t const* addr)
{
     return (PVC_Vect4ui){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_load_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8ui
pvc_load_8ui(uint32_t const* addr)
{
     return (PVC_Vect8ui){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[4]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16ui
pvc_load_16ui(uint32_t const* addr)
{
     return (PVC_Vect16ui){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_si256(&addr[8]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[4]),
        ._pvc_xmm[2] = _mm_load_si128(&addr[8]),
        ._pvc_xmm[3] = _mm_load_si128(&addr[12]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect2l
pvc_load_2l(int64_t const* addr)
{
     return (PVC_Vect2l){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_load_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
#endif
    };
}

static inline PVC_Vect4l
pvc_load_4l(int64_t const* addr)
{
     return (PVC_Vect4l){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[2]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8l
pvc_load_8l(int64_t const* addr)
{
     return (PVC_Vect8l){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_si256(&addr[4]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[2]),
        ._pvc_xmm[2] = _mm_load_si128(&addr[4]),
        ._pvc_xmm[3] = _mm_load_si128(&addr[6]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect2ul
pvc_load_2ul(uint64_t const* addr)
{
     return (PVC_Vect2ul){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_load_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
#endif
    };
}

static inline PVC_Vect4ul
pvc_load_4ul(uint64_t const* addr)
{
     return (PVC_Vect4ul){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[2]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8ul
pvc_load_8ul(uint64_t const* addr)
{
     return (PVC_Vect8ul){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_si256(&addr[4]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_load_si128(&addr[2]),
        ._pvc_xmm[2] = _mm_load_si128(&addr[4]),
        ._pvc_xmm[3] = _mm_load_si128(&addr[6]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect4f
pvc_load_4f(float const* addr)
{
     return (PVC_Vect4f){
#if defined(__SSE__)
        ._pvc_xmm = _mm_load_ps(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8f
pvc_load_8f(float const* addr)
{
     return (PVC_Vect8f){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_ps(addr),
#elif defined(__SSE__)
        ._pvc_xmm[0] = _mm_load_ps(&addr[0]),
        ._pvc_xmm[1] = _mm_load_ps(&addr[4]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16f
pvc_load_16f(float const* addr)
{
     return (PVC_Vect16f){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_ps(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_ps(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_ps(&addr[8]),
#elif defined(__SSE__)
        ._pvc_xmm[0] = _mm_load_ps(&addr[0]),
        ._pvc_xmm[1] = _mm_load_ps(&addr[4]),
        ._pvc_xmm[2] = _mm_load_ps(&addr[8]),
        ._pvc_xmm[3] = _mm_load_ps(&addr[12]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect2d
pvc_load_2d(double const* addr)
{
     return (PVC_Vect2d){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_load_pd(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
#endif
    };
}

static inline PVC_Vect4d
pvc_load_4d(double const* addr)
{
     return (PVC_Vect4d){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_load_pd(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_pd(&addr[0]),
        ._pvc_xmm[1] = _mm_load_pd(&addr[2]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8d
pvc_load_8d(double const* addr)
{
     return (PVC_Vect8d){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_load_pd(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_load_pd(&addr[0]),
        ._pvc_ymm[1] = _mm256_load_pd(&addr[4]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_load_pd(&addr[0]),
        ._pvc_xmm[1] = _mm_load_pd(&addr[2]),
        ._pvc_xmm[2] = _mm_load_pd(&addr[4]),
        ._pvc_xmm[3] = _mm_load_pd(&addr[6]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

/**
 * @def pvc_loadu(T, addr)
 *
 * @brief Load packed values from memory.
 *
 * Load packed values of type @a T from address @a addr which may not be
 * aligned.
 */
#define pvc_loadu(T, addr)                 \
    _Generic(*(T)0,                        \
             PVC_Vect16c:  pvc_loadu_16c,  \
             PVC_Vect32c:  pvc_loadu_32c,  \
             PVC_Vect64c:  pvc_loadu_64c,  \
             PVC_Vect16uc: pvc_loadu_16uc, \
             PVC_Vect32uc: pvc_loadu_32uc, \
             PVC_Vect64uc: pvc_loadu_64uc, \
             PVC_Vect8s:   pvc_loadu_8s,   \
             PVC_Vect16s:  pvc_loadu_16s,  \
             PVC_Vect32s:  pvc_loadu_32s,  \
             PVC_Vect8us:  pvc_loadu_8us,  \
             PVC_Vect16us: pvc_loadu_16us, \
             PVC_Vect32us: pvc_loadu_32us, \
             PVC_Vect4i:   pvc_loadu_4i,   \
             PVC_Vect8i:   pvc_loadu_8i,   \
             PVC_Vect16i:  pvc_loadu_16i,  \
             PVC_Vect4ui:  pvc_loadu_4ui,  \
             PVC_Vect8ui:  pvc_loadu_8ui,  \
             PVC_Vect16ui: pvc_loadu_16ui, \
             PVC_Vect2l:   pvc_loadu_2l,   \
             PVC_Vect4l:   pvc_loadu_4l,   \
             PVC_Vect8l:   pvc_loadu_8l,   \
             PVC_Vect2ul:  pvc_loadu_2ul,  \
             PVC_Vect4ul:  pvc_loadu_4ul,  \
             PVC_Vect8ul:  pvc_loadu_8ul,  \
             PVC_Vect4f:   pvc_loadu_4f,   \
             PVC_Vect8f:   pvc_loadu_8f,   \
             PVC_Vect16f:  pvc_loadu_16f,  \
             PVC_Vect2d:   pvc_loadu_2d,   \
             PVC_Vect4d:   pvc_loadu_4d,   \
             PVC_Vect8d:   pvc_loadu_8d)(addr)

static inline PVC_Vect16c
pvc_loadu_16c(int8_t const* addr)
{
     return (PVC_Vect16c){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_loadu_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect32c
pvc_loadu_32c(int8_t const* addr)
{
     return (PVC_Vect32c){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[16]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
#endif
    };
}

static inline PVC_Vect64c
pvc_loadu_64c(int8_t const* addr)
{
     return (PVC_Vect64c){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_si256(&addr[32]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[16]),
        ._pvc_xmm[2] = _mm_loadu_si128(&addr[32]),
        ._pvc_xmm[3] = _mm_loadu_si128(&addr[48]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
        ._pvc_val[32] = addr[32],
        ._pvc_val[33] = addr[33],
        ._pvc_val[34] = addr[34],
        ._pvc_val[35] = addr[35],
        ._pvc_val[36] = addr[36],
        ._pvc_val[37] = addr[37],
        ._pvc_val[38] = addr[38],
        ._pvc_val[39] = addr[39],
        ._pvc_val[40] = addr[40],
        ._pvc_val[41] = addr[41],
        ._pvc_val[42] = addr[42],
        ._pvc_val[43] = addr[43],
        ._pvc_val[44] = addr[44],
        ._pvc_val[45] = addr[45],
        ._pvc_val[46] = addr[46],
        ._pvc_val[47] = addr[47],
        ._pvc_val[48] = addr[48],
        ._pvc_val[49] = addr[49],
        ._pvc_val[50] = addr[50],
        ._pvc_val[51] = addr[51],
        ._pvc_val[52] = addr[52],
        ._pvc_val[53] = addr[53],
        ._pvc_val[54] = addr[54],
        ._pvc_val[55] = addr[55],
        ._pvc_val[56] = addr[56],
        ._pvc_val[57] = addr[57],
        ._pvc_val[58] = addr[58],
        ._pvc_val[59] = addr[59],
        ._pvc_val[60] = addr[60],
        ._pvc_val[61] = addr[61],
        ._pvc_val[62] = addr[62],
        ._pvc_val[63] = addr[63],
#endif
    };
}

static inline PVC_Vect16uc
pvc_loadu_16uc(uint8_t const* addr)
{
     return (PVC_Vect16uc){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_loadu_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect32uc
pvc_loadu_32uc(uint8_t const* addr)
{
     return (PVC_Vect32uc){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[16]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
#endif
    };
}

static inline PVC_Vect64uc
pvc_loadu_64uc(uint8_t const* addr)
{
     return (PVC_Vect64uc){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_si256(&addr[32]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[16]),
        ._pvc_xmm[2] = _mm_loadu_si128(&addr[32]),
        ._pvc_xmm[3] = _mm_loadu_si128(&addr[48]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
        ._pvc_val[32] = addr[32],
        ._pvc_val[33] = addr[33],
        ._pvc_val[34] = addr[34],
        ._pvc_val[35] = addr[35],
        ._pvc_val[36] = addr[36],
        ._pvc_val[37] = addr[37],
        ._pvc_val[38] = addr[38],
        ._pvc_val[39] = addr[39],
        ._pvc_val[40] = addr[40],
        ._pvc_val[41] = addr[41],
        ._pvc_val[42] = addr[42],
        ._pvc_val[43] = addr[43],
        ._pvc_val[44] = addr[44],
        ._pvc_val[45] = addr[45],
        ._pvc_val[46] = addr[46],
        ._pvc_val[47] = addr[47],
        ._pvc_val[48] = addr[48],
        ._pvc_val[49] = addr[49],
        ._pvc_val[50] = addr[50],
        ._pvc_val[51] = addr[51],
        ._pvc_val[52] = addr[52],
        ._pvc_val[53] = addr[53],
        ._pvc_val[54] = addr[54],
        ._pvc_val[55] = addr[55],
        ._pvc_val[56] = addr[56],
        ._pvc_val[57] = addr[57],
        ._pvc_val[58] = addr[58],
        ._pvc_val[59] = addr[59],
        ._pvc_val[60] = addr[60],
        ._pvc_val[61] = addr[61],
        ._pvc_val[62] = addr[62],
        ._pvc_val[63] = addr[63],
#endif
    };
}

static inline PVC_Vect8s
pvc_loadu_8s(int16_t const* addr)
{
     return (PVC_Vect8s){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_loadu_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16s
pvc_loadu_16s(int16_t const* addr)
{
     return (PVC_Vect16s){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[8]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect32s
pvc_loadu_32s(int16_t const* addr)
{
     return (PVC_Vect32s){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_si256(&addr[16]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[8]),
        ._pvc_xmm[2] = _mm_loadu_si128(&addr[16]),
        ._pvc_xmm[3] = _mm_loadu_si128(&addr[24]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
#endif
    };
}

static inline PVC_Vect8us
pvc_loadu_8us(uint16_t const* addr)
{
     return (PVC_Vect8us){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_loadu_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16us
pvc_loadu_16us(uint16_t const* addr)
{
     return (PVC_Vect16us){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[8]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect32us
pvc_loadu_32us(uint16_t const* addr)
{
     return (PVC_Vect32us){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_si256(&addr[16]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[8]),
        ._pvc_xmm[2] = _mm_loadu_si128(&addr[16]),
        ._pvc_xmm[3] = _mm_loadu_si128(&addr[24]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
        ._pvc_val[16] = addr[16],
        ._pvc_val[17] = addr[17],
        ._pvc_val[18] = addr[18],
        ._pvc_val[19] = addr[19],
        ._pvc_val[20] = addr[20],
        ._pvc_val[21] = addr[21],
        ._pvc_val[22] = addr[22],
        ._pvc_val[23] = addr[23],
        ._pvc_val[24] = addr[24],
        ._pvc_val[25] = addr[25],
        ._pvc_val[26] = addr[26],
        ._pvc_val[27] = addr[27],
        ._pvc_val[28] = addr[28],
        ._pvc_val[29] = addr[29],
        ._pvc_val[30] = addr[30],
        ._pvc_val[31] = addr[31],
#endif
    };
}

static inline PVC_Vect4i
pvc_loadu_4i(int32_t const* addr)
{
     return (PVC_Vect4i){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_loadu_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8i
pvc_loadu_8i(int32_t const* addr)
{
     return (PVC_Vect8i){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[4]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16i
pvc_loadu_16i(int32_t const* addr)
{
     return (PVC_Vect16i){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_si256(&addr[8]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[4]),
        ._pvc_xmm[2] = _mm_loadu_si128(&addr[8]),
        ._pvc_xmm[3] = _mm_loadu_si128(&addr[12]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect4ui
pvc_loadu_4ui(uint32_t const* addr)
{
     return (PVC_Vect4ui){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_loadu_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8ui
pvc_loadu_8ui(uint32_t const* addr)
{
     return (PVC_Vect8ui){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[4]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16ui
pvc_loadu_16ui(uint32_t const* addr)
{
     return (PVC_Vect16ui){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_si256(&addr[8]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[4]),
        ._pvc_xmm[2] = _mm_loadu_si128(&addr[8]),
        ._pvc_xmm[3] = _mm_loadu_si128(&addr[12]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect2l
pvc_loadu_2l(int64_t const* addr)
{
     return (PVC_Vect2l){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_loadu_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
#endif
    };
}

static inline PVC_Vect4l
pvc_loadu_4l(int64_t const* addr)
{
     return (PVC_Vect4l){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[2]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8l
pvc_loadu_8l(int64_t const* addr)
{
     return (PVC_Vect8l){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_si256(&addr[4]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[2]),
        ._pvc_xmm[2] = _mm_loadu_si128(&addr[4]),
        ._pvc_xmm[3] = _mm_loadu_si128(&addr[6]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect2ul
pvc_loadu_2ul(uint64_t const* addr)
{
     return (PVC_Vect2ul){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_loadu_si128(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
#endif
    };
}

static inline PVC_Vect4ul
pvc_loadu_4ul(uint64_t const* addr)
{
     return (PVC_Vect4ul){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_si256(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[2]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8ul
pvc_loadu_8ul(uint64_t const* addr)
{
     return (PVC_Vect8ul){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_si512(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_si256(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_si256(&addr[4]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_si128(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_si128(&addr[2]),
        ._pvc_xmm[2] = _mm_loadu_si128(&addr[4]),
        ._pvc_xmm[3] = _mm_loadu_si128(&addr[6]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect4f
pvc_loadu_4f(float const* addr)
{
     return (PVC_Vect4f){
#if defined(__SSE__)
        ._pvc_xmm = _mm_loadu_ps(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8f
pvc_loadu_8f(float const* addr)
{
     return (PVC_Vect8f){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_ps(addr),
#elif defined(__SSE__)
        ._pvc_xmm[0] = _mm_loadu_ps(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_ps(&addr[4]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

static inline PVC_Vect16f
pvc_loadu_16f(float const* addr)
{
     return (PVC_Vect16f){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_ps(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_ps(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_ps(&addr[8]),
#elif defined(__SSE__)
        ._pvc_xmm[0] = _mm_loadu_ps(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_ps(&addr[4]),
        ._pvc_xmm[2] = _mm_loadu_ps(&addr[8]),
        ._pvc_xmm[3] = _mm_loadu_ps(&addr[12]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
        ._pvc_val[8] = addr[8],
        ._pvc_val[9] = addr[9],
        ._pvc_val[10] = addr[10],
        ._pvc_val[11] = addr[11],
        ._pvc_val[12] = addr[12],
        ._pvc_val[13] = addr[13],
        ._pvc_val[14] = addr[14],
        ._pvc_val[15] = addr[15],
#endif
    };
}

static inline PVC_Vect2d
pvc_loadu_2d(double const* addr)
{
     return (PVC_Vect2d){
#if defined(__SSE2__)
        ._pvc_xmm = _mm_loadu_pd(addr),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
#endif
    };
}

static inline PVC_Vect4d
pvc_loadu_4d(double const* addr)
{
     return (PVC_Vect4d){
#if defined(__AVX__)
        ._pvc_ymm = _mm256_loadu_pd(addr),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_pd(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_pd(&addr[2]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
#endif
    };
}

static inline PVC_Vect8d
pvc_loadu_8d(double const* addr)
{
     return (PVC_Vect8d){
#if defined(__AVX512F__)
        ._pvc_zmm = _mm512_loadu_pd(addr),
#elif defined(__AVX__)
        ._pvc_ymm[0] = _mm256_loadu_pd(&addr[0]),
        ._pvc_ymm[1] = _mm256_loadu_pd(&addr[4]),
#elif defined(__SSE2__)
        ._pvc_xmm[0] = _mm_loadu_pd(&addr[0]),
        ._pvc_xmm[1] = _mm_loadu_pd(&addr[2]),
        ._pvc_xmm[2] = _mm_loadu_pd(&addr[4]),
        ._pvc_xmm[3] = _mm_loadu_pd(&addr[6]),
#else
        ._pvc_val[0] = addr[0],
        ._pvc_val[1] = addr[1],
        ._pvc_val[2] = addr[2],
        ._pvc_val[3] = addr[3],
        ._pvc_val[4] = addr[4],
        ._pvc_val[5] = addr[5],
        ._pvc_val[6] = addr[6],
        ._pvc_val[7] = addr[7],
#endif
    };
}

/**
 * @def pvc_loadp(T, n, addr)
 *
 * @brief Partial load of packed values from memory.
 *
 * Load @a n consecutive values of type @a T from address @a addr which may not be
 * aligned.
 */
#define pvc_loadp(T, n, addr)              \
    _Generic(*(T)0,                        \
             PVC_Vect16c:  pvc_loadp_16c,  \
             PVC_Vect32c:  pvc_loadp_32c,  \
             PVC_Vect64c:  pvc_loadp_64c,  \
             PVC_Vect16uc: pvc_loadp_16uc, \
             PVC_Vect32uc: pvc_loadp_32uc, \
             PVC_Vect64uc: pvc_loadp_64uc, \
             PVC_Vect8s:   pvc_loadp_8s,   \
             PVC_Vect16s:  pvc_loadp_16s,  \
             PVC_Vect32s:  pvc_loadp_32s,  \
             PVC_Vect8us:  pvc_loadp_8us,  \
             PVC_Vect16us: pvc_loadp_16us, \
             PVC_Vect32us: pvc_loadp_32us, \
             PVC_Vect4i:   pvc_loadp_4i,   \
             PVC_Vect8i:   pvc_loadp_8i,   \
             PVC_Vect16i:  pvc_loadp_16i,  \
             PVC_Vect4ui:  pvc_loadp_4ui,  \
             PVC_Vect8ui:  pvc_loadp_8ui,  \
             PVC_Vect16ui: pvc_loadp_16ui, \
             PVC_Vect2l:   pvc_loadp_2l,   \
             PVC_Vect4l:   pvc_loadp_4l,   \
             PVC_Vect8l:   pvc_loadp_8l,   \
             PVC_Vect2ul:  pvc_loadp_2ul,  \
             PVC_Vect4ul:  pvc_loadp_4ul,  \
             PVC_Vect8ul:  pvc_loadp_8ul,  \
             PVC_Vect4f:   pvc_loadp_4f,   \
             PVC_Vect8f:   pvc_loadp_8f,   \
             PVC_Vect16f:  pvc_loadp_16f,  \
             PVC_Vect2d:   pvc_loadp_2d,   \
             PVC_Vect4d:   pvc_loadp_4d,   \
             PVC_Vect8d:   pvc_loadp_8d)(n, addr)

/**
 * @def pvc_store(addr, vect)
 *
 * @brief Store packed values to aligned memory.
 *
 * Store packed values @a vect into memory at address @a addr which must be
 * aligned.
 */
#define pvc_store(addr, vect)              \
    _Generic((vect),                       \
             PVC_Vect16c:  pvc_store_16c,  \
             PVC_Vect32c:  pvc_store_32c,  \
             PVC_Vect64c:  pvc_store_64c,  \
             PVC_Vect16uc: pvc_store_16uc, \
             PVC_Vect32uc: pvc_store_32uc, \
             PVC_Vect64uc: pvc_store_64uc, \
             PVC_Vect8s:   pvc_store_8s,   \
             PVC_Vect16s:  pvc_store_16s,  \
             PVC_Vect32s:  pvc_store_32s,  \
             PVC_Vect8us:  pvc_store_8us,  \
             PVC_Vect16us: pvc_store_16us, \
             PVC_Vect32us: pvc_store_32us, \
             PVC_Vect4i:   pvc_store_4i,   \
             PVC_Vect8i:   pvc_store_8i,   \
             PVC_Vect16i:  pvc_store_16i,  \
             PVC_Vect4ui:  pvc_store_4ui,  \
             PVC_Vect8ui:  pvc_store_8ui,  \
             PVC_Vect16ui: pvc_store_16ui, \
             PVC_Vect2l:   pvc_store_2l,   \
             PVC_Vect4l:   pvc_store_4l,   \
             PVC_Vect8l:   pvc_store_8l,   \
             PVC_Vect2ul:  pvc_store_2ul,  \
             PVC_Vect4ul:  pvc_store_4ul,  \
             PVC_Vect8ul:  pvc_store_8ul,  \
             PVC_Vect4f:   pvc_store_4f,   \
             PVC_Vect8f:   pvc_store_8f,   \
             PVC_Vect16f:  pvc_store_16f,  \
             PVC_Vect2d:   pvc_store_2d,   \
             PVC_Vect4d:   pvc_store_4d,   \
             PVC_Vect8d:   pvc_store_8d)(addr, vect)

static inline void
pvc_store_16c(int8_t* addr, PVC_Vect16c vect)
{
#if defined(__SSE2__)
    _mm_store_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_store_32c(int8_t* addr, PVC_Vect32c vect)
{
#if defined(__AVX__)
    _mm256_store_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[16], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
#endif
}

static inline void
pvc_store_64c(int8_t* addr, PVC_Vect64c vect)
{
#if defined(__AVX512F__)
    _mm512_store_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_si256(&addr[32], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[16], vect._pvc_xmm[1]),
    _mm_store_si128(&addr[32], vect._pvc_xmm[2]),
    _mm_store_si128(&addr[48], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
    addr[32] = vect._pvc_val[32],
    addr[33] = vect._pvc_val[33],
    addr[34] = vect._pvc_val[34],
    addr[35] = vect._pvc_val[35],
    addr[36] = vect._pvc_val[36],
    addr[37] = vect._pvc_val[37],
    addr[38] = vect._pvc_val[38],
    addr[39] = vect._pvc_val[39],
    addr[40] = vect._pvc_val[40],
    addr[41] = vect._pvc_val[41],
    addr[42] = vect._pvc_val[42],
    addr[43] = vect._pvc_val[43],
    addr[44] = vect._pvc_val[44],
    addr[45] = vect._pvc_val[45],
    addr[46] = vect._pvc_val[46],
    addr[47] = vect._pvc_val[47],
    addr[48] = vect._pvc_val[48],
    addr[49] = vect._pvc_val[49],
    addr[50] = vect._pvc_val[50],
    addr[51] = vect._pvc_val[51],
    addr[52] = vect._pvc_val[52],
    addr[53] = vect._pvc_val[53],
    addr[54] = vect._pvc_val[54],
    addr[55] = vect._pvc_val[55],
    addr[56] = vect._pvc_val[56],
    addr[57] = vect._pvc_val[57],
    addr[58] = vect._pvc_val[58],
    addr[59] = vect._pvc_val[59],
    addr[60] = vect._pvc_val[60],
    addr[61] = vect._pvc_val[61],
    addr[62] = vect._pvc_val[62],
    addr[63] = vect._pvc_val[63],
#endif
}

static inline void
pvc_store_16uc(uint8_t* addr, PVC_Vect16uc vect)
{
#if defined(__SSE2__)
    _mm_store_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_store_32uc(uint8_t* addr, PVC_Vect32uc vect)
{
#if defined(__AVX__)
    _mm256_store_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[16], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
#endif
}

static inline void
pvc_store_64uc(uint8_t* addr, PVC_Vect64uc vect)
{
#if defined(__AVX512F__)
    _mm512_store_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_si256(&addr[32], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[16], vect._pvc_xmm[1]),
    _mm_store_si128(&addr[32], vect._pvc_xmm[2]),
    _mm_store_si128(&addr[48], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
    addr[32] = vect._pvc_val[32],
    addr[33] = vect._pvc_val[33],
    addr[34] = vect._pvc_val[34],
    addr[35] = vect._pvc_val[35],
    addr[36] = vect._pvc_val[36],
    addr[37] = vect._pvc_val[37],
    addr[38] = vect._pvc_val[38],
    addr[39] = vect._pvc_val[39],
    addr[40] = vect._pvc_val[40],
    addr[41] = vect._pvc_val[41],
    addr[42] = vect._pvc_val[42],
    addr[43] = vect._pvc_val[43],
    addr[44] = vect._pvc_val[44],
    addr[45] = vect._pvc_val[45],
    addr[46] = vect._pvc_val[46],
    addr[47] = vect._pvc_val[47],
    addr[48] = vect._pvc_val[48],
    addr[49] = vect._pvc_val[49],
    addr[50] = vect._pvc_val[50],
    addr[51] = vect._pvc_val[51],
    addr[52] = vect._pvc_val[52],
    addr[53] = vect._pvc_val[53],
    addr[54] = vect._pvc_val[54],
    addr[55] = vect._pvc_val[55],
    addr[56] = vect._pvc_val[56],
    addr[57] = vect._pvc_val[57],
    addr[58] = vect._pvc_val[58],
    addr[59] = vect._pvc_val[59],
    addr[60] = vect._pvc_val[60],
    addr[61] = vect._pvc_val[61],
    addr[62] = vect._pvc_val[62],
    addr[63] = vect._pvc_val[63],
#endif
}

static inline void
pvc_store_8s(int16_t* addr, PVC_Vect8s vect)
{
#if defined(__SSE2__)
    _mm_store_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_store_16s(int16_t* addr, PVC_Vect16s vect)
{
#if defined(__AVX__)
    _mm256_store_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[8], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_store_32s(int16_t* addr, PVC_Vect32s vect)
{
#if defined(__AVX512F__)
    _mm512_store_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_si256(&addr[16], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[8], vect._pvc_xmm[1]),
    _mm_store_si128(&addr[16], vect._pvc_xmm[2]),
    _mm_store_si128(&addr[24], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
#endif
}

static inline void
pvc_store_8us(uint16_t* addr, PVC_Vect8us vect)
{
#if defined(__SSE2__)
    _mm_store_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_store_16us(uint16_t* addr, PVC_Vect16us vect)
{
#if defined(__AVX__)
    _mm256_store_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[8], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_store_32us(uint16_t* addr, PVC_Vect32us vect)
{
#if defined(__AVX512F__)
    _mm512_store_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_si256(&addr[16], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[8], vect._pvc_xmm[1]),
    _mm_store_si128(&addr[16], vect._pvc_xmm[2]),
    _mm_store_si128(&addr[24], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
#endif
}

static inline void
pvc_store_4i(int32_t* addr, PVC_Vect4i vect)
{
#if defined(__SSE2__)
    _mm_store_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_store_8i(int32_t* addr, PVC_Vect8i vect)
{
#if defined(__AVX__)
    _mm256_store_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[4], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_store_16i(int32_t* addr, PVC_Vect16i vect)
{
#if defined(__AVX512F__)
    _mm512_store_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_si256(&addr[8], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[4], vect._pvc_xmm[1]),
    _mm_store_si128(&addr[8], vect._pvc_xmm[2]),
    _mm_store_si128(&addr[12], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_store_4ui(uint32_t* addr, PVC_Vect4ui vect)
{
#if defined(__SSE2__)
    _mm_store_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_store_8ui(uint32_t* addr, PVC_Vect8ui vect)
{
#if defined(__AVX__)
    _mm256_store_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[4], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_store_16ui(uint32_t* addr, PVC_Vect16ui vect)
{
#if defined(__AVX512F__)
    _mm512_store_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_si256(&addr[8], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[4], vect._pvc_xmm[1]),
    _mm_store_si128(&addr[8], vect._pvc_xmm[2]),
    _mm_store_si128(&addr[12], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_store_2l(int64_t* addr, PVC_Vect2l vect)
{
#if defined(__SSE2__)
    _mm_store_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
#endif
}

static inline void
pvc_store_4l(int64_t* addr, PVC_Vect4l vect)
{
#if defined(__AVX__)
    _mm256_store_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[2], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_store_8l(int64_t* addr, PVC_Vect8l vect)
{
#if defined(__AVX512F__)
    _mm512_store_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_si256(&addr[4], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[2], vect._pvc_xmm[1]),
    _mm_store_si128(&addr[4], vect._pvc_xmm[2]),
    _mm_store_si128(&addr[6], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_store_2ul(uint64_t* addr, PVC_Vect2ul vect)
{
#if defined(__SSE2__)
    _mm_store_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
#endif
}

static inline void
pvc_store_4ul(uint64_t* addr, PVC_Vect4ul vect)
{
#if defined(__AVX__)
    _mm256_store_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[2], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_store_8ul(uint64_t* addr, PVC_Vect8ul vect)
{
#if defined(__AVX512F__)
    _mm512_store_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_si256(&addr[4], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_store_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_store_si128(&addr[2], vect._pvc_xmm[1]),
    _mm_store_si128(&addr[4], vect._pvc_xmm[2]),
    _mm_store_si128(&addr[6], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_store_4f(float* addr, PVC_Vect4f vect)
{
#if defined(__SSE__)
    _mm_store_ps(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_store_8f(float* addr, PVC_Vect8f vect)
{
#if defined(__AVX__)
    _mm256_store_ps(addr, vect._pvc_ymm),
#elif defined(__SSE__)
    _mm_store_ps(&addr[0], vect._pvc_xmm[0]),
    _mm_store_ps(&addr[4], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_store_16f(float* addr, PVC_Vect16f vect)
{
#if defined(__AVX512F__)
    _mm512_store_ps(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_ps(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_ps(&addr[8], vect._pvc_ymm[1]),
#elif defined(__SSE__)
    _mm_store_ps(&addr[0], vect._pvc_xmm[0]),
    _mm_store_ps(&addr[4], vect._pvc_xmm[1]),
    _mm_store_ps(&addr[8], vect._pvc_xmm[2]),
    _mm_store_ps(&addr[12], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_store_2d(double* addr, PVC_Vect2d vect)
{
#if defined(__SSE2__)
    _mm_store_pd(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
#endif
}

static inline void
pvc_store_4d(double* addr, PVC_Vect4d vect)
{
#if defined(__AVX__)
    _mm256_store_pd(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_store_pd(&addr[0], vect._pvc_xmm[0]),
    _mm_store_pd(&addr[2], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_store_8d(double* addr, PVC_Vect8d vect)
{
#if defined(__AVX512F__)
    _mm512_store_pd(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_store_pd(&addr[0], vect._pvc_ymm[0]),
    _mm256_store_pd(&addr[4], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_store_pd(&addr[0], vect._pvc_xmm[0]),
    _mm_store_pd(&addr[2], vect._pvc_xmm[1]),
    _mm_store_pd(&addr[4], vect._pvc_xmm[2]),
    _mm_store_pd(&addr[6], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

/**
 * @def pvc_storeu(addr, vect)
 *
 * @brief Store packed values to memory.
 *
 * Store packed values @a vect into memory at address @a addr which may not be
 * aligned.
 */
#define pvc_storeu(addr, vect)              \
    _Generic((vect),                        \
             PVC_Vect16c:  pvc_storeu_16c,  \
             PVC_Vect32c:  pvc_storeu_32c,  \
             PVC_Vect64c:  pvc_storeu_64c,  \
             PVC_Vect16uc: pvc_storeu_16uc, \
             PVC_Vect32uc: pvc_storeu_32uc, \
             PVC_Vect64uc: pvc_storeu_64uc, \
             PVC_Vect8s:   pvc_storeu_8s,   \
             PVC_Vect16s:  pvc_storeu_16s,  \
             PVC_Vect32s:  pvc_storeu_32s,  \
             PVC_Vect8us:  pvc_storeu_8us,  \
             PVC_Vect16us: pvc_storeu_16us, \
             PVC_Vect32us: pvc_storeu_32us, \
             PVC_Vect4i:   pvc_storeu_4i,   \
             PVC_Vect8i:   pvc_storeu_8i,   \
             PVC_Vect16i:  pvc_storeu_16i,  \
             PVC_Vect4ui:  pvc_storeu_4ui,  \
             PVC_Vect8ui:  pvc_storeu_8ui,  \
             PVC_Vect16ui: pvc_storeu_16ui, \
             PVC_Vect2l:   pvc_storeu_2l,   \
             PVC_Vect4l:   pvc_storeu_4l,   \
             PVC_Vect8l:   pvc_storeu_8l,   \
             PVC_Vect2ul:  pvc_storeu_2ul,  \
             PVC_Vect4ul:  pvc_storeu_4ul,  \
             PVC_Vect8ul:  pvc_storeu_8ul,  \
             PVC_Vect4f:   pvc_storeu_4f,   \
             PVC_Vect8f:   pvc_storeu_8f,   \
             PVC_Vect16f:  pvc_storeu_16f,  \
             PVC_Vect2d:   pvc_storeu_2d,   \
             PVC_Vect4d:   pvc_storeu_4d,   \
             PVC_Vect8d:   pvc_storeu_8d)(addr, vect)

static inline void
pvc_storeu_16c(int8_t* addr, PVC_Vect16c vect)
{
#if defined(__SSE2__)
    _mm_storeu_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_storeu_32c(int8_t* addr, PVC_Vect32c vect)
{
#if defined(__AVX__)
    _mm256_storeu_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[16], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
#endif
}

static inline void
pvc_storeu_64c(int8_t* addr, PVC_Vect64c vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_si256(&addr[32], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[16], vect._pvc_xmm[1]),
    _mm_storeu_si128(&addr[32], vect._pvc_xmm[2]),
    _mm_storeu_si128(&addr[48], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
    addr[32] = vect._pvc_val[32],
    addr[33] = vect._pvc_val[33],
    addr[34] = vect._pvc_val[34],
    addr[35] = vect._pvc_val[35],
    addr[36] = vect._pvc_val[36],
    addr[37] = vect._pvc_val[37],
    addr[38] = vect._pvc_val[38],
    addr[39] = vect._pvc_val[39],
    addr[40] = vect._pvc_val[40],
    addr[41] = vect._pvc_val[41],
    addr[42] = vect._pvc_val[42],
    addr[43] = vect._pvc_val[43],
    addr[44] = vect._pvc_val[44],
    addr[45] = vect._pvc_val[45],
    addr[46] = vect._pvc_val[46],
    addr[47] = vect._pvc_val[47],
    addr[48] = vect._pvc_val[48],
    addr[49] = vect._pvc_val[49],
    addr[50] = vect._pvc_val[50],
    addr[51] = vect._pvc_val[51],
    addr[52] = vect._pvc_val[52],
    addr[53] = vect._pvc_val[53],
    addr[54] = vect._pvc_val[54],
    addr[55] = vect._pvc_val[55],
    addr[56] = vect._pvc_val[56],
    addr[57] = vect._pvc_val[57],
    addr[58] = vect._pvc_val[58],
    addr[59] = vect._pvc_val[59],
    addr[60] = vect._pvc_val[60],
    addr[61] = vect._pvc_val[61],
    addr[62] = vect._pvc_val[62],
    addr[63] = vect._pvc_val[63],
#endif
}

static inline void
pvc_storeu_16uc(uint8_t* addr, PVC_Vect16uc vect)
{
#if defined(__SSE2__)
    _mm_storeu_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_storeu_32uc(uint8_t* addr, PVC_Vect32uc vect)
{
#if defined(__AVX__)
    _mm256_storeu_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[16], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
#endif
}

static inline void
pvc_storeu_64uc(uint8_t* addr, PVC_Vect64uc vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_si256(&addr[32], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[16], vect._pvc_xmm[1]),
    _mm_storeu_si128(&addr[32], vect._pvc_xmm[2]),
    _mm_storeu_si128(&addr[48], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
    addr[32] = vect._pvc_val[32],
    addr[33] = vect._pvc_val[33],
    addr[34] = vect._pvc_val[34],
    addr[35] = vect._pvc_val[35],
    addr[36] = vect._pvc_val[36],
    addr[37] = vect._pvc_val[37],
    addr[38] = vect._pvc_val[38],
    addr[39] = vect._pvc_val[39],
    addr[40] = vect._pvc_val[40],
    addr[41] = vect._pvc_val[41],
    addr[42] = vect._pvc_val[42],
    addr[43] = vect._pvc_val[43],
    addr[44] = vect._pvc_val[44],
    addr[45] = vect._pvc_val[45],
    addr[46] = vect._pvc_val[46],
    addr[47] = vect._pvc_val[47],
    addr[48] = vect._pvc_val[48],
    addr[49] = vect._pvc_val[49],
    addr[50] = vect._pvc_val[50],
    addr[51] = vect._pvc_val[51],
    addr[52] = vect._pvc_val[52],
    addr[53] = vect._pvc_val[53],
    addr[54] = vect._pvc_val[54],
    addr[55] = vect._pvc_val[55],
    addr[56] = vect._pvc_val[56],
    addr[57] = vect._pvc_val[57],
    addr[58] = vect._pvc_val[58],
    addr[59] = vect._pvc_val[59],
    addr[60] = vect._pvc_val[60],
    addr[61] = vect._pvc_val[61],
    addr[62] = vect._pvc_val[62],
    addr[63] = vect._pvc_val[63],
#endif
}

static inline void
pvc_storeu_8s(int16_t* addr, PVC_Vect8s vect)
{
#if defined(__SSE2__)
    _mm_storeu_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_storeu_16s(int16_t* addr, PVC_Vect16s vect)
{
#if defined(__AVX__)
    _mm256_storeu_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[8], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_storeu_32s(int16_t* addr, PVC_Vect32s vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_si256(&addr[16], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[8], vect._pvc_xmm[1]),
    _mm_storeu_si128(&addr[16], vect._pvc_xmm[2]),
    _mm_storeu_si128(&addr[24], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
#endif
}

static inline void
pvc_storeu_8us(uint16_t* addr, PVC_Vect8us vect)
{
#if defined(__SSE2__)
    _mm_storeu_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_storeu_16us(uint16_t* addr, PVC_Vect16us vect)
{
#if defined(__AVX__)
    _mm256_storeu_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[8], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_storeu_32us(uint16_t* addr, PVC_Vect32us vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_si256(&addr[16], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[8], vect._pvc_xmm[1]),
    _mm_storeu_si128(&addr[16], vect._pvc_xmm[2]),
    _mm_storeu_si128(&addr[24], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
    addr[16] = vect._pvc_val[16],
    addr[17] = vect._pvc_val[17],
    addr[18] = vect._pvc_val[18],
    addr[19] = vect._pvc_val[19],
    addr[20] = vect._pvc_val[20],
    addr[21] = vect._pvc_val[21],
    addr[22] = vect._pvc_val[22],
    addr[23] = vect._pvc_val[23],
    addr[24] = vect._pvc_val[24],
    addr[25] = vect._pvc_val[25],
    addr[26] = vect._pvc_val[26],
    addr[27] = vect._pvc_val[27],
    addr[28] = vect._pvc_val[28],
    addr[29] = vect._pvc_val[29],
    addr[30] = vect._pvc_val[30],
    addr[31] = vect._pvc_val[31],
#endif
}

static inline void
pvc_storeu_4i(int32_t* addr, PVC_Vect4i vect)
{
#if defined(__SSE2__)
    _mm_storeu_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_storeu_8i(int32_t* addr, PVC_Vect8i vect)
{
#if defined(__AVX__)
    _mm256_storeu_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[4], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_storeu_16i(int32_t* addr, PVC_Vect16i vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_si256(&addr[8], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[4], vect._pvc_xmm[1]),
    _mm_storeu_si128(&addr[8], vect._pvc_xmm[2]),
    _mm_storeu_si128(&addr[12], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_storeu_4ui(uint32_t* addr, PVC_Vect4ui vect)
{
#if defined(__SSE2__)
    _mm_storeu_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_storeu_8ui(uint32_t* addr, PVC_Vect8ui vect)
{
#if defined(__AVX__)
    _mm256_storeu_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[4], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_storeu_16ui(uint32_t* addr, PVC_Vect16ui vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_si256(&addr[8], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[4], vect._pvc_xmm[1]),
    _mm_storeu_si128(&addr[8], vect._pvc_xmm[2]),
    _mm_storeu_si128(&addr[12], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_storeu_2l(int64_t* addr, PVC_Vect2l vect)
{
#if defined(__SSE2__)
    _mm_storeu_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
#endif
}

static inline void
pvc_storeu_4l(int64_t* addr, PVC_Vect4l vect)
{
#if defined(__AVX__)
    _mm256_storeu_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[2], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_storeu_8l(int64_t* addr, PVC_Vect8l vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_si256(&addr[4], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[2], vect._pvc_xmm[1]),
    _mm_storeu_si128(&addr[4], vect._pvc_xmm[2]),
    _mm_storeu_si128(&addr[6], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_storeu_2ul(uint64_t* addr, PVC_Vect2ul vect)
{
#if defined(__SSE2__)
    _mm_storeu_si128(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
#endif
}

static inline void
pvc_storeu_4ul(uint64_t* addr, PVC_Vect4ul vect)
{
#if defined(__AVX__)
    _mm256_storeu_si256(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[2], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_storeu_8ul(uint64_t* addr, PVC_Vect8ul vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_si512(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_si256(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_si256(&addr[4], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_storeu_si128(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_si128(&addr[2], vect._pvc_xmm[1]),
    _mm_storeu_si128(&addr[4], vect._pvc_xmm[2]),
    _mm_storeu_si128(&addr[6], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_storeu_4f(float* addr, PVC_Vect4f vect)
{
#if defined(__SSE__)
    _mm_storeu_ps(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_storeu_8f(float* addr, PVC_Vect8f vect)
{
#if defined(__AVX__)
    _mm256_storeu_ps(addr, vect._pvc_ymm),
#elif defined(__SSE__)
    _mm_storeu_ps(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_ps(&addr[4], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

static inline void
pvc_storeu_16f(float* addr, PVC_Vect16f vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_ps(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_ps(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_ps(&addr[8], vect._pvc_ymm[1]),
#elif defined(__SSE__)
    _mm_storeu_ps(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_ps(&addr[4], vect._pvc_xmm[1]),
    _mm_storeu_ps(&addr[8], vect._pvc_xmm[2]),
    _mm_storeu_ps(&addr[12], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
    addr[8] = vect._pvc_val[8],
    addr[9] = vect._pvc_val[9],
    addr[10] = vect._pvc_val[10],
    addr[11] = vect._pvc_val[11],
    addr[12] = vect._pvc_val[12],
    addr[13] = vect._pvc_val[13],
    addr[14] = vect._pvc_val[14],
    addr[15] = vect._pvc_val[15],
#endif
}

static inline void
pvc_storeu_2d(double* addr, PVC_Vect2d vect)
{
#if defined(__SSE2__)
    _mm_storeu_pd(addr, vect._pvc_xmm),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
#endif
}

static inline void
pvc_storeu_4d(double* addr, PVC_Vect4d vect)
{
#if defined(__AVX__)
    _mm256_storeu_pd(addr, vect._pvc_ymm),
#elif defined(__SSE2__)
    _mm_storeu_pd(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_pd(&addr[2], vect._pvc_xmm[1]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
#endif
}

static inline void
pvc_storeu_8d(double* addr, PVC_Vect8d vect)
{
#if defined(__AVX512F__)
    _mm512_storeu_pd(addr, vect._pvc_zmm),
#elif defined(__AVX__)
    _mm256_storeu_pd(&addr[0], vect._pvc_ymm[0]),
    _mm256_storeu_pd(&addr[4], vect._pvc_ymm[1]),
#elif defined(__SSE2__)
    _mm_storeu_pd(&addr[0], vect._pvc_xmm[0]),
    _mm_storeu_pd(&addr[2], vect._pvc_xmm[1]),
    _mm_storeu_pd(&addr[4], vect._pvc_xmm[2]),
    _mm_storeu_pd(&addr[6], vect._pvc_xmm[3]),
#else
    addr[0] = vect._pvc_val[0],
    addr[1] = vect._pvc_val[1],
    addr[2] = vect._pvc_val[2],
    addr[3] = vect._pvc_val[3],
    addr[4] = vect._pvc_val[4],
    addr[5] = vect._pvc_val[5],
    addr[6] = vect._pvc_val[6],
    addr[7] = vect._pvc_val[7],
#endif
}

/**
 * @def pvc_storep(addr, n, vect)
 *
 * @brief Partial store of packed values to memory.
 *
 * Store the @a n first values of @a vect to memory at address @a addr which may not be
 * aligned.
 */
#define pvc_storep(addr, n, vect)           \
    _Generic((vect),                        \
             PVC_Vect16c:  pvc_storep_16c,  \
             PVC_Vect32c:  pvc_storep_32c,  \
             PVC_Vect64c:  pvc_storep_64c,  \
             PVC_Vect16uc: pvc_storep_16uc, \
             PVC_Vect32uc: pvc_storep_32uc, \
             PVC_Vect64uc: pvc_storep_64uc, \
             PVC_Vect8s:   pvc_storep_8s,   \
             PVC_Vect16s:  pvc_storep_16s,  \
             PVC_Vect32s:  pvc_storep_32s,  \
             PVC_Vect8us:  pvc_storep_8us,  \
             PVC_Vect16us: pvc_storep_16us, \
             PVC_Vect32us: pvc_storep_32us, \
             PVC_Vect4i:   pvc_storep_4i,   \
             PVC_Vect8i:   pvc_storep_8i,   \
             PVC_Vect16i:  pvc_storep_16i,  \
             PVC_Vect4ui:  pvc_storep_4ui,  \
             PVC_Vect8ui:  pvc_storep_8ui,  \
             PVC_Vect16ui: pvc_storep_16ui, \
             PVC_Vect2l:   pvc_storep_2l,   \
             PVC_Vect4l:   pvc_storep_4l,   \
             PVC_Vect8l:   pvc_storep_8l,   \
             PVC_Vect2ul:  pvc_storep_2ul,  \
             PVC_Vect4ul:  pvc_storep_4ul,  \
             PVC_Vect8ul:  pvc_storep_8ul,  \
             PVC_Vect4f:   pvc_storep_4f,   \
             PVC_Vect8f:   pvc_storep_8f,   \
             PVC_Vect16f:  pvc_storep_16f,  \
             PVC_Vect2d:   pvc_storep_2d,   \
             PVC_Vect4d:   pvc_storep_4d,   \
             PVC_Vect8d:   pvc_storep_8d)(addr, n, vect)
/** @} */

#endif /* _PVC_VECT_H */
