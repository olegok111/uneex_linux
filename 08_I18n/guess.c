#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _(STRING) gettext(STRING)

int main(int argc, char* argv[]) {
//     setlocale (LC_ALL, "");
// 	bindtextdomain (PACKAGE, LOCALE_PATH);
// 	textdomain (PACKAGE);
    setlocale(LC_ALL, "");

    const unsigned maxnum = 100;
    const unsigned guess_cnt = 7; // ceil(log2(maxnum))
    printf(_("Think of a number no less than 1 and no more than %u.\n"), maxnum);

    char* user_input = NULL;
    size_t user_input_len = 0;
    unsigned guess = maxnum / 2;
    unsigned delta = maxnum / 4;
    for (unsigned i = 0; i < guess_cnt; ++i) {
        printf(_("Is it more than %u?"), guess);
        getline(&user_input, &user_input_len, stdin);

        if (delta == 0) {
            ++delta;
        }

        if (!strncmp(user_input, _("y"), 2)) {
            guess += delta;
        } else {
            guess -= delta;
        }

        delta /= 2;
    }

    printf(_("The number must be %u\n"), guess);

    return 0;
}
