#include <check.h>
#include "../src/roman.h"

char *r;
int n;

#suite RomanNumConversion

#tcase Int2Roman
#test some_ints_to_roman_test
    r = to_roman(1);
    ck_assert_str_eq(r, "I");
    r = to_roman(100);
    ck_assert_str_eq(r, "C");
    r = to_roman(88);
    ck_assert_str_eq(r, "LXXXVIII");
    r = to_roman(37);
    ck_assert_str_eq(r, "XXXVII");

#tcase Roman2Int
#test some_roman_nums_to_int_test
    n = from_roman("I");
    ck_assert_uint_eq(n, 1);
    n = from_roman("C");
    ck_assert_uint_eq(n, 100);
    n = from_roman("LXXXVIII");
    ck_assert_uint_eq(n, 88);
    n = from_roman("XLIX");
    ck_assert_uint_eq(n, 49);

#tcase BackAndForth
#test int_to_roman_to_int_test
    for (unsigned i = 1; i < MAXNUM; ++i) {
        r = to_roman(i);
        n = from_roman(r);
        ck_assert_uint_eq(n, i);
    }
