# Location of the sources.
srcdir = .

# To compile with Anger Fog's Vector Class Library (VCL, available at
# https://github.com/vectorclass/version2/), it is sufficient to
# define the VCL_DIR variable to the directroy where the VLC header
# files are stored.
VCL_DIR = ./vcl
VCL_INC = -I"$(VCL_DIR)"

CC = gcc
CPPFLAGS = -I.
# Options -O3 -ffast-math are a must for CLang and GCC.
# CLang produces faster vectorized code than GCC.
CFLAGS = -O3 -ffast-math
CXX = g++ -std=c++17
CXXFLAGS = $(CFLAGS) $(VCL_INC)

PTHREAD_LIBS = -lpthread
PTHREAD_FLAGS =

# Replace with $(srcdir)/tee.sh if the tee command is not available.
TEE = tee

LEVEL_2_FLAGS = -DINSTRSET=2 -msse2
LEVEL_3_FLAGS = -DINSTRSET=3 -msse3
LEVEL_4_FLAGS = -DINSTRSET=4 -mssse3
LEVEL_5_FLAGS = -DINSTRSET=5 -msse4.1
LEVEL_6_FLAGS = -DINSTRSET=6 -msse4.2
LEVEL_7_FLAGS = -DINSTRSET=7 -mavx
LEVEL_8_FLAGS = -DINSTRSET=8 -mfma -mavx2
LEVEL_9_FLAGS = -DINSTRSET=9 -mfma -mavx512f
LEVEL_10_FLAGS = -DINSTRSET=10 -mfma -mavx512vl -mavx512bw -mavx512dq
LEVEL_MAX_FLAGS = $(LEVEL_10_FLAGS)
REF_FLAGS = -march=native

OBJS = \
    timing.o \
    init.o \
    vdot_ref.o \
    vdot_2.o \
    vdot_3.o \
    vdot_4.o \
    vdot_5.o \
    vdot_6.o \
    vdot_7.o \
    vdot_8.o \
    vdot_9.o \
    vdot_10.o
TESTS = \
    test1 \
    test2

STATIC_LIBRARY = libpvc.a

default: all

all: $(STATIC_LIBRARY) $(TESTS)

clean:
	rm -f $(OBJS) $(TESTS) *~
	rm -f *.o preprocessing-tests-*

$(STATIC_LIBRARY): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)
	ranlib $@

$(srcdir)/pvc-vect.h: $(srcdir)/gen-vect-hdr.tcl
	test -e "$@" && mv -f "$@" "$@.bak"
	tclsh "$<" >"$@"

init.o: $(srcdir)/init.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(PTHREAD_FLAGS) -c "$<"

timing.o: $(srcdir)/timing.c $(srcdir)/pvc.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c "$<"

test1: $(srcdir)/test1.c $(srcdir)/pvc.h init.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $< init.o -o $@ $(PTHREAD_LIBS)

test2: $(srcdir)/test2.c $(srcdir)/pvc.h $(STATIC_LIBRARY)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(STATIC_LIBRARY) $(PTHREAD_LIBS) -lm

$(srcdir)/vdot.c:
	ln -s vdot.cpp "$(srcdir)/vdot.c"

vdot_ref.o: $(srcdir)/vdot.c $(srcdir)/pvc.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -DDISPATCH $(REF_FLAGS) -c $< -o $@
vdot_2.o: $(srcdir)/vdot.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LEVEL_2_FLAGS) -c $< -o $@
vdot_3.o: $(srcdir)/vdot.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LEVEL_3_FLAGS) -c $< -o $@
vdot_4.o: $(srcdir)/vdot.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LEVEL_4_FLAGS) -c $< -o $@
vdot_5.o: $(srcdir)/vdot.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LEVEL_5_FLAGS) -c $< -o $@
vdot_6.o: $(srcdir)/vdot.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LEVEL_6_FLAGS) -c $< -o $@
vdot_7.o: $(srcdir)/vdot.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LEVEL_7_FLAGS) -c $< -o $@
vdot_8.o: $(srcdir)/vdot.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LEVEL_8_FLAGS) -c $< -o $@
vdot_9.o: $(srcdir)/vdot.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LEVEL_9_FLAGS) -c $< -o $@
vdot_10.o: $(srcdir)/vdot.cpp $(srcdir)/pvc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LEVEL_10_FLAGS) -c $< -o $@

