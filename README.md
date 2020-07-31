# PVC: Playing with Vectorization in C

PVC is a small C library for:

- Meta-programming in C.

- Tools and definitions for auto-vectorization.

- Optimized functions that benefit from *Single Instruction Multiple
  Data* (SIMD) instructions of modern CPU architectures.

Some parts of PVC consist in macro definitions or inlined-code that
require no compilation of PVC, it is sufficient to include the
suitable header files:

- [`<pvc.h>`](./src/pvc.h) for native byte order, compiler version, etc.
- [`<pvc-types.h>`](./src/pvc-types.h) for type-generic code dealing
  with basic C types (e.g., `PVC_TYPE_MAX(T)` to get the maximum
  representable value of type `T`);
- [`<pvc-math.h>`](./src/pvc-math.h) for simple in-lined math-like
  functions that evaluate their arguments only once (`pvc_min`,
  `pvc_max`, `pvc_clamp`);
- [`<pvc-meta.h>`](./src/pvc-meta.h) for meta-programming with the C
  pre-processor;
- [`<pvc-vect.h>`](./src/pvc-vect.h) for helper types and macros to
  code with intrinsic functions and vectors of packed values.

The vectorized functions provided by PVC require a C++ compiler
implementing C++17 standard (like `gcc -std=c++17`) to be built but is
intended to be called from C or C++ code.  Runtime dispatching is
exploited to have a single library that can be used with any
(supported) CPU.


## Usage

PVC is work in progress.  Go to the [src](./src) directory and edit
the definition of the variable `VCL_DIR` in file
[`src/Makefile`](./src/Makefile) to be the directory where the header
files of the VCL library are stored (see below).


## References and useful links

- Jens Gusted's book [*Modern C*](https://modernc.gforge.inria.fr/)
  about programming with C11 and C99.

- Jens Gusted's [P99
  package](https://gustedt.gitlabpages.inria.fr/p99/) for
  meta-programming in C.

- Agner Fog's [Vector Class
  Library](https://github.com/vectorclass/version2/releases) is a
  public domain C++ library (released under the Apache License version
  2.0) developed by Agner Fog's to exploit *Single Instruction
  Multiple Data* (SIMD) instructions of modern CPU architectures.  The
  library consists in header and code files that have to be included
  in the source.  The minimal requirements for using VCL version 2 is
  SSE2 and a C++ compiler implementing C++17 standard (like `gcc
  -std=c++17`).

- Agner Fog's [*Software Optimization
  Resources*](https://www.agner.org/optimize/) notably his manual
  *Optimizing software in C++*.
