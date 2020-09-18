/*
 * types-tests.c -
 *
 * C code for testing macros and functions related to numerical types.
 *
 *-----------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pvc-types.h"

#if 0
static char const*
type_name(int id)
{
    switch (id) {
    case PVC_TYPE_ID_BOOL:               return "bool";
    case PVC_TYPE_ID_CHAR:               return "char";
    case PVC_TYPE_ID_SIGNED_CHAR:        return "signed char";
    case PVC_TYPE_ID_UNSIGNED_CHAR:      return "unsigned char";
    case PVC_TYPE_ID_SHORT:              return "short";
    case PVC_TYPE_ID_UNSIGNED_SHORT:     return "unsigned short";
    case PVC_TYPE_ID_INT:                return "int";
    case PVC_TYPE_ID_UNSIGNED_INT:       return "unsigned int";
    case PVC_TYPE_ID_LONG:               return "long";
    case PVC_TYPE_ID_UNSIGNED_LONG:      return "unsigned long";
    case PVC_TYPE_ID_LONG_LONG:          return "long long";
    case PVC_TYPE_ID_UNSIGNED_LONG_LONG: return "unsigned long long";
    case PVC_TYPE_ID_FLOAT:              return "float";
    case PVC_TYPE_ID_DOUBLE:             return "double";
    case PVC_TYPE_ID_LONG_DOUBLE:        return "long double";
    default:                             return "<other>";
    }
}
#endif

int main(int argc, char* argv[])
{
    bool verbose = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--verbose") == 0 ||
            strcmp(argv[i], "-V") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "--help") == 0 ||
                   strcmp(argv[i], "-h") == 0) {
            printf("%s [OPTIONS ...] [--]\n", argv[0]);
            printf("Run tests.  Options are:\n");
            printf("  -h, --help     Print this help.\n");
            printf("  -V, --verbose  Verbose mode.\n");
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "--") != 0) {
            fprintf(stderr, "%s: too many arguments (try with --help)\n",
                    argv[0]);
            return EXIT_FAILURE;
        }
    }

    long ntests = 0;
    long nfailures = 0;
#define TEST(expr, result)                                      \
    do {                                                        \
        ++ntests;                                               \
        if ((expr) == (result)) {                               \
            if (verbose) {                                      \
                printf("OK: %s -> %s\n", #expr, #result);       \
            }                                                   \
        } else {                                                \
            ++nfailures;                                        \
            if (verbose) {                                      \
                printf("ERROR: %s != %s\n", #expr, #result);    \
            }                                                   \
        }                                                       \
    } while (0)

    TEST(PVC_TYPE_ID(double),  PVC_TYPE_ID_DOUBLE);
    TEST(PVC_TYPE_ID(const double), PVC_TYPE_ID_DOUBLE);
    TEST(PVC_TYPE_ID(volatile double), PVC_TYPE_ID_DOUBLE);
    TEST(PVC_TYPE_ID(double*), PVC_TYPE_ID_OTHER);

    TEST(PVC_IS_FLOAT(double), false);
    TEST(PVC_IS_FLOAT(const double), false);
    TEST(PVC_IS_FLOAT(volatile double), false);
    TEST(PVC_IS_FLOAT(double*), false);

    TEST(PVC_IS_DOUBLE(double), true);
    TEST(PVC_IS_DOUBLE(const double), true);
    TEST(PVC_IS_DOUBLE(volatile double), true);
    TEST(PVC_IS_DOUBLE(double*), false);

    TEST(PVC_IS_SIGNED(double), true);
    TEST(PVC_IS_SIGNED(const double), true);
    TEST(PVC_IS_SIGNED(volatile double), true);
    TEST(PVC_IS_SIGNED(double*), false);

    TEST(PVC_IS_UNSIGNED(double), false);
    TEST(PVC_IS_UNSIGNED(const double), false);
    TEST(PVC_IS_UNSIGNED(volatile double), false);
    TEST(PVC_IS_UNSIGNED(double*), false);

    TEST(PVC_IS_FLOATINGPOINT(double), true);
    TEST(PVC_IS_FLOATINGPOINT(const double), true);
    TEST(PVC_IS_FLOATINGPOINT(volatile double), true);
    TEST(PVC_IS_FLOATINGPOINT(double*), false);

    TEST(PVC_IS_INTEGER(double), false);
    TEST(PVC_IS_INTEGER(const double), false);
    TEST(PVC_IS_INTEGER(volatile double), false);
    TEST(PVC_IS_INTEGER(double*), false);

#ifdef __cplusplus
    TEST(isinf(PVC_TYPE_MAX(double)), true);
    TEST(isinf(PVC_TYPE_MIN(double)), true);
    TEST(isinf(PVC_TYPE_MAX(const double)), true);
    TEST(isinf(PVC_TYPE_MIN(volatile double)), true);
    TEST(PVC_TYPE_MAX(double) > 0, true);
    TEST(PVC_TYPE_MIN(double) < 0, true);
    TEST(PVC_TYPE_MAX(const double) > 0, true);
    TEST(PVC_TYPE_MIN(volatile double) < 0, true);
#else /* not C++ */
    TEST(isinf(PVC_TYPE_MAX(double)), +1);
    TEST(isinf(PVC_TYPE_MIN(double)), -1);
    TEST(isinf(PVC_TYPE_MAX(const double)), +1);
    TEST(isinf(PVC_TYPE_MIN(volatile double)), -1);
#endif /* C or C++ */
    TEST(isinf(PVC_DBL_INF), true);
    TEST(isnan(PVC_DBL_NAN), true);

    TEST(PVC_IS_FLOATINGPOINT(const double), true);
    TEST(PVC_IS_FLOATINGPOINT(volatile double), true);
    TEST(PVC_IS_FLOATINGPOINT(double*), false);

    if (verbose) {
        printf("\n");
    }
    printf("Number of tests:    %4ld\n", ntests);
    printf("Number of failures: %4ld\n", nfailures);
    return (nfailures == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