TEST_ID = gcc-native
TEST_CC = $(shell "$(srcdir)/config.sh" --cc $(TEST_ID))
TEST_CFLAGS = $(shell "$(srcdir)/config.sh" --cflags $(TEST_ID))
TEST_CC_VERSION = $(shell "$(srcdir)/config.sh" --version $(TEST_ID))
preprocessing-$(TEST_ID).o: $(srcdir)/preprocessing.c $(srcdir)/preprocessing.h
	$(TEST_CC) $(CPPFLAGS) $(TEST_CFLAGS) -c "$<" -o "$@"
preprocessing-tests-$(TEST_ID).o: $(srcdir)/preprocessing-tests.c $(srcdir)/preprocessing.h $(srcdir)/pvc.h
	$(TEST_CC) $(CPPFLAGS) $(TEST_CFLAGS) \
	    -DCOMPILER_COMMAND="\"$(TEST_CC) $(TEST_CFLAGS)\"" -c "$<" -o "$@"
#preprocessing-tests-$(TEST_ID).o: $(srcdir)/preprocessing-tests.c $(srcdir)/preprocessing.h $(srcdir)/pvc.h
# 	$(TEST_CC) $(CPPFLAGS) $(TEST_CFLAGS) \
# 	    -DCOMPILER_COMMAND="\"$(TEST_CC) $(TEST_CFLAGS)\"" \
# 	    -DCOMPILER_VERSION="\"$(TEST_CC_VERSION)\"" -c "$<" -o "$@"
timing-$(TEST_ID).o: $(srcdir)/timing.c $(srcdir)/pvc.h
	$(TEST_CC) $(CPPFLAGS) $(TEST_CFLAGS) -c "$<" -o "$@"
preprocessing-tests-$(TEST_ID): preprocessing-tests-$(TEST_ID).o preprocessing-$(TEST_ID).o timing-$(TEST_ID).o
	$(TEST_CC) preprocessing-tests-$(TEST_ID).o preprocessing-$(TEST_ID).o timing-$(TEST_ID).o -o "$@" -lm
preprocessing-tests-$(TEST_ID).out: preprocessing-tests-$(TEST_ID)
	./preprocessing-tests-$(TEST_ID) | $(TEE) preprocessing-tests-$(TEST_ID).out

preprocessing-tests: preprocessing-tests-$(TEST_ID)
run-preprocessing-tests: preprocessing-tests-$(TEST_ID).out

run-tests:
	make TEST_ID=clang-O3-fast-math-native      run-preprocessing-tests
	make TEST_ID=clang-O3-fast-math-sse2        run-preprocessing-tests
	make TEST_ID=clang-O3-fast-math-sse4        run-preprocessing-tests
	make TEST_ID=clang-O3-fast-math-avx2        run-preprocessing-tests
	make TEST_ID=gcc-O3-fast-math-native        run-preprocessing-tests
	make TEST_ID=gcc-O3-fast-math-sse2          run-preprocessing-tests
	make TEST_ID=gcc-O3-fast-math-sse4          run-preprocessing-tests
	make TEST_ID=gcc-O3-fast-math-avx2          run-preprocessing-tests
	make TEST_ID=gcc-O3-fast-math-unroll-native run-preprocessing-tests
	make TEST_ID=gcc-O3-fast-math-unroll-sse2   run-preprocessing-tests
	make TEST_ID=gcc-O3-fast-math-unroll-sse4   run-preprocessing-tests
	make TEST_ID=gcc-O3-fast-math-unroll-avx2   run-preprocessing-tests

run-types-tests: types-tests types-tests++
	./types-tests
	./types-tests++

types-tests: $(srcdir)/types-tests.c $(srcdir)/pvc-types.h
	$(CC) -O -Wall -I. $< -o $@
types-tests++: $(srcdir)/types-tests.cpp $(srcdir)/types-tests.c $(srcdir)/pvc-types.h
	$(CXX) -O -Wall -I. $< -o $@

.PHONY: clean all preprocessing-tests run-preprocessing-tests
