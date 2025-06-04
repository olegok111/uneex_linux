#include <string.h>
#include "roman_table.h"
#include "roman.h"

/** @file libroman.c
 *
 * Logic for roman numeral conversion.
 */

char* to_roman(unsigned x) {
    return roman_table[x-1];
}

unsigned from_roman(char *r) {
    for (unsigned i = 1; i < MAXNUM + 1; ++i) {
        if (!strncmp(r, roman_table[i-1], MAX_ROMAN_LEN + 1)) {
            return i;
        }
    }
}
