# Notes about code vectorization

## GCC (and CLANG) options

See [on-line doc.](https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html):

* `-march=`*cpu-type*

  Generate instructions for the machine type cpu-type. In contrast to
  `-mtune=`*cpu-type*, which merely tunes the generated code for the specified
  *cpu-type*, `-march=`*cpu-type* allows GCC to generate code that may not run
  at all on processors other than the one indicated. Specifying
  `-march=`*cpu-type* implies `-mtune=`*cpu-type*.

* `-mtune=`*cpu-type*

  Tune to *cpu-type* everything applicable about the generated code, except for
  the ABI and the set of available instructions. While picking a specific
  *cpu-type* schedules things appropriately for that particular chip, the
  compiler does not generate any code that cannot run on the default machine
  type unless you use a `-march=`*cpu-type* option. For example, if GCC is
  configured for i686-pc-linux-gnu then `-mtune=pentium4` generates code that
  is tuned for Pentium 4 but still runs on i686 machines.

To enable vectorization of floating point reductions use `-ffast-math` with
GCC or CLang (option `-fassociative-math` can also be used with GCC).

With `gcc`, option `-ffast-math` also sets the options `-fno-math-errno`,
`-funsafe-math-optimizations`, `-ffinite-math-only`, `-fno-rounding-math`,
`-fno-signaling-nans`, `-fcx-limited-range` and `-fexcess-precision=fast`.

Minimal set of good compiler options for vectorization:

* with GCC:   `-O3 -march=native -ffast-math -funroll-loops`;
* with CLang: `-O3 -march=native -ffast-math`.

As of GCC 9.3.0, `-funroll-loops` is needed to unroll vectorized loops.

As of CLang 10.0.0, `-ffast-math` with `-O2` or `-O3` is all that is needed to
produce good unrolled vectorized loops.

Other possible opetions with GCC: `-fassociative-math`, `-funroll-loops`,
`-ftree-vectorize` (set by `-O3`), `-fno-trapping-math`, `-fno-math-errno`.

If appropriate, `-march=znver2` with GCC (and `-O3 -ffast-math`) is better than
`-mavx2 -mfma` or `-march=znver1` for AMD Threadripper processor but not as
good as CLang with `-O3 -ffast-math -march=native` (adding `-funroll-loops`
and/or `-ftree-vectorize` does not improve that for GCC).


## Using Intrinsics

From Agner Fog's manual:

> It is not recommended to use the vectors of 64 bits total size, because these
> are incompatible with floating point code. If you do use the 64-bit vectors
> then you have to execute `_mm_empty()` after the 64-bit vector operations and
> before any floating point code. The vectors of 128 bits and more do not have
> this problem.

Thus: **do not use 64-bit (MM) registers**.

Floating-point vectors of size 128 (XMM registers), 256 (YMM registers) and/or
256 (ZMM registers) bits may be available depending on the processor.

* 128-bit packed integers (`__m128i`) or packed single precision floating
  points (`__m128`) require SSE.  128-bit packed double precision floating
  points (`__m128d`) require SSE2.

* 256-bit packed integers (`__m256i`), packed single precision floating points
  (`__m256`) or packed double precision floating points (`__m256d`) require
  AVX.

* 512-bit packed integers (`__m512i`), packed single precision floating points
  (`__m512`) or packed double precision floating points (`__m512d`) require
  AVX512F.


## Vector Class Library (VCL)

