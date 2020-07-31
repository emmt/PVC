#! /bin/sh
#                                                                   -*- TCL -*-
# gen-vect-hdr -
#
# Generate <pvc-vect.h> header.
#
#------------------------------------------------------------------------------
#
# This file is part of PVC software released under the MIT "Expat" license.
#
# Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
#
#------------------------------------------------------------------------------
# The next line restarts using tclsh \
    exec tclsh "$0" "$@"

#------------------------------------------------------------------------------
#
# Definitions of intrinsic functions.
#
namespace eval ::vect::intrinsics {
    # Namespace variable to store all definitions.
    variable db

    proc __init__ {} {
        variable db
        unset -nocomplain db
        # Element-wise arithmetic operations.
        #
        # i8  _epi8  8-bit integer
        # u8  _epu8  8-bit unsigned integer
        # i16 _epi16 16-bit integer
        # u16 _epu16 16-bit unsigned integer
        # i32 _epi32 32-bit integer
        # u32 _epu32 32-bit unsigned integer
        # i64 _epi64 64-bit integer
        # u64 _epu64 64-bit unsigned integer
        # f   _ps    32-bit floating-point
        # d   _pd    64-bit floating-point
        #
        # Addition/subtraction.
        __def__ 128 {add sub} {f}                SSE
        __def__ 128 {add sub} {i8 i16 i32 i64 d} SSE2
        __def__ 256 {add sub} {f d}              AVX
        __def__ 256 {add sub} {i8 i16 i32 i64}   AVX2
        __def__ 512 {add sub} {i32 f d}          AVX512F; # KNCNI
        __def__ 512 {add sub} {i64}              AVX512F
        __def__ 512 {add sub} {i8 i16}           AVX512BW

        # Multiplication/division.
        __def__ 128 {mul div} {f}       SSE
        __def__ 128 {mul div} {d}       SSE2
        __def__ 256 {mul div} {f d}     AVX
        __def__ 256 {mul}     {i32 u32} AVX2
        __def__ 512 {mul div} {f d}     AVX512F
        __def__ 512 {mul}     {i32 u32} AVX512F

        # Addition/subtraction with saturation.
        __def__ 128 {adds subs} {i8 u8 i16 u16} SSE2
        __def__ 256 {adds subs} {i8 u8 i16 u16} AVX2
        __def__ 512 {adds subs} {i8 u8 i16 u16} AVX512BW

        # Element-wise minimum/maximum.
        __def__ 128 {min max} {f}                     SSE
        __def__ 128 {min max} {u8 i16 d}              SSE2
        __def__ 128 {min max} {i8 u16 i32 u32}        SSE4_1
        __def__ 128 {min max} {i64 u64}               {AVX512F & AVX512VL}
        __def__ 256 {min max} {f d}                   AVX
        __def__ 256 {min max} {i8 u8 i16 u16 i32 u32} AVX2
        __def__ 256 {min max} {i64 u64}               {AVX512F & AVX512VL}
        __def__ 512 {min max} {i32 u32 i64 u64 f d}   AVX512F
        __def__ 512 {min max} {i8 u8 i16 u16}         AVX512BW

        # Fused multiply-add.
        __def__ {128 256} {fmadd fmsub} {f d} FMA
        __def__ 512       {fmadd fmsub} {f d} AVX512F

        # Load/store/setzero operations.
        foreach op {load loadu store storeu setzero} {
            set db(instr,_mm_${op}_si128)     SSE2
            set db(instr,_mm_${op}_ps)        SSE
            set db(instr,_mm_${op}_pd)        SSE2

            set db(instr,_mm256_${op}_si256)  AVX
            set db(instr,_mm256_${op}_ps)     AVX
            set db(instr,_mm256_${op}_pd)     AVX

            set db(instr,_mm512_${op}_si512)  AVX512F
            set db(instr,_mm512_${op}_ps)     AVX512F
            set db(instr,_mm512_${op}_pd)     AVX512F
        }
    }

