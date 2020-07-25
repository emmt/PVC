/*
 * timing.c -
 *
 * Measuring time.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#include <stdio.h>
#include <math.h>
#include <float.h>
#include "pvc.h"

void pvc_time_stat_init(PVC_TimeStatData* tsd)
{
    tsd->min = DBL_MAX;
    tsd->max = 0;
    tsd->sum1 = 0;
    tsd->sum2 = 0;
    tsd->numb = 0;
}

void pvc_time_stat_update(PVC_TimeStatData* tsd, double t)
{
    if (tsd->numb < 1) {
        tsd->min = t;
        tsd->max = t;
        tsd->sum1 = t;
        tsd->sum2 = t*t;
        tsd->numb = 1;
    } else {
        tsd->min = (t < tsd->min ? t : tsd->min);
        tsd->max = (t > tsd->max ? t : tsd->max);
        tsd->sum1 += t;
        tsd->sum2 += t*t;
        tsd->numb += 1;
    }
}

PVC_TimeStat* pvc_time_stat_compute(PVC_TimeStat* ts,
                                    PVC_TimeStatData const* tsd)
{
    ts->min = tsd->min;
    ts->max = tsd->max;
    if (tsd->numb >= 1) {
        ts->avg = tsd->sum1/tsd->numb;
        if (tsd->numb >= 2) {
            ts->std = sqrt((tsd->sum2 - ts->avg*tsd->sum1)/(tsd->numb - 1));
        } else {
            ts->std = 0;
        }
    } else {
        ts->avg = 0;
        ts->std = 0;
    }
    ts->numb = tsd->numb;
    return ts;
}

void pvc_time_stat_print(FILE* output,
                         char const* pfx,
                         PVC_TimeStat const* ts)
{
    if (output == NULL) {
        output = stdout;
    }
    double const scl = 1E6; // print timings in microseconds
    printf("%snumber of evaluations: %ld\n", pfx, ts->numb);
    printf("%smin. time: %7.3f µs\n", pfx, ts->min*scl);
    printf("%smax. time: %7.3f µs\n", pfx, ts->max*scl);
    printf("%savg. time: %7.3f ± %.3f µs\n", pfx, ts->avg*scl, ts->std*scl);
}

double pvc_elapsed_seconds(struct timespec const* t,
                           struct timespec const* t0)
{
    // tv_sec may be unsigned.
    double secs;
    if (t->tv_sec >= t0->tv_sec) {
        secs = t->tv_sec - t0->tv_sec;
    } else {
        secs = -(double)(t0->tv_sec - t->tv_sec);
    }
    if (t->tv_nsec >= t0->tv_nsec) {
        secs += 1e-9*(t->tv_nsec - t0->tv_nsec);
    } else {
        secs -= 1e-9*(t0->tv_nsec - t->tv_nsec);
    }
    return secs;
}