The [Vector Class Library](https://github.com/vectorclass/version2/releases) is
a public domain C++ library (released under the Apache License version 2.0)
developed by Agner Fog's to exploit *Single Instruction Multiple Data* (SIMD)
instructions of modern CPU architectures.  The library consists in header and
code files that have to be included in the source.  The minimal requirements
for using VCL version 2 is SSE2 and a C++ compiler implementing C++17 standard
(like `gcc -std=c++17`).

To simplify the many possibilities, VCL summarizes the set of available
instructions by a single integer, `INSTRSET` (for *instruction set*), and
assumes that capabilities at a given level include all capabilities of lower
levels.  The function `instrset_detect()` defined in `instrset_detect.cpp` can
be called at run-time to determine the set of instructions of the current CPU.
This can be used to dispatch to different versions of some function each
compiled for a given instruction set.


| `INSTRSET` | GCC flags                          | Description                    | Vector size (bits) |
|-----------:|:-----------------------------------|:-------------------------------|:------------------:|
|          1 | `-msse`                            | SSE                            | 128                |
|          2 | `-msse2`                           | SSE2                           | 128                |
|          3 | `-msse3`                           | SSE3                           | 128                |
|          4 | `-mssse3`                          | SSSE3                          | 128                |
|          5 | `-msse4.1`                         | SSE4.1                         | 128                |
|          6 | `-msse4.2`                         | SSE4.2                         | 128                |
|          7 | `-mavx`                            | AVX                            | 256                |
|          8 | `-mavx2 -mfma`                     | AVX2                           | 256                |
|          9 | `-mavx512f`                        | AVX512F                        | 512                |
|         10 | `-mavx512vl -mavx512bw -mavx512dq` | AVX512VL + AVX512BW + AVX512DQ | 512                |

To limit the set of instructions used by VCL, it is sufficient to define the
macro `INSTRSET` before including `<vectorclass.h>`.  If `INSTRSET` is not
defined, it is automatically determined according to the settings of the
compiler (at compile-time thus).  Setting the macro `INSTRSET` can be used to
compile a function for a given instruction set.

The script `cputest.sh` (with code `cputest.cpp`) can be used to check the
effects of the compiler flags such as `-msse3`, `-mavx`, etc.
Usage is as follows:

```.sh
./cputest.sh [FLAGS...]
```

where `[FLAGS...]` denotes the compiler flags.  The script is rather
rudumentary but may however be called with environment variables `CXX`,
`VCLDIR` and `TMPDIR` respectively set to the C++ compiler (`g++ -std=c++17` by
default), the directory VCL library sources and the temporary directory (`/tmp`
by default).  The script compiles an executable named `$TMPDIR/cputest-$USER`.
For instance:

```.sh
CXX="clang -std=c++17" ./cputest.sh -msse4
```

to check option `-msse4` with CLang compiler.


| GCC flags                                | Instructions                                                                      | `INSTRSET` |
|:-----------------------------------------|:----------------------------------------------------------------------------------|-----------:|
| `-mno-sse2`                              | SSE                                                                               |          2 |
|                                          | SSE SSE2                                                                          |          2 |
| `-msse3`                                 | SSE SSE2 SSE3                                                                     |          3 |
| `-mssse3`                                | SSE SSE2 SSE3 SSSE3                                                               |          4 |
| `-msse4.1`                               | SSE SSE2 SSE3 SSSE3 SSE4.1                                                        |          5 |
| `-msse4.2`                               | SSE SSE2 SSE3 SSSE3 SSE4.1 SSE4.2                                                 |          6 |
| `-msse4`                                 | SSE SSE2 SSE3 SSSE3 SSE4.1 SSE4.2                                                 |          6 |
| `-mavx`                                  | SSE SSE2 SSE3 SSSE3 SSE4.1 SSE4.2 AVX                                             |          7 |
| `-mfma`                                  | SSE SSE2 SSE3 SSSE3 SSE4.1 SSE4.2 AVX FMA                                         |          7 |
| `-mfma -mavx2`                           | SSE SSE2 SSE3 SSSE3 SSE4.1 SSE4.2 AVX FMA AVX2                                    |          8 |
| `-mfma -mavx512f`                        | SSE SSE2 SSE3 SSSE3 SSE4.1 SSE4.2 AVX FMA AVX2 AVX512F                            |          9 |
| `-mfma -mavx512vl -mavx512bw -mavx512dq` | SSE SSE2 SSE3 SSSE3 SSE4.1 SSE4.2 AVX FMA AVX2 AVX512F AVX512VL AVX512BW AVX512DQ |         10 |

Notes:

* Option `-msse2` is the least assumed one, so to just have SSE, `-mno-sse2`
  must be given.

* Option `-msse4` implies all SSE4 instructions (that is SSE4.2).

* Option `-mfma` should be specified with option `-mavx2` or higher.  Option
  `-mfma` alone also select AVX instructions and below.

According to the above table, it seems that GNU compiler options related to the
instruction set implement the same king of hierarchy as in VLC: *what can do
more can do less*. CLang behaves the same.

This suggest the following compiler flags to compile versions of a vectorized
function using different instruction sets (accounting for the fact that VCL is
not usable below level 2):

```
LEVEL_2_FLAGS = -DINSTRSET=2 -msse2
LEVEL_3_FLAGS = -DINSTRSET=3 -msse3
LEVEL_4_FLAGS = -DINSTRSET=4 -mssse3
LEVEL_5_FLAGS = -DINSTRSET=5 -msse4.1
LEVEL_6_FLAGS = -DINSTRSET=6 -msse4.2
LEVEL_7_FLAGS = -DINSTRSET=7 -mavx
LEVEL_8_FLAGS = -DINSTRSET=8 -mfma -mavx2
LEVEL_9_FLAGS = -DINSTRSET=9 -mfma -mavx512f
LEVEL_10_FLAGS = -DINSTRSET=10 -mfma -mavx512vl -mavx512bw -mavx512dq
```

Number of SIMD registers:
* SSE provides 128-bit vectors of single precision floats with 8 registers
  (XMM0-XMM7).
* SSE2 provides 128-bit vectors of double precision floats with 8 registers
  (XMM0-XMM7).
* SSE3, in 64-bit mode, the number of register is extended from 8 to 16.
* AVX extends the 16 128-bit registers to 256-bit registers (YMM0, YMM1, etc.).
* AVX512 extends the 16 256-bit registers to 512-bit registers (ZMM0, ZMM1, etc.).

The following commands can be used to figure out which values of `INSTRSET`
trigger different pieces of code in VCL (assuming `$VCLDIR` is the directory
where are the VCL sources):

```.sh
grep -h INSTRSET $VCLDIR/*.{h,cpp} \
    | sed -e 's,//.*,,;s/  */ /g;s/^ *# */#/;s/#elif /#if /;/INSTRSET/!d;/^#if /!d;s/[ \r]*$//;' \
    | sort -u
```

As of commit `bbb95859eeaf7cd92674166bbcf4ab083acd04ee` of VCL, the output is:

```
#if defined(__clang__) && INSTRSET < 5
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && !defined(__clang__) && INSTRSET < 5
#if false && INSTRSET >= 3
#if INSTRSET == 1
#if INSTRSET < 10
#if INSTRSET >= 10
#if INSTRSET >= 10 && defined ( __AVX512VBMI__ )
#if INSTRSET >= 10 && defined (__AVX512VBMI__)
#if INSTRSET >= 10 && defined (__AVX512VBMI2__)
#if INSTRSET >= 10 && defined(_mm256_rsqrt14_ps)
#if INSTRSET >= 10 && !defined (_MSC_VER)
#if INSTRSET >= 10 && !defined(_MSC_VER)
#if INSTRSET >= 10 && (!defined(_MSC_VER) || defined(__INTEL_COMPILER))
#if INSTRSET < 2
#if INSTRSET == 2
#if INSTRSET == 3
#if INSTRSET >= 3
#if INSTRSET >= 3 && false
#if INSTRSET == 4
#if INSTRSET >= 4
#if INSTRSET >= 4 & false
#if INSTRSET >= 4 && false
#if INSTRSET >= 4 && INSTRSET < 10
#if INSTRSET == 5
#if INSTRSET >= 5
#if INSTRSET >= 5 && defined(__x86_64__)
#if INSTRSET == 6
#if INSTRSET >= 6
#if INSTRSET == 7
#if INSTRSET > 7
#if INSTRSET >= 7
#if INSTRSET < 8
#if INSTRSET >= 8
#if INSTRSET >= 8 && !defined(__FMA__)
#if INSTRSET == 9
#if INSTRSET >= 9
#if INSTRSET == 9 && MAX_VECTOR_SIZE >= 512
#if _MSC_VER < 1920 && INSTRSET > 8
```

which shows that all levels from 1 to 10 may have an incidence.  However for
loating-point operations (`vectorf*.h` files), only levels 3, 4, 5, 7, 8, 9 and
10 seem to have an incidence.

| Processor family                                 | MMX | SSE | SSE2 | SSE3 | SSSE3 | SSE4.1 | SSE4.2 | AVX | AVX2 FMA | AVX512F | AVX512VL AVX512BW AVX512DQ | Instr. Set |
|:-------------------------------------------------|:---:|:---:|:----:|:----:|:-----:|:------:|:------:|:---:|:--------:|:-------:|:--------------------------:|-----------:|
| Pentium M, Pentium 4                             | x   | x   | x    |      |       |        |        |     |          |         |                            |          2 |
| Prescott, Nocona                                 | x   | x   | x    | x    |       |        |        |     |          |         |                            |          3 |
| Core 2, Bonnell                                  | x   | x   | x    | x    | x     |        |        |     |          |         |                            |          4 |
| Nehalem, Westmere, Silvermont, Goldmont, Tremont | x   | x   | x    | x    | x     | x      | x      |     |          |         |                            |          6 |
| Sandybridge, Ivybridge                           | x   | x   | x    | x    | x     | x      | x      | x   |          |         |                            |          7 |
| Haswell, Broadwell, Skylake, Alderlake           | x   | x   | x    | x    | x     | x      | x      | x   | x        |         |                            |          8 |
| Knight’s Landing                                 | x   | x   | x    | x    | x     | x      | x      | x   | x        | x       |                            |          9 |
| Skylake-AVX512, Cannonlake                       | x   | x   | x    | x    | x     | x      | x      | x   | x        | x       | x                          |         10 |
