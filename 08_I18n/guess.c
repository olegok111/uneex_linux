#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define _(STRING) gettext(STRING)

int main(void) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    const unsigned maxnum = 100;
    printf(_("Think of a number no less than 1 and no more than %u.\n"), maxnum);

    char* user_input = NULL;
    size_t user_input_len = 0;
    unsigned l = 1;
    unsigned r = maxnum;
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
