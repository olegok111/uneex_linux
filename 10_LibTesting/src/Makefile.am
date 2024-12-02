CFLAGS = -std=c99 -Wall -Wextra
if COND_GCOV
CFLAGS += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS += -O3 -g3
endif

lib_LTLIBRARIES = libgrobuf.la
#bin_PROGRAMS = grobuf

libgrobuf.c: grobuf.h

gcov:
	gcov -o .libs libgrobuf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
