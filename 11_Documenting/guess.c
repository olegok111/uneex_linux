#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "roman_table.h"

#define _(STRING) gettext(STRING)

/*
 * Dec2Rom
 */
char* to_roman(unsigned x) {
    return roman_table[x];
}

/*
 * Rom2Dec
 */
unsigned from_roman(char *r) {
    for (unsigned i = 1; i < MAXNUM + 1; ++i) {
        if (strncmp(r, roman_table[i-1], MAX_ROMAN_LEN + 1)) {
            return i;
        }
    }
}

/*
 * Guessing game
 */
int main(void) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    printf(_("Think of a number no less than 1 and no more than %u.\n"), MAXNUM);

    char* user_input = NULL;
    size_t user_input_len = 0;
    unsigned l = 1;
    unsigned r = MAXNUM;
    while (l != r) {
        printf(_("Is the number more than %u?"), (r + l) / 2);
        getline(&user_input, &user_input_len, stdin);

        if (!strncmp(user_input, _("y\n"), 2)) {
            l = (r + l) / 2 + 1;
        } else {
            r = (r + l) / 2;
        }
    }

    printf(_("The number must be %u\n"), (r + l) / 2);

    return 0;
}