    # Private method, define multiple intrinsic functions.
    proc __def__ {sizes ops types instr} {
        variable db
        foreach size $sizes {
            switch -exact -- $size {
                xmm - 128 {
                    set nbits 128
                    set pfx "_mm"
                }
                ymm - 256 {
                    set nbits 256
                    set pfx "_mm256"
                }
                zmm - 512 {
                    set nbits 512
                    set pfx "_mm512"
                }
                default {
                    error "Invalid packed vector size \"$size\""
                }
            }
            foreach type $types {
                switch -exact -- $type {
                    i8 - u8 - i16 - u16 - i32 - u32 - i64 - u64 {
                        set sfx ep$type
                    }
                    f {
                        set sfx ps
                    }
                    d {
                        set sfx pd
                    }
                    default {
                        error "Invalid element type \"$type\""
                    }
                }
                foreach op $ops {
                    set func ${pfx}_${op}_${sfx}
                    if {[info exists db(instr,$func)]} {
                        error "Duplicate definition for \"$func\""
                    }
                    set db(instr,$func) $instr
                }
            }
        }
    }

    proc parse_function func {
        set re {^(_mm|_mm256|_mm512)_([a-z]+)_(ep[iu](8|16|32|64|128)|p[sd]|si[0-9]+)$}
        if {[regexp -- $re $func all pfx op sfx]} {
            return [list $pfx $op $sfx]
        }
    }

    proc get_nbits arg {
        switch -exact -- $arg {
            xmm - 128 {
                return 128
            }
            ymm - 256 {
                return 256
            }
            zmm - 512 {
                return 512
            }
            default {
                error "Unknown number of bits for \"$arg\""
            }
        }
    }

    # TO DO: directly understand vector type as unique argument.
    #
    # Yield the intrinsic function to perform given operation on registers
    # of given size with given element type.
    proc get_function {op arg1 arg2} {
        variable db
        switch -exact -- $arg1 {
            xmm - 128 {
                set nbits 128
                set pfx "_mm"
            }
            ymm - 256 {
                set nbits 256
                set pfx "_mm256"
            }
            zmm - 512 {
                set nbits 512
                set pfx "_mm512"
            }
            default {
                error "Invalid packed vector size \"$arg1\""
            }
        }
        switch -exact -- $arg2 {
            c - int8_t - i8 {
                set sfx epi8
            }
            uc - uint8_t - u8 {
                set sfx epu8
            }
            s - int16_t - i16 {
                set sfx epi16
            }
            us - uint16_t - u16 {
                set sfx epu16
            }
            i - int32_t - i32 {
                set sfx epi32
            }
            ui - uint32_t - u32 {
                set sfx epu16
            }
            l - int64_t - i64 {
                set sfx epi64
            }
            ul - uint64_t - u64 {
                set sfx epu16
            }
            f - float - f32 - s {
                set sfx ps
            }
            d - double - f64 {
                set sfx pd
            }
            default {
                error "Invalid element type \"$arg2\""
            }
        }
        set func ${pfx}_${op}_${sfx}
        if {[info exists db(instr,$func)]} {
            return $func
        }
        if {[string match "ep*" $sfx]} {
            set func ${pfx}_${op}_si${nbits}
            if {[info exists db(instr,$func)]} {
                return $func
            }
        }
    }

    proc get_define func {
        variable db
        if {![info exists db(instr,$func)]} {
            error "Unknown intrinsic function \"$func\""
        }
        set instr $db(instr,$func)
        regsub -all -- { +} $instr "" instr
        regsub -all -- {\|+} $instr " || " instr
        regsub -all -- {\&+} $instr " \\&\\& " instr
        regsub -all -- {([A-Z][A-Z0-9_]*)} $instr "defined(__\\1__)" instr
        return $instr
    }

    # This must be the last instruction.
    __init__
}

#------------------------------------------------------------------------------
#
# Management of C code buffer with automatic indentation.
#
namespace eval ::vect::code {
    # Namespace variable to store settings and state.
    variable db
    unset -nocomplain db
    set db(buffer)  ""
    set db(level)   0
    set db(tabsize) 4; # spaces per indentation level
    set db(indent)  ""

    proc reset {} {
        variable db
        set db(buffer)  ""
        set db(level)   0
        set db(indent)  ""
    }

