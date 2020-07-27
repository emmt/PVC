/*
 * pvc-max.h -
 *
 * Inline version of the max function.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PVC_MAX_H
#define _PVC_MAX_H 1

#include <pvc-types.h>

/* Protect against someone else defining private symbols. */
#if defined(_pvc_arg1) || defined(_pvc_arg2)
#  error "Macros _pvc_argN (with N integer) must not be defined."
#endif

#endif /* _PVC_MAX_H */
