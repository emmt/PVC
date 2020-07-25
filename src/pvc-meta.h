/*
 * pvc-meta.h -
 *
 * Definitions for meta-programming in C.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of PVC software released under the MIT "Expat" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */

#ifndef _PVC_META_H
#define _PVC_META_H 1

/**
 * @def PVC_MAX_NARGS
 *
 * The number of arguments for some macros dealing with variadic arguments.
 */
#define PVC_MAX_NARGS 20

/**
 * @def PVC_NARGS(...)
 *
 * Yield the number of variadic arguments in `...`.  A maximum of 20
 * arguments is supported.
 */
#define PVC_NARGS(...) \
    PVC_GET_21(__VA_ARGS__,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

/**
 * @def PVC_CALL_NUMBERED(F,...)
 *
 * Call with variadic arguments `...` the function or macro whose name is
 * given by the concatenation of the prefix @a F with the number of
 * variadic arguments in `...`.
 */
#define PVC_CALL_NUMBERED(F,...) PVC_CALL_PASTED(F,PVC_NARGS(__VA_ARGS__),__VA_ARGS__)

/**
 * @def PVC_CALL_PASTED(P,S,...)
 *
 * Call with variadic arguments `...` the function or macro whose name is
 * given by the concatenation of prefix @a P and suffix @a S.
 */
#define PVC_CALL_PASTED(P,S,...) _PVC_PASTE(P,S)(__VA_ARGS__)

/**
 * @def PVC_GET(N, ...)
 *
 * Yield the @a N-th argument from the list of arguments `...`.  A limit of
 * @a N ≤ 21 is imposed.
 */
#define PVC_GET(N,...) PVC_CALL_PASTED(PVC_GET_,N,__VA_ARGS__)
#define PVC_GET_0( ...)
#define PVC_GET_1( _1,...)                                                                          _1
#define PVC_GET_2( _1,_2,...)                                                                       _2
#define PVC_GET_3( _1,_2,_3,...)                                                                    _3
#define PVC_GET_4( _1,_2,_3,_4,...)                                                                 _4
#define PVC_GET_5( _1,_2,_3,_4,_5,...)                                                              _5
#define PVC_GET_6( _1,_2,_3,_4,_5,_6,...)                                                           _6
#define PVC_GET_7( _1,_2,_3,_4,_5,_6,_7,...)                                                        _7
#define PVC_GET_8( _1,_2,_3,_4,_5,_6,_7,_8,...)                                                     _8
#define PVC_GET_9( _1,_2,_3,_4,_5,_6,_7,_8,_9,...)                                                  _9
#define PVC_GET_10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,...)                                             _10
#define PVC_GET_11(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,...)                                         _11
#define PVC_GET_12(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,...)                                     _12
#define PVC_GET_13(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,...)                                 _13
#define PVC_GET_14(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,...)                             _14
#define PVC_GET_15(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,...)                         _15
#define PVC_GET_16(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,...)                     _16
#define PVC_GET_17(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,...)                 _17
#define PVC_GET_18(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,...)             _18
#define PVC_GET_19(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,...)         _19
#define PVC_GET_20(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,...)     _20
#define PVC_GET_21(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,...) _21

/**
 * @def PVC_REPLACE(N, X, ...)
 *
 * Yield a list where the @a N-th variadic argument in `...` has been
 * replaced by @a X.  A limit of @a N ≤ 20 is imposed.
 */
#define PVC_REPLACE(N,X,...) PVC_CALL_PASTED(PVC_REPLACE_,PVC_NARGS(__VA_ARGS__),X,__VA_ARGS__)
#define PVC_REPLACE_0( X,...)                                                                        __VA_ARGS__
#define PVC_REPLACE_1( X,_1,...)                                                                     X,__VA_ARGS__
#define PVC_REPLACE_2( X,_1,_2,...)                                                                  _1,X,__VA_ARGS__
#define PVC_REPLACE_3( X,_1,_2,_3,...)                                                               _1,_2,X,__VA_ARGS__
#define PVC_REPLACE_4( X,_1,_2,_3,_4,...)                                                            _1,_2,_3,X,__VA_ARGS__
#define PVC_REPLACE_5( X,_1,_2,_3,_4,_5,...)                                                         _1,_2,_3,_4,X,__VA_ARGS__
#define PVC_REPLACE_6( X,_1,_2,_3,_4,_5,_6,...)                                                      _1,_2,_3,_4,_5,X,__VA_ARGS__
#define PVC_REPLACE_7( X,_1,_2,_3,_4,_5,_6,_7,...)                                                   _1,_2,_3,_4,_5,_6,X,__VA_ARGS__
#define PVC_REPLACE_8( X,_1,_2,_3,_4,_5,_6,_7,_8,...)                                                _1,_2,_3,_4,_5,_6,_7,X,__VA_ARGS__
#define PVC_REPLACE_9( X,_1,_2,_3,_4,_5,_6,_7,_8,_9,...)                                             _1,_2,_3,_4,_5,_6,_7,_8,X,__VA_ARGS__
#define PVC_REPLACE_10(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,...)                                         _1,_2,_3,_4,_5,_6,_7,_8,_9,X,__VA_ARGS__
#define PVC_REPLACE_11(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,...)                                     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,X,__VA_ARGS__
#define PVC_REPLACE_12(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,...)                                 _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,X,__VA_ARGS__
#define PVC_REPLACE_13(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,...)                             _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,X,__VA_ARGS__
#define PVC_REPLACE_14(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,...)                         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,X,__VA_ARGS__
#define PVC_REPLACE_15(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,...)                     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,X,__VA_ARGS__
#define PVC_REPLACE_16(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,...)                 _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,X,__VA_ARGS__
#define PVC_REPLACE_17(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,...)             _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,X,__VA_ARGS__
#define PVC_REPLACE_18(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,...)         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,X,__VA_ARGS__
#define PVC_REPLACE_19(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,...)     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,X,__VA_ARGS__
#define PVC_REPLACE_20(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,...) _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,X,__VA_ARGS__

/**
 * @def PVC_DELETE(N, ...)
 *
 * Yield a list where the @a N-th variadic argument in `...` has been
 * suppressed.  A limit of @a N ≤ 20 is imposed.
 */
#define PVC_DELETE(N,...) PVC_CALL_PASTED(PVC_DELETE_,N,__VA_ARGS__)
#define PVC_DELETE_0( ...)                                                                        __VA_ARGS__
#define PVC_DELETE_1( _1,...)                                                                     __VA_ARGS__
#define PVC_DELETE_2( _1,_2,...)                                                                  _1,__VA_ARGS__
#define PVC_DELETE_3( _1,_2,_3,...)                                                               _1,_2,__VA_ARGS__
#define PVC_DELETE_4( _1,_2,_3,_4,...)                                                            _1,_2,_3,__VA_ARGS__
#define PVC_DELETE_5( _1,_2,_3,_4,_5,...)                                                         _1,_2,_3,_4,__VA_ARGS__
#define PVC_DELETE_6( _1,_2,_3,_4,_5,_6,...)                                                      _1,_2,_3,_4,_5,__VA_ARGS__
#define PVC_DELETE_7( _1,_2,_3,_4,_5,_6,_7,...)                                                   _1,_2,_3,_4,_5,_6,__VA_ARGS__
#define PVC_DELETE_8( _1,_2,_3,_4,_5,_6,_7,_8,...)                                                _1,_2,_3,_4,_5,_6,_7,__VA_ARGS__
#define PVC_DELETE_9( _1,_2,_3,_4,_5,_6,_7,_8,_9,...)                                             _1,_2,_3,_4,_5,_6,_7,_8,__VA_ARGS__
#define PVC_DELETE_10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,...)                                         _1,_2,_3,_4,_5,_6,_7,_8,_9,__VA_ARGS__
#define PVC_DELETE_11(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,...)                                     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,__VA_ARGS__
#define PVC_DELETE_12(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,...)                                 _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,__VA_ARGS__
#define PVC_DELETE_13(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,...)                             _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,__VA_ARGS__
#define PVC_DELETE_14(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,...)                         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,__VA_ARGS__
#define PVC_DELETE_15(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,...)                     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,__VA_ARGS__
#define PVC_DELETE_16(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,...)                 _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,__VA_ARGS__
#define PVC_DELETE_17(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,...)             _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,__VA_ARGS__
#define PVC_DELETE_18(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,...)         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,__VA_ARGS__
#define PVC_DELETE_19(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,...)     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,__VA_ARGS__
#define PVC_DELETE_20(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,...) _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,__VA_ARGS__

/* For macros like PVC_MAP_#, PVC_REDUCE_#, etc., using variadic arguments,
   it is easier to encode the macros and it let the caller specify more
   arguments than required. */

/**
 * @def PVC_MAP(F, ...)
 *
 * Yield a list built by applying the function @a F to all arguments in
 * `...`.  That is, yield an expression like:
 *
 * ```.c
 * F(ARG_1),F(ARG_2),...
 * ```
 *
 * A maximum of 20 arguments is supported.
 */
#define PVC_MAP(F,...) PVC_MAP_N(PVC_NARGS(__VA_ARGS__),F,__VA_ARGS__)

/**
 * @def PVC_MAP_N(N, F, ...)
 *
 * Yield a list built by applying the function @a F to the first @a N arguments in
 * `...` ignoring the extraneous ones.  That is, yield an expression like:
 *
 * ```.c
 * F(ARG_1),F(ARG_2),...,F(ARG_N)
 * ```
 *
 * A limit of @a N ≤ 20 is imposed.
 */
#define PVC_MAP_N(N,F,...) PVC_CALL_PASTED(PVC_MAP_,N,F,__VA_ARGS__)
#define PVC_MAP_0( F,  ...)
#define PVC_MAP_1( F,X,...) F(X)
#define PVC_MAP_2( F,X,...) F(X),PVC_MAP_1( F, __VA_ARGS__)
#define PVC_MAP_3( F,X,...) F(X),PVC_MAP_2( F, __VA_ARGS__)
#define PVC_MAP_4( F,X,...) F(X),PVC_MAP_3( F, __VA_ARGS__)
#define PVC_MAP_5( F,X,...) F(X),PVC_MAP_4( F, __VA_ARGS__)
#define PVC_MAP_6( F,X,...) F(X),PVC_MAP_5( F, __VA_ARGS__)
#define PVC_MAP_7( F,X,...) F(X),PVC_MAP_6( F, __VA_ARGS__)
#define PVC_MAP_8( F,X,...) F(X),PVC_MAP_7( F, __VA_ARGS__)
#define PVC_MAP_9( F,X,...) F(X),PVC_MAP_8( F, __VA_ARGS__)
#define PVC_MAP_10(F,X,...) F(X),PVC_MAP_9( F, __VA_ARGS__)
#define PVC_MAP_11(F,X,...) F(X),PVC_MAP_10(F, __VA_ARGS__)
#define PVC_MAP_12(F,X,...) F(X),PVC_MAP_11(F, __VA_ARGS__)
#define PVC_MAP_13(F,X,...) F(X),PVC_MAP_12(F, __VA_ARGS__)
#define PVC_MAP_14(F,X,...) F(X),PVC_MAP_13(F, __VA_ARGS__)
#define PVC_MAP_15(F,X,...) F(X),PVC_MAP_14(F, __VA_ARGS__)
#define PVC_MAP_16(F,X,...) F(X),PVC_MAP_15(F, __VA_ARGS__)
#define PVC_MAP_17(F,X,...) F(X),PVC_MAP_16(F, __VA_ARGS__)
#define PVC_MAP_18(F,X,...) F(X),PVC_MAP_17(F, __VA_ARGS__)
#define PVC_MAP_19(F,X,...) F(X),PVC_MAP_18(F, __VA_ARGS__)
#define PVC_MAP_20(F,X,...) F(X),PVC_MAP_19(F, __VA_ARGS__)

#define PVC_EVAL(a)           a
#define PVC_NOTHING(...)
#define PVC_IDENTITY(...)     __VA_ARGS__
#define PVC_PROTECT(...)     (__VA_ARGS__)

#define PVC_IF_EQ(A, B) _PVC_IF_CLAUSE(PVC_PASTE4(_PVC_IS_,A,_EQ_,B)())
#define PVC_IF_NE(A, B) _PVC_IF_NOT_CLAUSE(PVC_PASTE4(_PVC_IS_,A,_EQ_,B)())
#define PVC_IF_EQ_0(N)   PVC_IF_EQ(0,N)
#define PVC_IF_ELSE(...) PVC_IF_EQ_0(PVC_IS_EQ_0(__VA_ARGS__))

#define _PVC_CLAUSE1(...) __VA_ARGS__ PVC_NOTHING
#define _PVC_CLAUSE2(...) PVC_IDENTITY

#define _PVC_IF_CLAUSE(EXP)     PVC_GET_3(EXP, _PVC_CLAUSE1, _PVC_CLAUSE2, ~)
#define _PVC_IF_NOT_CLAUSE(EXP) PVC_GET_3(EXP, _PVC_CLAUSE2, _PVC_CLAUSE1, ~)

#define _PVC_IS_0_EQ_0(...) ,
#define _PVC_IS_1_EQ_1(...) ,
#define _PVC_IS_2_EQ_2(...) ,
#define _PVC_IS_3_EQ_3(...) ,
#define _PVC_IS_4_EQ_4(...) ,
#define _PVC_IS_5_EQ_5(...) ,
#define _PVC_IS_6_EQ_6(...) ,
#define _PVC_IS_7_EQ_7(...) ,
#define _PVC_IS_8_EQ_8(...) ,
#define _PVC_IS_9_EQ_9(...) ,
#define _PVC_IS_10_EQ_10(...) ,
#define _PVC_IS_11_EQ_11(...) ,
#define _PVC_IS_12_EQ_12(...) ,
#define _PVC_IS_13_EQ_13(...) ,
#define _PVC_IS_14_EQ_14(...) ,
#define _PVC_IS_15_EQ_15(...) ,
#define _PVC_IS_16_EQ_16(...) ,
#define _PVC_IS_17_EQ_17(...) ,
#define _PVC_IS_18_EQ_18(...) ,
#define _PVC_IS_19_EQ_19(...) ,
#define _PVC_IS_20_EQ_20(...) ,
#define _PVC_IS_21_EQ_21(...) ,
#define _PVC_IS_22_EQ_22(...) ,
#define _PVC_IS_23_EQ_23(...) ,
#define _PVC_IS_24_EQ_24(...) ,
#define _PVC_IS_25_EQ_25(...) ,
#define _PVC_IS_26_EQ_26(...) ,
#define _PVC_IS_27_EQ_27(...) ,
#define _PVC_IS_28_EQ_28(...) ,
#define _PVC_IS_29_EQ_29(...) ,

#define PVC_SUM(...)         PVC_REDUCE(+,PVC_PROTECT,__VA_ARGS__)
#define PVC_SUM_N(N,...)     PVC_REDUCE_N(N,+,PVC_PROTECT,__VA_ARGS__)
#define PVC_PRODUCT(...)     PVC_REDUCE(*,PVC_PROTECT,__VA_ARGS__)
#define PVC_PRODUCT_N(N,...) PVC_REDUCE_N(N,*,PVC_PROTECT,__VA_ARGS__)

/**
 * @def PVC_REDUCE(OP, F, ...)
 *
 * Reduce all variadic arguments in `...` via function (or macro) @a F and
 * operator @a OP.  That is, yield an expression like:
 *
 * ```.c
 * F(ARG_1) OP F(ARG_2) OP ...
 * ```
 */
#define PVC_REDUCE(OP,F,...) \
    PVC_REDUCE_N(PVC_NARGS(__VA_ARGS__),OP,F,__VA_ARGS__)

/**
 * @def PVC_REDUCE_N(N, OP, F, ...)
 *
 * Reduce the @a N first variadic arguments in `...` ignoring the
 * extraneous ones via function (or macro) @a F and operator @a OP.  That
 * is, yield an expression like:
 *
 * ```.c
 * F(ARG_1) OP F(ARG_2) ... OP F(ARG_N)
 * ```
 */
#define PVC_REDUCE_N(N,OP,F,...)  PVC_CALL_PASTED(PVC_REDUCE_,N,OP,F,__VA_ARGS__)
#define PVC_REDUCE_0( OP,F,  ...)
#define PVC_REDUCE_1( OP,F,X,...) F(X)
#define PVC_REDUCE_2( OP,F,X,...) F(X) OP PVC_REDUCE_1( OP, F, __VA_ARGS__)
#define PVC_REDUCE_3( OP,F,X,...) F(X) OP PVC_REDUCE_2( OP, F, __VA_ARGS__)
#define PVC_REDUCE_4( OP,F,X,...) F(X) OP PVC_REDUCE_3( OP, F, __VA_ARGS__)
#define PVC_REDUCE_5( OP,F,X,...) F(X) OP PVC_REDUCE_4( OP, F, __VA_ARGS__)
#define PVC_REDUCE_6( OP,F,X,...) F(X) OP PVC_REDUCE_5( OP, F, __VA_ARGS__)
#define PVC_REDUCE_7( OP,F,X,...) F(X) OP PVC_REDUCE_6( OP, F, __VA_ARGS__)
#define PVC_REDUCE_8( OP,F,X,...) F(X) OP PVC_REDUCE_7( OP, F, __VA_ARGS__)
#define PVC_REDUCE_9( OP,F,X,...) F(X) OP PVC_REDUCE_8( OP, F, __VA_ARGS__)
#define PVC_REDUCE_10(OP,F,X,...) F(X) OP PVC_REDUCE_9( OP, F, __VA_ARGS__)
#define PVC_REDUCE_11(OP,F,X,...) F(X) OP PVC_REDUCE_10(OP, F, __VA_ARGS__)
#define PVC_REDUCE_12(OP,F,X,...) F(X) OP PVC_REDUCE_11(OP, F, __VA_ARGS__)
#define PVC_REDUCE_13(OP,F,X,...) F(X) OP PVC_REDUCE_12(OP, F, __VA_ARGS__)
#define PVC_REDUCE_14(OP,F,X,...) F(X) OP PVC_REDUCE_13(OP, F, __VA_ARGS__)
#define PVC_REDUCE_15(OP,F,X,...) F(X) OP PVC_REDUCE_14(OP, F, __VA_ARGS__)
#define PVC_REDUCE_16(OP,F,X,...) F(X) OP PVC_REDUCE_15(OP, F, __VA_ARGS__)
#define PVC_REDUCE_17(OP,F,X,...) F(X) OP PVC_REDUCE_16(OP, F, __VA_ARGS__)
#define PVC_REDUCE_18(OP,F,X,...) F(X) OP PVC_REDUCE_17(OP, F, __VA_ARGS__)
#define PVC_REDUCE_19(OP,F,X,...) F(X) OP PVC_REDUCE_18(OP, F, __VA_ARGS__)
#define PVC_REDUCE_20(OP,F,X,...) F(X) OP PVC_REDUCE_19(OP, F, __VA_ARGS__)

/**
 * @def PVC_COMPOSE_REDUCE(OP, F1, F2, ...)
 *
 * Reduce all arguments in `...` via the composition of functions (or
 * macros) @a F1 and @a F2 and operator @a OP.  That is, yield an
 * expression like:
 *
 * ```.c
 * F1(F2(ARG_1)) OP F1(F2(ARG_2)) OP ...
 * ```
 */
#define PVC_COMPOSE_REDUCE(OP,F1,F2,...) \
    PVC_COMPOSE_REDUCE_N(PVC_NARGS(__VA_ARGS__),OP,F1,F2,__VA_ARGS__)

/**
 * @def PVC_COMPOSE_REDUCE_N(N, OP, F1, F2, ...)
 *
 * Reduce the @a N first arguments in `...` ignoring the extraneous ones
 * via the composition of functions (or macros) @a F1 and @a F2 and
 * operator @a OP.  That is, yield an expression like:
 *
 * ```.c
 * F1(F2(ARG_1)) OP F1(F2(ARG_2)) ... OP F1(F2(ARG_N))
 * ```
 */
#define PVC_COMPOSE_REDUCE_N(N,OP,F1,F2,...) PVC_CALL_PASTED(PVC_COMPOSE_REDUCE_,N,OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_0( OP,F1,F2,  ...)
#define PVC_COMPOSE_REDUCE_1( OP,F1,F2,X,...) F1(F2(X))
#define PVC_COMPOSE_REDUCE_2( OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_1( OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_3( OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_2( OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_4( OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_3( OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_5( OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_4( OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_6( OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_5( OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_7( OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_6( OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_8( OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_7( OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_9( OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_8( OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_10(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_9( OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_11(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_10(OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_12(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_11(OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_13(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_12(OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_14(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_13(OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_15(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_14(OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_16(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_15(OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_17(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_16(OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_18(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_17(OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_19(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_18(OP,F1,F2,__VA_ARGS__)
#define PVC_COMPOSE_REDUCE_20(OP,F1,F2,X,...) F1(F2(X)) OP PVC_COMPOSE_REDUCE_19(OP,F1,F2,__VA_ARGS__)

/* The following macro is needed to: (i) force macro expansion before
   concatenating arguments, (ii) to provide a (cheap) equivalent to
   PVC_PASTE_2 which can be used by PVC_PASTE_2.  The latter is because
   macro itself is desactivated when expanding a function-like macro (e.g.,
   to avoid infinite loops), so another macro than PVC_PASTE_2 must be used
   in the expression resulting from PVC_PASTE_2. */
#define _PVC_PASTE(_1,_2) _PVC_PASTE_2(_1,_2)

/**
 * @def PVC_PASTE(...)
 *
 * Expand and concatenate all arguments in `...` and without separators.  A
 * maximum of 20 arguments is supported.
 *
 * Note that pasting arguments must yield a valid token for the
 * preprocessor.
 */
#define PVC_PASTE(...) PVC_CALL_NUMBERED(PVC_PASTE_,__VA_ARGS__)

/**
 * @def PVC_PASTE_N(N, ...)
 *
 * Expand and concatenate the @a N first arguments of `...` ignoring the
 * extraneous ones and without separators.  A limit @a N ≤ 20 is imposed.
 *
 * Note that pasting arguments must yield a valid token for the
 * preprocessor.
 */
#define PVC_PASTE_N(N,...) PVC_CALL_PASTED(PVC_PASTE_,N,__VA_ARGS__)
#define PVC_PASTE_0( ...) _PVC_PASTE_0( __VA_ARGS__)
#define PVC_PASTE_1( ...) _PVC_PASTE_1( __VA_ARGS__)
#define PVC_PASTE_2( ...) _PVC_PASTE_2( __VA_ARGS__)
#define PVC_PASTE_3( ...) _PVC_PASTE_3( __VA_ARGS__)
#define PVC_PASTE_4( ...) _PVC_PASTE_4( __VA_ARGS__)
#define PVC_PASTE_5( ...) _PVC_PASTE_5( __VA_ARGS__)
#define PVC_PASTE_6( ...) _PVC_PASTE_6( __VA_ARGS__)
#define PVC_PASTE_7( ...) _PVC_PASTE_7( __VA_ARGS__)
#define PVC_PASTE_8( ...) _PVC_PASTE_8( __VA_ARGS__)
#define PVC_PASTE_9( ...) _PVC_PASTE_9( __VA_ARGS__)
#define PVC_PASTE_10(...) _PVC_PASTE_10(__VA_ARGS__)
#define PVC_PASTE_11(...) _PVC_PASTE_11(__VA_ARGS__)
#define PVC_PASTE_12(...) _PVC_PASTE_12(__VA_ARGS__)
#define PVC_PASTE_13(...) _PVC_PASTE_13(__VA_ARGS__)
#define PVC_PASTE_14(...) _PVC_PASTE_14(__VA_ARGS__)
#define PVC_PASTE_15(...) _PVC_PASTE_15(__VA_ARGS__)
#define PVC_PASTE_16(...) _PVC_PASTE_16(__VA_ARGS__)
#define PVC_PASTE_17(...) _PVC_PASTE_17(__VA_ARGS__)
#define PVC_PASTE_18(...) _PVC_PASTE_18(__VA_ARGS__)
#define PVC_PASTE_19(...) _PVC_PASTE_19(__VA_ARGS__)
#define PVC_PASTE_20(...) _PVC_PASTE_20(__VA_ARGS__)

/* Recursive definitions for _PVC_PASTE_# is not possible to avoid that
   intermediate tokens be expanded. */

#define _PVC_PASTE_0(...)
#define _PVC_PASTE_1( _1,...)                                                                     _1
#define _PVC_PASTE_2( _1,_2,...)                                                                  _1 ## _2
#define _PVC_PASTE_3( _1,_2,_3,...)                                                               _1 ## _2 ## _3
#define _PVC_PASTE_4( _1,_2,_3,_4,...)                                                            _1 ## _2 ## _3 ## _4
#define _PVC_PASTE_5( _1,_2,_3,_4,_5,...)                                                         _1 ## _2 ## _3 ## _4 ## _5
#define _PVC_PASTE_6( _1,_2,_3,_4,_5,_6,...)                                                      _1 ## _2 ## _3 ## _4 ## _5 ## _6
#define _PVC_PASTE_7( _1,_2,_3,_4,_5,_6,_7,...)                                                   _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7
#define _PVC_PASTE_8( _1,_2,_3,_4,_5,_6,_7,_8,...)                                                _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8
#define _PVC_PASTE_9( _1,_2,_3,_4,_5,_6,_7,_8,_9,...)                                             _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9
#define _PVC_PASTE_10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,...)                                         _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10
#define _PVC_PASTE_11(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,...)                                     _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11
#define _PVC_PASTE_12(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,...)                                 _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12
#define _PVC_PASTE_13(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,...)                             _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13
#define _PVC_PASTE_14(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,...)                         _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13 ## _14
#define _PVC_PASTE_15(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,...)                     _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13 ## _14 ## _15
#define _PVC_PASTE_16(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,...)                 _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13 ## _14 ## _15 ## _16
#define _PVC_PASTE_17(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,...)             _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13 ## _14 ## _15 ## _16 ## _17
#define _PVC_PASTE_18(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,...)         _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13 ## _14 ## _15 ## _16 ## _17 ## _18
#define _PVC_PASTE_19(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,...)     _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13 ## _14 ## _15 ## _16 ## _17 ## _18 ## _19
#define _PVC_PASTE_20(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,...) _1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13 ## _14 ## _15 ## _16 ## _17 ## _18 ## _19 ## _20

/**
 * @def PVC_JOIN(S, ...)
 *
 * Expand and join with separator @a S all arguments in `...`.  A maximum
 * of 20 arguments is supported.
 */
#define PVC_JOIN(S,...) PVC_JOIN_N(PVC_NARGS(__VA_ARGS__), S, __VA_ARGS__)

/**
 * @def PVC_JOIN_N(N,S, ...)
 *
 * Expand and join with separator @a S the first @a N arguments in `...`
 * ignoring the extraneous ones.  A limit @a N ≤ 20 is imposed.
 *
 * Separator S is inserted surrounded by spaces so it must be empty or a
 * valid token in itself.
 */
#define PVC_JOIN_N(N,S,...) _PVC_PASTE_2(PVC_JOIN_,N)(S,__VA_ARGS__)
#define PVC_JOIN_0( S,  ...)
#define PVC_JOIN_1( S,X,...) X
#define PVC_JOIN_2( S,X,...) X S PVC_JOIN_1( S,__VA_ARGS__)
#define PVC_JOIN_3( S,X,...) X S PVC_JOIN_2( S,__VA_ARGS__)
#define PVC_JOIN_4( S,X,...) X S PVC_JOIN_3( S,__VA_ARGS__)
#define PVC_JOIN_5( S,X,...) X S PVC_JOIN_4( S,__VA_ARGS__)
#define PVC_JOIN_6( S,X,...) X S PVC_JOIN_5( S,__VA_ARGS__)
#define PVC_JOIN_7( S,X,...) X S PVC_JOIN_6( S,__VA_ARGS__)
#define PVC_JOIN_8( S,X,...) X S PVC_JOIN_7( S,__VA_ARGS__)
#define PVC_JOIN_9( S,X,...) X S PVC_JOIN_8( S,__VA_ARGS__)
#define PVC_JOIN_10(S,X,...) X S PVC_JOIN_9( S,__VA_ARGS__)
#define PVC_JOIN_11(S,X,...) X S PVC_JOIN_10(S,__VA_ARGS__)
#define PVC_JOIN_12(S,X,...) X S PVC_JOIN_11(S,__VA_ARGS__)
#define PVC_JOIN_13(S,X,...) X S PVC_JOIN_12(S,__VA_ARGS__)
#define PVC_JOIN_14(S,X,...) X S PVC_JOIN_13(S,__VA_ARGS__)
#define PVC_JOIN_15(S,X,...) X S PVC_JOIN_14(S,__VA_ARGS__)
#define PVC_JOIN_16(S,X,...) X S PVC_JOIN_15(S,__VA_ARGS__)
#define PVC_JOIN_17(S,X,...) X S PVC_JOIN_16(S,__VA_ARGS__)
#define PVC_JOIN_18(S,X,...) X S PVC_JOIN_17(S,__VA_ARGS__)
#define PVC_JOIN_19(S,X,...) X S PVC_JOIN_18(S,__VA_ARGS__)
#define PVC_JOIN_20(S,X,...) X S PVC_JOIN_19(S,__VA_ARGS__)

/**
 * @def PVC_FIRST(...)
 *
 * Yield the first argument in `...`.  There is no limits on the number of
 * arguments unless the preprocessor imposes one.
 */
#define PVC_FIRST(X, ...) X

/**
 * @def PVC_LAST(...)
 *
 * Yield the last argument in `...`.  A maximum of 20 arguments is supported.
 */
#define PVC_LAST(...) PVC_CALL_NUMBERED(PVC_GET_,__VA_ARGS__)

/**
 * @def PVC_TAIL(...)
 *
 * Yield all but the the first argument of `...`.  There is no limits on
 * the number of arguments unless the preprocessor imposes one.
 */
#define PVC_TAIL(X, ...) __VA_ARGS__

/**
 * @def PVC_HEAD(...)
 *
 * Yield all but the the last argument of `...`.  A maximum of 20 arguments
 * is supported.
 */
#define PVC_HEAD(...)  PVC_CALL_NUMBERED(_PVC_HEAD_,__VA_ARGS__)

/* Directly calling the following macros does not make sense, so they are
   considered as private. */
#define _PVC_HEAD_0()
#define _PVC_HEAD_1( _1)
#define _PVC_HEAD_2( _1,_2)                                                                  _1
#define _PVC_HEAD_3( _1,_2,_3)                                                               _1,_2
#define _PVC_HEAD_4( _1,_2,_3,_4)                                                            _1,_2,_3
#define _PVC_HEAD_5( _1,_2,_3,_4,_5)                                                         _1,_2,_3,_4
#define _PVC_HEAD_6( _1,_2,_3,_4,_5,_6)                                                      _1,_2,_3,_4,_5
#define _PVC_HEAD_7( _1,_2,_3,_4,_5,_6,_7)                                                   _1,_2,_3,_4,_5,_6
#define _PVC_HEAD_8( _1,_2,_3,_4,_5,_6,_7,_8)                                                _1,_2,_3,_4,_5,_6,_7
#define _PVC_HEAD_9( _1,_2,_3,_4,_5,_6,_7,_8,_9)                                             _1,_2,_3,_4,_5,_6,_7,_8
#define _PVC_HEAD_10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10)                                         _1,_2,_3,_4,_5,_6,_7,_8,_9
#define _PVC_HEAD_11(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11)                                     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10
#define _PVC_HEAD_12(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12)                                 _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11
#define _PVC_HEAD_13(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13)                             _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12
#define _PVC_HEAD_14(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14)                         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13
#define _PVC_HEAD_15(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15)                     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14
#define _PVC_HEAD_16(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16)                 _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15
#define _PVC_HEAD_17(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17)             _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16
#define _PVC_HEAD_18(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18)         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17
#define _PVC_HEAD_19(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19)     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18
#define _PVC_HEAD_20(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20) _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19


/**
 * @def PVC_REVERSE(...)
 *
 * Yield variadic arguments `...` in reverse order.  A maximum of 20
 * arguments is supported.
 */
#define PVC_REVERSE(...) PVC_CALL_NUMBERED(_PVC_REVERSE_,__VA_ARGS__)

#define _PVC_REVERSE_0()
#define _PVC_REVERSE_1( _1)                                                                                                                                         _1
#define _PVC_REVERSE_2( _1,_2)                                                                                                                                   _2,_1
#define _PVC_REVERSE_3( _1,_2,_3)                                                                                                                             _3,_2,_1
#define _PVC_REVERSE_4( _1,_2,_3,_4)                                                                                                                       _4,_3,_2,_1
#define _PVC_REVERSE_5( _1,_2,_3,_4,_5)                                                                                                                 _5,_4,_3,_2,_1
#define _PVC_REVERSE_6( _1,_2,_3,_4,_5,_6)                                                                                                           _6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_7( _1,_2,_3,_4,_5,_6,_7)                                                                                                     _7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_8( _1,_2,_3,_4,_5,_6,_7,_8)                                                                                               _8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_9( _1,_2,_3,_4,_5,_6,_7,_8,_9)                                                                                         _9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10)                                                                                 _10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_11(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11)                                                                         _11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_12(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12)                                                                 _12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_13(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13)                                                         _13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_14(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14)                                                 _14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_15(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15)                                         _15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_16(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16)                                 _16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_17(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17)                         _17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_18(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18)                 _18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_19(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19)         _19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1
#define _PVC_REVERSE_20(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20) _20,_19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1

/**
 * @def PVC_TYPE_SUFFIX(T)
 *
 * @brief Yield suffix associated with type.
 *
 * Yield the suffix associated with type @a T as summarized by the following table
 * (the same conventions as in the Vector Class Library are used):
 *
 * | Suffix | Type       | Description (mnemonic)                   |
 * |-------:|:-----------|:-----------------------------------------|
 * |    `c` | `int8_t`   | 8-bit signed integer (signed char)       |
 * |   `uc` | `uint8_t`  | 8-bit unsigned integer (unsigned char)   |
 * |    `s` | `int16_t`  | 16-bit signed integer (signed short)     |
 * |   `us` | `uint16_t` | 16-bit unsigned integer (unsigned short) |
 * |    `i` | `int32_t`  | 32-bit signed integer (signed int)       |
 * |   `ui` | `uint32_t` | 32-bit unsigned integer (unsigned int)   |
 * |    `q` | `int64_t`  | 64-bit signed integer                    |
 * |   `uq` | `uint64_t` | 64-bit unsigned integer                  |
 * |    `f` | `float`    | 32-bit floating-point (float)            |
 * |    `d` | `double`   | 64-bit floating-point (double)           |
 */
#define PVC_TYPE_SUFFIX(T) PVC_PASTE(_PVC_TYPE_SUFFIX_,T)
#define _PVC_TYPE_SUFFIX_int8_t    c
#define _PVC_TYPE_SUFFIX_uint8_t  uc
#define _PVC_TYPE_SUFFIX_int16_t   s
#define _PVC_TYPE_SUFFIX_uint16_t us
#define _PVC_TYPE_SUFFIX_int32_t   i
#define _PVC_TYPE_SUFFIX_uint32_t ui
#define _PVC_TYPE_SUFFIX_int64_t   q
#define _PVC_TYPE_SUFFIX_uint64_t uq
#define _PVC_TYPE_SUFFIX_float     f
#define _PVC_TYPE_SUFFIX_double    d

/**
 * @def PVC_IS_SINGLE(T)
 *
 * Yield whether floating-point type `T` is single precision.
 */
#define  PVC_IS_SINGLE(T) PVC_PASTE(_PVC_IS_SINGLE_,T)
#define _PVC_IS_SINGLE_float  1
#define _PVC_IS_SINGLE_double 0

#endif /* _PVC_META_H */