    # Push a code line or a comment block in the code buffer.
    proc push args {
        variable db
        set code [join $args " "]
        set temp [string trimright $code " "]; # Trim leading spaces
        if {[string match "#*" $temp] || [string match "/\\**" $temp]} {
            # This is a comment block or a preprocessor directive.
            append db(buffer) $code "\n"
        } else {
            # Trim C++ style comment.
            set i [string first "//" $temp]
            if {$i >= 0} {
                set temp [string range $temp 0 [expr {$i - 1}]]
            }
            set level $db(level)
            if {[string index $temp 0] eq "\}"} {
                # Decrease indentation level for this line if
                # first non-space character is a closing brace.
                incr level -1
            }
            if {$level < 0} {
                set level 0
            }
            if {![info exists db(indent,$level)]} {
                set n [expr {$level*$db(tabsize)}]
                set db(indent,$level) [format "%${n}s" ""]
            }
            append db(buffer) $db(indent,$level) $code "\n"
            if {$temp ne ""} {
                # Count brace level.
                set adj 0
                set off 0
                while {true} {
                    set off [string first "\{" $temp $off]
                    if {$off < 0} {
                        break
                    }
                    incr adj
                    incr off
                }
                set off 0
                while {true} {
                    set off [string first "\}" $temp $off]
                    if {$off < 0} {
                        break
                    }
                    incr adj -1
                    incr off
                }
                if {$adj != 0} {
                    incr db(level) $adj
                    if {$db(level) < 0} {
                        set db(level) 0
                        error "Too many closing braces"
                    }
                }
            }
        }
    }

    # Print code to given channel and clear buffer.
    proc print chn {
        puts -nonewline $chn [take]
    }

    # Clear code buffer.
    proc clear {} {
        variable db
        set db(buffer) ""
    }

    # Take code buffer.
    proc take {} {
        variable db
        set code $db(buffer)
        set db(buffer) ""
        return $code
    }
}

#------------------------------------------------------------------------------
#
# Generate C code for vectorized operations.
#
namespace eval ::vect {
    # Initial configuration.
    variable config
    array unset config
    set config(library,name) "PVC"
    set config(library,prefix) "pvc_"
    set config(style) "abbrev"; # "abbrev" or "canonic"
    set config(tabsize) 4; # spaces per indentation level


    proc packed {op typ} {
        global std
        return $std(pkd,pfx,$typ)$op$std(pkd,sfx,$typ)
    }

    proc define {op ret func args req} {
        #global db
        #set dp($op,$func) [list $op $ret $func $args $req]
        #puts [format "%s %-7s %-20s {%s} %s" [string toupper $op] $ret $func $args $req]
    }
    proc is_xmm typ {
        string match "__m128*" $typ
    }
    proc is_ymm typ {
        string match "__m256*" $typ
    }
    proc is_zmm typ {
        string match "__m512*" $typ
    }

    # A "short" type is of the form "${eltype}" for a scale and of the
    # form "${nelem}${eltype}" for a packed vector type, where
    # "${eltype}" depends on the style and "${nelem}" is the number of
    # elements.
    #
    # config(style)               => naming style, "abbrev" or "canonic"
    # config(intrinsic_nbits)     => list of packed vector lengths in bits
    # config(types)               => list of unique short types
    # config(canonic_eltypes)     => list of canonic scalar types
    # config(abbrev_eltypes)      => list of abbreviated scalar types
    # config(eltypes)             => list of unique short scalar types
    # config(canonic_eltype,$typ) => canonic scalar type for $typ
    # config(abbrev_eltype,$typ)  => abbreviated scalar type for $typ
    # config(type,$typ)           => short type for $typ
    # config(ctype,$typ)          => C type for $typ
    # config(eltype,$typ)         => short element type for $typ
    # config(elsize,$typ)         => number of bytes per element in type $typ
    # config(nelem,$typ)          => number of elements in type $typ
    # config(nbits,$typ)          => number of bits for type $typ
    # config(size,$typ)           => number of bytes for type $typ
    # config(type,$typ)           => short type for $typ
    # config(is_scalar,$typ)      => type $typ is scalar
    # config(is_vector,$typ)      => type $typ is packed vector
    # config(is_signed,$typ)      => elements in type $typ are signed
    # config(is_unsigned,$typ)    => elements in type $typ are unsigned
    # config(is_float,$typ)       => elements in type $typ are floating-point
    # config(is_integer,$typ)     => elements in type $typ are integer

