#! /bin/sh
#
# config.sh -
#
# Script to query compiler command, options and versions according to
# unified conventions.
#
#---------------------------------------------------------------------------
#
# This file is part of PVC software released under the MIT "Expat" license.
#
# Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
#

prog=$(basename "$0")

die() {
    echo >&2 "$*"
    exit 1
}

usage() {
    echo "Usage: $prog CMD TGT"
}

if test $# -lt 1; then
    usage >&2
    exit 1
fi
command=$1
case "$command" in
    -h | --help)
        usage
        echo "Query compiler settings for target TGT, e.g. \"gcc-native\"."
        echo "Commands are:"
        echo "    --cc            Get C compiler command."
        echo "    --cxx           Get C++ compiler command."
        echo "    --version       Get version of compiler."
        echo "    --cflags        Get C optimization flags."
        echo "    --cxxflags      Get C++ optimization flags."
        echo "    -h, --help      Print this help."
        exit 0
        ;;
    --cc | --cxx | --cflags | --cxxflags | --version )
        if test $# -lt 2; then
            die "Missing target."
            exit 1
        fi
        target=$2
        ;;
    *)
        die "Unknown command \"$command\""
        ;;
esac

case "$target" in
    *-* )
        compiler=$(echo "x$target" | sed -e 's/^x\([^-]*\)-.*/\1/')
        params=$(echo "x$target" | sed -e 's/^x[^-]*-//')
        ;;
    * )
        compiler=$target
        params=""
        ;;
esac

case "$compiler" in
    gcc )
        if test "$command" = "--cc"; then
            echo "gcc"
            exit 0
        elif test "$command" = "--cxx"; then
            echo "gcc -std=c++17"
            exit 0
        elif test "$command" = "--version"; then
            echo "gcc --version"
            exit 0
        fi
        ;;

    clang )
        if test "$command" = "--cc"; then
            echo "clang"
            exit 0
        elif test "$command" = "--cxx"; then
            echo "clang -std=c++17"
            exit 0
        elif test "$command" = "--version"; then
            echo "clang --version"
            exit 0
        fi;;

    * )
        die "Unknown compiler: \"$compiler\"";;
esac

# First try preset options.
case "$params" in
    sse             | preset1 ) flags="-O3 -ffast-math -msse";;
    sse2            | preset2 ) flags="-O3 -ffast-math -msse2";;
    sse3            | preset3 ) flags="-O3 -ffast-math -msse3";;
    ssse3           | preset4 ) flags="-O3 -ffast-math -msse3";;
    ssse4.1         | preset5 ) flags="-O3 -ffast-math -msse4.1";;
    ssse4 | ssse4.2 | preset6 ) flags="-O3 -ffast-math -msse4.2";;
    avx             | preset7 ) flags="-O3 -ffast-math -mavx";;
    avx2            | preset8 ) flags="-O3 -ffast-math -mavx2 -mfma";;
    avx512f         | preset9 ) flags="-O3 -ffast-math -mavx512f";;
    avx512+         | preset10) flags="-O3 -ffast-math -mavx512vl -mavx512bw -mavx512dq";;
    native                    ) flags="-O3 -ffast-math -march=native";;
    *                         ) flags="";;
esac

if test "x$flags" != "x"; then
    echo "$flags"
    exit 0
fi

# Extract options one by one.
check_option() {
    case "$params" in
        $1 )
            params=""
            ;;
        $1-* )
            params=$(echo "$params" | sed -e "s/^$1-//")
            return 0
            ;;
        *-$1 )
            params=$(echo "x$params" | sed -e "s/^x//;s/-$1\$//")
            return 0
            ;;
        *-$1-* )
            params=$(echo "x$params" | sed -e "s/^x//;s/-$1-/-/")
            return 0
            ;;
        * )
            return 1
            ;;
    esac
}

# Get optimization level, then other options.
if check_option "Ov"; then
    flags="-O3 -ffast-math"
elif check_option "O3"; then
    flags="-O3"
elif check_option "O2"; then
    flags="-O2"
elif check_option "O1" || check_option "O"; then
    flags="-O1"
elif check_option "O0"; then
    flags="-O0"
elif check_option "Og"; then
    flags="-Og"
elif check_option "Os"; then
    flags="-Os"
elif check_option "Ofast"; then
    flags="-Ofast"
fi

if check_option "fast-math"; then
    flags="$flags -ffast-math"
fi
if check_option "unroll-loops" || check_option "unroll"; then
    flags="$flags -funroll-loops"
fi
if check_option "native"; then
    flags="$flags -march=native"
elif check_option "avx512+"; then
    flags="$flags -mavx512vl -mavx512bw -mavx512dq"
elif check_option "avx512f"; then
    flags="$flags -mavx512f"
elif check_option "avx2"; then
    flags="$flags -mavx2 -mfma"
elif check_option "avx"; then
    flags="$flags -mavx"
elif check_option "ssse4.2" || check_option "ssse4"; then
    flags="$flags -msse4.2"
elif check_option "ssse4.1"; then
    flags="$flags -msse4.1"
elif check_option "ssse3"; then
    flags="$flags -msse3"
elif check_option "sse3"; then
    flags="$flags -msse3"
elif check_option "sse2"; then
    flags="$flags -msse2"
elif check_option "sse"; then
    flags="$flags -msse"
fi
if test "x$params" != "x"; then
    die "Unknown option(s) \"$params\""
fi
echo "$flags"
exit 0
