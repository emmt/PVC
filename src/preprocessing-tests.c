/*
 * preprocessing-tests.c -
 *
 * Test performances of image pre-processing.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#include <pvc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include "preprocessing.h"
#if USE_PAPI
#  include <papi.h>
#endif

#ifndef COMPILER_COMMAND
#  warning "Compiler command should be specified by COMPILER_COMMAND"
#  define COMPILER_COMMAND "unknown"
#endif
#ifndef COMPILER_VERSION
#  define COMPILER_VERSION PVC_COMPILER_VERSION
#endif
#ifndef FLOAT
#  define FLOAT float
#endif
#ifndef PIXEL
#  define PIXEL uint8_t
#endif
#ifndef WIDTH
#  define WIDTH 380
#endif
#ifndef STRIDE
#  define STRIDE 400
#endif
#ifndef HEIGHT
#  define HEIGHT 380
#endif
#if WIDTH < 1
#  error "Invalid WIDTH (must be >= 1)."
#endif
#if HEIGHT < 1
#  error "Invalid HEIGHT (must be >= 1)."
#endif
#if STRIDE < WIDTH
#  error "Invalid STRIDE (must be >= WIDTH)."
#endif

/* Number of warmup iterations. */
#ifndef WARMUP
#  define WARMUP 50000
#endif

/* Number of iterations to estimate timings. */
#ifndef REPEAT
#  define REPEAT 10000
#endif


//#define GET_TIMESPEC(ts) timespec_get(ts, TIME_UTC)
//#define GET_TIMESPEC(ts) clock_gettime(CLOCK_REALTIME, ts)
#define GET_TIMESPEC(ts) clock_gettime(CLOCK_MONOTONIC, ts)

static void print_results(FILE* output, char const* func,
                          PVC_TimeStatData const* tsd,
                          bool verbose)
{
    double const scl = 1E6; // print timings in microseconds
    PVC_TimeStat ts;
    pvc_time_stat_compute(&ts, tsd);
    if (verbose) {
        fprintf(output, "Results for %s:\n", func);
        pvc_time_stat_print(output, "  ", &ts);
    } else {
        fprintf(output, "%25s %10.3f %10.3f %10.3f %10.3f\n",
                func, ts.min*scl, ts.max*scl,
                ts.avg*scl, ts.std*scl);
    }
    fflush(output);
}

int
main(int argc, char* argv[argc+1])
{
    long width = WIDTH;
    long height = HEIGHT;
    long stride = STRIDE;
    long warmup = WARMUP;
    long repeat = REPEAT;
    bool verbose = false;
    char dummy;

    for (int i = 1; i < argc; ++i) {
        int n;
        n = sscanf(argv[i], "--width=%ld %c", &width, &dummy);
        if (n > 0) {
            if (n != 1 || width < 1) {
                fprintf(stderr, "Invalid argument of --width option.\n");
                return EXIT_FAILURE;
            }
            continue;
        }
        n = sscanf(argv[i], "--height=%ld %c", &height, &dummy);
        if (n > 0) {
            if (n != 1 || height < 1) {
                fprintf(stderr, "Invalid argument of --height option.\n");
                return EXIT_FAILURE;
            }
            continue;
        }
        n = sscanf(argv[i], "--stride=%ld %c", &stride, &dummy);
        if (n > 0) {
            if (n != 1 || stride < 1) {
                fprintf(stderr, "Invalid argument of --stride option.\n");
                return EXIT_FAILURE;
            }
            continue;
        }
        n = sscanf(argv[i], "--warmup=%ld %c", &warmup, &dummy);
        if (n > 0) {
            if (n != 1 || warmup < 0) {
                fprintf(stderr, "Invalid argument of --warmup option.\n");
                return EXIT_FAILURE;
            }
            continue;
        }
        n = sscanf(argv[i], "--repeat=%ld %c", &repeat, &dummy);
        if (n > 0) {
            if (n != 1 || repeat < 1) {
                fprintf(stderr, "Invalid argument of --repeat option.\n");
                return EXIT_FAILURE;
            }
            continue;
        }
        if (strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
            continue;
        }
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Usage: %s [OPTIONS]\n", argv[0]);
            printf("    Measure execution times of variants of image "
                   "pre-processing\n    methods.\n");
            printf("Options:\n");
            printf("  --width=WIDTH    Number of pixels per row [%ld]\n",
                   (long)WIDTH);
            printf("  --height=HEIGHT  Number of pixel rows [%ld]\n",
                   (long)HEIGHT);
            printf("  --stride=STRIDE  Raw image stride [%ld]\n",
                   (long)STRIDE);
            printf("  --warmup=WARMUP  Number of warmup calls [%ld]\n",
                   (long)WARMUP);
            printf("  --repeat=REPEAT  Number of calls to measure [%ld]\n",
                   (long)REPEAT);
            printf("  --verbose        Print results in verbose format.\n");
            printf("  --help, -h       Print this help.\n");
            return EXIT_SUCCESS;
        }
        if (strcmp(argv[i], "--") != 0 || i < argc - 1) {
            fprintf(stderr, "Unknown option or too many arguments.\n");
            return EXIT_FAILURE;
        }
    }
    if (stride < width) {
        fprintf(stderr, "Stride must be at least equal to width.\n");
        return EXIT_FAILURE;
    }

    FILE* output = stdout;