    # Define intrinsic functions that will be used.
    proc init {{style "abbrev"}} {
        variable config

        if {! [info exists config(style)]} {
            set config(style) "abbrev"
        }
        set style $config(style)
        if {$style ne "abbrev" && $style ne "canonic"} {
            error "Unknown style \"$style\""
        }

        # Standard settings.
        set config(register,128) "xmm"
        set config(register,256) "ymm"
        set config(register,512) "zmm"

        # Scalar types.
        foreach {canonic abbrev} {
            i8  c
            u8  uc
            i16 s
            u16 us
            i32 i
            u32 ui
            i64 l
            u64 ul
            f32 f
            f64 d
        } {
            if {[scan $canonic "%1\[iuf\]%d%s" t nbits nil] != 2} {
                error "Invalid scalar type \"$canonic\""
            }
            set size     [expr {$nbits/8}]
            set signed   [expr {$t ne "u"}]
            set float    [expr {$t eq "f"}]
            set integer  [expr {!$float}]
            set unsigned [expr {!$signed}]
            if {$style eq "abbrev"} {
                set type $abbrev
            } else {
                set type $canonic
            }
            set eltype $type
            if {$integer && $signed} {
                set ctype int${nbits}_t
            } elseif {$integer && $unsigned} {
                set ctype uint${nbits}_t
            } elseif {$abbrev eq "f"} {
                set ctype float
            } elseif {$abbrev eq "d"} {
                set ctype double
            } else {
                error "Unknown C type for canonic type \"$canonic\""
            }
            lappend config(types) $type
            lappend config(eltypes) $eltype
            lappend config(canonic_eltypes) $canonic
            lappend config(abbrev_eltypes) $abbrev
            foreach field [list $canonic $abbrev] {
                set config(abbrev_eltype,$field) $abbrev
                set config(canonic_eltype,$field) $canonic
                set config(type,$field) $type
                set config(ctype,$field) $ctype
                set config(nelem,$field) 1
                set config(nbits,$field) $nbits
                set config(size,$field) $size
                set config(elsize,$field) $size
                set config(eltype,$field) $eltype
                set config(is_scalar,$field) 1
                set config(is_vector,$field) 0
                set config(is_signed,$field) $signed
                set config(is_unsigned,$field) $unsigned
                set config(is_integer,$field) $signed
                set config(is_float,$field) $signed
            }
        }

        # Vector types.
        set config(intrinsic_nbits) [lsort -increasing -integer {128 256 512}]
        set config(intrinsic_nbits_decreasing) \
            [lsort -decreasing -integer $config(intrinsic_nbits)]
        foreach eltype $config(eltypes) {
            foreach nbits $config(intrinsic_nbits) {
                set size  [expr {$nbits/8}]
                set nelem [expr {$size/$config(size,$eltype)}]
                set type ${nelem}${eltype}
                set ctype PVC_Vect${type}
                lappend config(types) $type
                lappend config(vector_ctypes) $ctype
                lappend config(all_types) $ctype $type
                foreach field [list $type $ctype] {
                    set config(ctype,$field) $ctype
                    set config(type,$field) $type
                    set config(size,$field) $size
                    set config(nbits,$field) $nbits
                    set config(nelem,$field) $nelem
                    set config(eltype,$field) $eltype
                    set config(elsize,$field) $config(elsize,$eltype)
                    set config(is_scalar,$field) 0
                    set config(is_vector,$field) 1
                    set config(is_integer,$field) $config(is_integer,$eltype)
                    set config(is_float,$field) $config(is_float,$eltype)
                    set config(is_signed,$field) $config(is_signed,$eltype)
                    set config(is_unsigned,$field) $config(is_unsigned,$eltype)
                }
            }
        }
    }

