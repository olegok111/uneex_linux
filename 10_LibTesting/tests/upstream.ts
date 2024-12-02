#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>
#include <check.h>

static jmp_buf escape;
#include "grobuf.h"

/* volatile due to setjmp() / longjmp() */
volatile int count_pass = 0;
volatile int count_fail = 0;

float *a = 0;
long *ai = 0;

#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

static uint32_t
pcg32(uint64_t *s)
{
    uint64_t m = 0x5851f42d4c957f2d;
    uint64_t a = 0x8b260b70b8e98891;
    uint64_t p = *s;
    uint32_t x = ((p >> 18) ^ p) >> 27;
    uint32_t r = p >> 59;
    *s = p * m + a;
    return (x >> r) | (x << (-r & 31u));
}

static unsigned long
bench(uint64_t *rng)
{
    unsigned long r = 0;
    uint32_t n = 1000000 + pcg32(rng) % 4000000;
    float *buf = 0;

    for (uint32_t i = 0; i < n; i++)
        buf_push(buf, pcg32(rng) / (double)UINT32_MAX);

    float threshold = pcg32(rng) / (double)UINT32_MAX;
    for (uint32_t i = 0; i < n; i++)
        r += buf[i] > threshold;

    buf_free(buf);
    return r;
}

#ifdef _WIN32
#include <windows.h>
uint64_t
uepoch(void)
{
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64_t tt = ft.dwHighDateTime;
    tt <<= 32;
    tt |= ft.dwLowDateTime;
    tt /=10;
    tt -= UINT64_C(11644473600000000);
    return tt;
}
#else
#include <sys/time.h>
uint64_t
uepoch(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000000LL * tv.tv_sec + tv.tv_usec;
}
#endif

#suite GrowableBuf
#tcase Benchmark
#test beachmark_test
    /* Benchtest? */
    uint64_t rng = 0x558d2750ae0e0887;
    unsigned long r = 0;
    uint64_t start = uepoch();
    for (int i = 0; i < 300; i++)
        r += bench(&rng);
    double t = (uepoch() - start) / 1e6;
    printf("%.6gs : actual %lu, expect 428859598\n", t, r);
    ck_assert_double_eq_tol(r, 428859598, 0.1);

#tcase BufFree
#test buf_free_test
    /* initialization, buf_free() */
    ck_assert_int_eq(buf_capacity(a), 0); // capacity init
    ck_assert_int_eq(buf_size(a), 0); // size init
    buf_push(a, 1.3f);
    ck_assert_int_eq(buf_size(a), 1); // size 1
    ck_assert_float_eq(a[0], (float)1.3f); // value
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0); // clear
    ck_assert_int_ne(a, 0); // clear not-free
    buf_free(a);
    ck_assert_int_eq(a, 0); // free

    /* Clearing an NULL pointer is a no-op */
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0); // clear empty
    ck_assert_int_eq(a, 0); // clear no-op

#tcase BufOps
#test buf_ops_test
    /* buf_push(), [] operator */
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_int_eq(buf_size(ai), 10000); // size 10000
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert_int_eq(match, 10000); // match 10000
    buf_free(ai);

    /* buf_grow(), buf_trunc() */
    buf_grow(ai, 1000);
    ck_assert_int_eq(buf_capacity(ai), 1000); // grow 1000
    ck_assert_int_eq(buf_size(ai), 0); // size 0 (grow)
    buf_trunc(ai, 100);
    ck_assert_int_eq(buf_capacity(ai), 100); // trunc 100
    buf_free(ai);

#tcase BufPop
#test buf_pop_test
    /* buf_pop() */
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_int_eq(buf_size(a), 4); // size 4
    ck_assert_float_eq(buf_pop(a), (float)1.4f); // pop 3
    buf_trunc(a, 3);
    ck_assert_int_eq(buf_size(a), 3); // size 3
    ck_assert_float_eq(buf_pop(a), (float)1.3f); // pop 2
    ck_assert_float_eq(buf_pop(a), (float)1.2f); // pop 1
    ck_assert_float_eq(buf_pop(a), (float)1.1f); // pop 0
    ck_assert_int_eq(buf_size(a), 0); // size 0 (pop)
    buf_free(a);