#if USE_PAPI
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        fprintf(stderr, "PAPI_library_init() failed\n");
        return EXIT_FAILURE;
    }
#endif
    PIXEL* raw = malloc((stride*height)*sizeof(PIXEL));
    FLOAT* wgt = malloc((width*height)*sizeof(FLOAT));
    FLOAT* dat = malloc((width*height)*sizeof(FLOAT));
    FLOAT* A = malloc((width*height)*sizeof(FLOAT));
    FLOAT* B = malloc((width*height)*sizeof(FLOAT));
    FLOAT* Q = malloc((width*height)*sizeof(FLOAT));
    FLOAT* R = malloc((width*height)*sizeof(FLOAT));
    int status = EXIT_SUCCESS;
    if (raw == NULL || wgt == NULL || dat == NULL ||
	A == NULL || B == NULL || Q == NULL || R == NULL) {
        fprintf(stderr, "Insufficient memory\n");
        status = EXIT_FAILURE;
    }
    if (status != EXIT_SUCCESS) {
        goto done;
    }
#define raw(i,j) raw[(i) + (stride)*(j)]
#define wgt(i,j) wgt[(i) + (width)*(j)]
#define dat(i,j) dat[(i) + (width)*(j)]
#define A(i,j)   A[(i) + (width)*(j)]
#define B(i,j)   B[(i) + (width)*(j)]
#define Q(i,j)   Q[(i) + (width)*(j)]
#define R(i,j)   R[(i) + (width)*(j)]

    for (size_t y = 0; y < height; ++y) {
	for (size_t x = 0; x < width; ++x) {
	    raw(x,y) = x + y;
	    wgt(x,y) = 1;
	    dat(x,y) = 0;
	    A(x,y) = 1;
	    B(x,y) = 0;
	    Q(x,y) = 1;
	    R(x,y) = 0.01;
	}
    }

    //printf("Results for %s:\n", "clock_gettime");
    //pvc_time_stat_print(output, "  ", &tm[0]);
    if (!verbose) {
        fprintf(output,
                "# Timings for pre-processing of acquired images.\n"
                "#\n"
                "#   Compiled with: %s\n"
                "#   Compiler version: %s\n"
                "#   Image width:  %4ld pixels\n"
                "#   Image height: %4ld pixels\n"
                "#   Image stride: %4ld pixels\n"
                "#   Number of warmups:      %ld\n"
                "#   Number of measurements: %ld\n"
                "#\n",
                COMPILER_COMMAND,
                COMPILER_VERSION,
                width, height, stride, warmup, repeat);
        fprintf(output, "#%s\n#%s\n",
                "        Method             Min (µs)   Max (µs)   Avg (µs)   Std (µs)",
                "--------------------------------------------------------------------");
        fflush(output);
    }
#define TEST(func)                                                      \
    do {                                                                \
        /* warm-up */                                                   \
        struct timespec t0;                                             \
        struct timespec t1;                                             \
        double t = 0;                                                   \
        for (int j = 0; j < warmup; ++j) {                              \
            GET_TIMESPEC(&t0);                                          \
            func(width, height, stride, wgt, dat, raw, A, B, Q, R);     \
            GET_TIMESPEC(&t1);                                          \
            t += pvc_elapsed_seconds(&t1, &t0);                         \
        }                                                               \
        /* measurements */                                              \
        PVC_TimeStatData tsd;                                           \
        pvc_time_stat_init(&tsd);                                       \
        for (int j = 0; j < repeat; ++j) {                              \
            GET_TIMESPEC(&t0);                                          \
            func(width, height, stride, wgt, dat, raw, A, B, Q, R);     \
            GET_TIMESPEC(&t1);                                          \
            pvc_time_stat_update(&tsd, pvc_elapsed_seconds(&t1, &t0));  \
        }                                                               \
        print_results(output, #func, &tsd, verbose);                    \
    } while (0)

    TEST(preprocess_v11_uc_f);
    TEST(preprocess_v21_uc_f);
    TEST(preprocess_v31_uc_f);
    TEST(preprocess_v41_uc_f);

    TEST(preprocess_v12_uc_f);
    TEST(preprocess_v22_uc_f);
    TEST(preprocess_v32_uc_f);
    TEST(preprocess_v42_uc_f);

    TEST(preprocess_v13_uc_f);
    TEST(preprocess_v23_uc_f);
    TEST(preprocess_v33_uc_f);
    TEST(preprocess_v43_uc_f);

    TEST(preprocess_v14_uc_f);
    TEST(preprocess_v24_uc_f);
    TEST(preprocess_v34_uc_f);
    TEST(preprocess_v44_uc_f);

    TEST(preprocess_v15_uc_f);
    TEST(preprocess_v25_uc_f);
    TEST(preprocess_v35_uc_f);
    TEST(preprocess_v45_uc_f);

    TEST(preprocess_v16_uc_f);
    TEST(preprocess_v26_uc_f);
    TEST(preprocess_v36_uc_f);
    TEST(preprocess_v46_uc_f);

    TEST(preprocess_v17_uc_f);
    TEST(preprocess_v27_uc_f);
    TEST(preprocess_v37_uc_f);
    TEST(preprocess_v47_uc_f);

 done:
    free(raw);
    free(wgt);
    free(dat);
    free(A);
    free(B);
    free(Q);
    free(R);
    return status;
}