    proc backslashify code {
        set lines [split $code "\n"]
        set n [llength $lines]
        if {$n == 0} {
            return
        } elseif {$n == 1} {
            return [string trimright [lindex $lines 0]]
        }
        set last [expr {$n - 1}]
        set maxlen 0
        for {set i 0} {$i < $last} {incr i} {
            set line [string trimright [lindex $lines $i]]
            set len [string length $line]
            set maxlen [expr {max($maxlen,$len)}]
        }
        set fmt [format "%%-%ds \\\n" $maxlen]
        set result ""
        for {set i 0} {$i < $last} {incr i} {
            append result [format $fmt [string trimright [lindex $lines $i]]]
        }
        append result [string trimright [lindex $lines $last]]
    }

    proc generic {name macro_args ctrl_expr suffixes func_args} {
        variable config
        set code "#define "
        append code ${name} \
            "(" [join $macro_args ", "] ")\n    _Generic(" $ctrl_expr ",\n"
        set last [lindex $suffixes end]
        foreach sfx $suffixes {
            if {$sfx ne $last} {
                set eol ",\n"
            } else {
                set eol ")"
                append eol "(" [join $func_args ", "] ")"
            }
            set ctype $config(ctype,$sfx)
            append code [format "%13s%-13s" "" ${ctype}:] " " \
                ${name}_${sfx} $eol
        }
        backslashify $code
    }

    # Get number of element per vector.  Argument can be a vector
    # type, a function name, a suffix.
    proc nelem arg {
        variable config

        if {[scan $arg "PVC_Vect%d" n] == 1} {
            return $n
        }
        set i [string last "_" $arg]
        if {$i >= 0} {
            if {[scan [string range $arg [expr {$i + 1}] end] "%d" n] == 1} {
                return $n
            }
        } else {
            if {[scan $arg "%d" n] == 1} {
                return $n
            }
        }
        error "Cannot guess packed vector type from \"$arg\""
    }

    # Append a line of code to a variable.
    proc push {varname args} {
        upvar $varname var
        eval append var $args "\n"
    }

    # Conversion of variables/field names to avoid issues with macro
    # definitions.
    proc protect_symbol name {
        variable config
        set pfx [string tolower $config(library,prefix)]
        return _${pfx}${name}
    }

    # Yields the intrinsic C type for a packed vector of given size
    # (in bits) storing given type of elements.
    proc intrinsic_packed_ctype {nbits eltype} {
        variable config
        set abbrev $config(abbrev_eltype,$eltype)
        if {$abbrev eq "f"} {
            set ext ""
        } elseif {$abbrev eq "d"} {
            set ext "d"
        } else {
            set ext "i"
        }
        return __m${nbits}${ext}
    }

    # Yields the name of the intrinsic function to apply an
    # elementwise operation to a packed vector.
    proc intrinsic_elementwise_function {func nbits eltype} {
        variable config
        if {$nbits == 128} {
            set pfx "_mm_"
        } elseif {$nbits == 256} {
            set pfx "_mm256_"
        } elseif {$nbits == 512} {
            set pfx "_mm512_"
        } else {
            error "Invalid number of bits \"$nbits\""
        }
        set abbrev $config(abbrev_eltype,$eltype)
        if {$abbrev eq "f"} {
            set sfx "_ps"
        } elseif {$abbrev eq "d"} {
            set sfx "_pd"
        } else {
            # Packed integers.
            if {$func eq "setzero" || $func eq "load" || $func eq "loadu" ||
                $func eq "store" || $func eq "storeu"} {
                set sfx "_si${nbits}"
            } else {
                error "Unknown intrinsic elementwise function \"$func\""
           }
        }
        return ${pfx}${func}${sfx}
    }

    # Yields the instruction level for pacjed vectors of given size
    # (in bits) storing a given type of elements.
    proc intrinsic_packed_level {nbits eltype} {
        variable config
        set abbrev $config(abbrev_eltype,$eltype)
        if {$nbits == 128} {
            if {$abbrev eq "f"} {
                return "SSE"
            } else {
                return "SSE2"
            }
        } elseif {$nbits == 256} {
            return "AVX"
        } elseif {$nbits == 512} {
            return "AVX512F"
        }
        error "Invalid number of bits \"$nbits\""
    }

