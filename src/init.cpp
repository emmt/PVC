/*
 * init.c -
 *
 * Initialize PVC library.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "pvc.h"

#define VCL_NAMESPACE vcl
#include "instrset_detect.cpp"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void fatal_error(char const* func, int code)
{
    fprintf(stderr, "%s() failed with code %d [%s]\n", func, code,
            strerror(code));
    exit(EXIT_FAILURE);
}

int pvc_instrset(void)
{
    int code = pthread_mutex_lock(&mtx);
    if (code != 0) {
        fatal_error("pthread_mutex_lock", code);
    }
    static volatile int instrset = -1;
    if (instrset == -1) {
        instrset = vcl::instrset_detect();
    }
    int result = instrset;
    code = pthread_mutex_unlock(&mtx);
    if (code != 0) {
        fatal_error("pthread_mutex_unlock", code);
    }
    return result;
}