    proc encode {{chn stdout}} {
        variable config
        set LIBPFX [string toupper $config(library,prefix)]
        set libpfx [string tolower $config(library,prefix)]
        set soft [string trim $LIBPFX "_"]
        set headername [string trim $libpfx "_"]-vec.h
        set headermacro "_${LIBPFX}VECT_H"
        set DOXYGEN_PARSING "${LIBPFX}DOXYGEN_PARSING"

        # List of registers to try in decreasing size/efficiency order.
        set registers {zmm ymm xmm}

        code::push "/*
 * ${headername} -
 *
 * Definitions for SIMD vectors in ${soft} library.
 *
 * *** WARNING *** This code has been generated by a script, do not edit
 * *** WARNING *** directly.
 *
 *---------------------------------------------------------------------------
 *
 * This file is part of ${soft} software released under the MIT \"Expat\" license.
 *
 * Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
 */
#ifndef $headermacro
#define $headermacro 1

#include <stdalign.h>
#include <immintrin.h>
#include <pvc-math.h>

/**
 * @addtogroup vect Packed vector types and operations.
 *
 * ${soft} provides the following types:
 *
 * Note that suffixes are not quite the same as those considered in the
 * meta-programming part.  The reason is to keep readable short type
 * names.
 *
 * @\{
 */
"

        # Make a nice ordered list of vector types and list of function suffixes.
        set ctypes {}
        set suffixes {}
        foreach eltype $config(eltypes) {
            foreach nbits $config(intrinsic_nbits) {
                set elsize $config(size,$eltype)
                set nelem [expr {$nbits/8/$elsize}]
                set type ${nelem}${eltype}
                set ctype $config(ctype,$type)
                lappend ctypes $ctype
                lappend suffixes $type
            }
        }

        # Define vector types.
        foreach ctype $ctypes {
            set size   $config(size,$ctype)
            set nelem  $config(nelem,$ctype)
            set eltype $config(eltype,$ctype)
            set elnbits [expr {$nbits/$nelem}]
            if {$config(is_float,$ctype)} {
                set values "floating-point values"
            } elseif {$config(is_signed,$ctype)} {
                set values "signed integers"
            } else {
                set values "unsigned integers"
            }

            code::push "/**
 * Vector of $nelem $config(nbits,$eltype)-bit $values.
 */"
            code::push "typedef union $ctype $ctype;"
            code::push "#ifndef ${DOXYGEN_PARSING}"
            code::push "union $ctype \{"
            foreach nbits $config(intrinsic_nbits_decreasing) {
                set p [expr {$size*8/$nbits}]
                if {$p == 0} {
                    continue
                } elseif {$p == 1} {
                    set ext ""
                } else {
                    set ext "\[$p\]"
                }
                set level [intrinsic_packed_level $nbits $eltype]
                set field [protect_symbol $config(register,$nbits)]
                set packed [intrinsic_packed_ctype $nbits $eltype]
                code::push "# ifdef __${level}__"
                code::push "${packed} ${field}${ext};"
                code::push "# endif"
            }
            set vtype $config(ctype,$eltype)
            set field [protect_symbol "val"]
            code::push "alignas($size) $vtype ${field}\[$nelem\];"
            code::push "\};"
            code::push "#endif /* ${DOXYGEN_PARSING} */"
            code::print $chn
        }

        #============================================================ SETZERO =
        code::push
        code::push "/**
 * @def pvc_vzero(T)
 *
 * @brief Get a zero-filled vector of given type.
 */"
        code::push [generic pvc_vzero T "*(T)0" $suffixes {}]

        foreach ctype $ctypes {
            set nelem  $config(nelem,$ctype)
            set eltype $config(eltype,$ctype)
            set type   $config(type,$ctype); # short type used as suffix
            set size   $config(size,$ctype)
            code::push
            code::push "static inline"
            code::push "$ctype pvc_vzero_${type}(void)"
            code::push "\{"
            code::push     "return (${ctype})\{"
            set _if "#if"
            foreach register $registers {
                set nbits [intrinsics::get_nbits $register]
                set p [expr {$size*8/$nbits}]
                if {$p < 1} {
                    continue; # Register is too large.
                }
                set func [intrinsics::get_function "setzero" $register $eltype]
                if {$func eq ""} {
                    continue; # No intrinsic function for this operation.
                }
                set field [protect_symbol $register]
                set define [intrinsics::get_define $func]
                code::push "$_if $define"
                if {$p == 1} {
                    code::push ".${field} = ${func}(),"
                } else {
                    for {set i 0} {$i < $p} {incr i} {
                        code::push ".${field}\[$i\] = ${func}(),"
                    }
                }
                set _if "#elif"
            }
            if {$_if ne "#if"} {
                code::push "#else"
            }
            set field [protect_symbol "val"]
            for {set i 0} {$i < $nelem} {incr i} {
                code::push ".${field}\[$i\] = 0,"
            }
            if {$_if ne "#if"} {
                code::push "#endif"
            }
            code::push     "\};"
            code::push "\}"
        }
        code::print $chn

        #======================================================== LOAD, LOADU =
        foreach op {load loadu} {
            if {$op eq "store"} {
                set memory "aligned memory"
                set must "must"
            } else {
                set memory "memory"
                set must "may not"
            }
            code::push
            code::push "/**
 * @def pvc_v${op}(T, addr)
 *
 * @brief Load packed values from ${memory}.
 *
 * Load packed values of type @a T from address @a addr which ${must} be
 * aligned.
 */"
            code::push [generic pvc_v${op} {T addr} "*(T)0" $suffixes addr]

            foreach ctype $ctypes {
                set nelem  $config(nelem,$ctype)
                set eltype $config(eltype,$ctype)
                set type   $config(type,$ctype); # short type used as suffix
                set size   $config(size,$ctype)
                code::push
                code::push "static inline $ctype"
                code::push "pvc_v${op}_${type}($config(ctype,$eltype) const* addr)"
                code::push "\{"
                code::push     "return (${ctype})\{"
                set _if "#if"
                foreach register $registers {
                    set nbits [intrinsics::get_nbits $register]
                    set p [expr {$size*8/$nbits}]
                    if {$p < 1} {
                        continue; # Register is too large.
                    }
                    set func [intrinsics::get_function $op $register $eltype]
                    if {$func eq ""} {
                        continue; # No intrinsic function for this operation.
                    }
                    set field [protect_symbol $register]
                    set define [intrinsics::get_define $func]
                    code::push "$_if $define"
                    if {$p == 1} {
                        code::push ".${field} = ${func}(addr),"
                    } else {
                        for {set i 0} {$i < $p} {incr i} {
                            set k [expr {$i*$nelem/$p}]
                            code::push ".${field}\[$i\] = ${func}(&addr\[$k\]),"
                        }
                    }
                    set _if "#elif"
                }
                if {$_if ne "#if"} {
                    code::push "#else"
                }
                set field [protect_symbol "val"]
                for {set i 0} {$i < $nelem} {incr i} {
                    code::push ".${field}\[$i\] = addr\[$i\],"
                }
                if {$_if ne "#if"} {
                    code::push "#endif"
                }
                code::push     "\};"
                code::push "\}"
            }
            code::print $chn
        }

        #============================================================== LOADP =
        code::push
        code::push "/**
 * @def pvc_vloadp(T, n, addr)
 *
 * @brief Partial load of packed values from memory.
 *
 * Load @a n consecutive values of type @a T from address @a addr which may not be
 * aligned.
 */"
        code::push [generic pvc_vloadp {T n addr} "*(T)0" $suffixes {n addr}]

        #====================================================== STORE, STOREU =
        foreach op {store storeu} {
            if {$op eq "store"} {
                set memory "aligned memory"
                set must "must"
            } else {
                set memory "memory"
                set must "may not"
            }
            code::push
            code::push "/**
 * @def pvc_v${op}(addr, vect)
 *
 * @brief Store packed values to ${memory}.
 *
 * Store packed values @a vect into memory at address @a addr which ${must} be
 * aligned.
 */"
            code::push [generic pvc_v${op} {addr vect} "(vect)" $suffixes {addr vect}]

            foreach ctype $ctypes {
                set nelem  $config(nelem,$ctype)
                set eltype $config(eltype,$ctype)
                set type   $config(type,$ctype); # short type used as suffix
                set size   $config(size,$ctype)
                code::push
                code::push "static inline void"
                code::push "pvc_v${op}_${type}($config(ctype,$eltype)* addr, $ctype vect)"
                code::push "\{"
                set _if "#if"
                foreach register $registers {
                    set nbits [intrinsics::get_nbits $register]
                    set p [expr {$size*8/$nbits}]
                    if {$p < 1} {
                        continue; # Register is too large.
                    }
                    set func [intrinsics::get_function $op $register $eltype]
                    if {$func eq ""} {
                        continue; # No intrinsic function for this operation.
                    }
                    set field [protect_symbol $register]
                    set define [intrinsics::get_define $func]
                    code::push "$_if $define"
                    if {$p == 1} {
                        code::push "${func}(addr, vect.${field}),"
                    } else {
                        for {set i 0} {$i < $p} {incr i} {
                            set k [expr {$i*$nelem/$p}]
                            code::push "${func}(&addr\[$k\], vect.${field}\[$i\]),"
                        }
                    }
                    set _if "#elif"
                }
                if {$_if ne "#if"} {
                    code::push "#else"
                }
                set field [protect_symbol "val"]
                for {set i 0} {$i < $nelem} {incr i} {
                    code::push "addr\[$i\] = vect.${field}\[$i\],"
                }
                if {$_if ne "#if"} {
                    code::push "#endif"
                }
                code::push "\}"
            }
            code::print $chn
       }

        #============================================================= STOREP =
        code::push
        code::push "/**
 * @def pvc_vstorep(addr, n, vect)
 *
 * @brief Partial store of packed values to memory.
 *
 * Store the @a n first values of @a vect to memory at address @a addr which may not be
 * aligned.
 */"
        code::push [generic pvc_vstorep {addr n vect} "(vect)" \
                        $suffixes {addr n vect}]

        #======================================= ADD, SUB, MUL, DIV, MIN, MAX =
        foreach {op brief format} {
            add "Add packed values"        {%s + %s}
            sub "Subtract packed values"   {%s - %s}
            mul "Multiply packed values"   {%s * %s}
            div "Divide packed values"     {%s / %s}
            min "Element-wise minimum"     {pvc_min(%s, %s)}
            max "Element-wise maximum"     {pvc_max(%s, %s)}
        } {
            code::push
            code::push "/**
 * @def c = pvc_v${op}(a, b)
 *
 * @brief ${brief}.
 */"
            code::push [generic pvc_v${op} {a b} "(a)" $suffixes {a b}]

            foreach ctype $ctypes {
                set nelem  $config(nelem,$ctype)
                set eltype $config(eltype,$ctype)
                set type   $config(type,$ctype); # short type used as suffix
                set size   $config(size,$ctype)
                code::push
                code::push "static inline $ctype"
                code::push "pvc_v${op}_${type}($ctype a, $ctype b)"
                code::push "\{"
                code::push     "return (${ctype})\{"
                set _if "#if"
                foreach register $registers {
                    set nbits [intrinsics::get_nbits $register]
                    set p [expr {$size*8/$nbits}]
                    if {$p < 1} {
                        continue; # Register is too large.
                    }
                    set func [intrinsics::get_function $op $register $eltype]
                    if {$func eq ""} {
                        continue; # No intrinsic function for this operation.
                    }
                    set field [protect_symbol $register]
                    set define [intrinsics::get_define $func]
                    code::push "$_if $define"
                    if {$p == 1} {
                        code::push ".${field} = ${func}(a.${field}, b.${field}),"
                    } else {
                        for {set i 0} {$i < $p} {incr i} {
                            set elem "${field}\[$i\]"
                            code::push ".${elem} = ${func}(a.${elem}, b.${elem}),"
                        }
                    }
                    set _if "#elif"
                }
                if {$_if ne "#if"} {
                    code::push "#else"
                }
                set field [protect_symbol "val"]
                for {set i 0} {$i < $nelem} {incr i} {
                    set elem "${field}\[$i\]"
                    set expr [format $format "a.${elem}" "b.${elem}"]
                    code::push ".${elem} = ${expr},"
                }
                if {$_if ne "#if"} {
                    code::push "#endif"
                }
                code::push     "\};"
                code::push "\}"
            }
            code::print $chn
       }

        code::push "/** @\} */

#endif /* $headermacro */"
        code::print $chn
    }

}

if {! $tcl_interactive} {
    vect::init
    vect::encode
}
