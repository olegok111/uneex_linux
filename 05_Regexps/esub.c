#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAXGR 10
// #define DBG

void print_bag(char *buf, regmatch_t *bags, int bagi) {
    printf("%.*s", bags[bagi].rm_eo - bags[bagi].rm_so, buf + bags[bagi].rm_so);
}

int main(int argc, char *argv[]) {
    char *buf = argv[3];
    int input_len = strlen(argv[3]);
    char *regex_string = argv[1];
    char *subst = argv[2];
    int subst_len = strlen(subst);
    regex_t regex;
    regmatch_t bags[MAXGR];
    int re_errcode;

    if (argc != 4) {
        printf(
"Usage: esub REGEXP SUBSTITUTION STRING\n" \
"Substitute the result of matching REGEXP on STRING with SUBSTITUTION, using\n" \
" ERE syntax. Produces same result as \n" \
" \"echo 'STRING' | sed -E 's/REGEXP/SUBSTITUTION/'\".\n"
);
        return 1;
    }

    if ((re_errcode = regcomp(&regex, regex_string, REG_EXTENDED)) == 0) {
        if (regexec(&regex, argv[3], MAXGR, bags, 0) == 0) {
#ifdef DBG
            printf("argv[3]: \"%s\"\n", argv[3]);

            for (int i = 0; i < MAXGR && bags[i].rm_so >= 0; i++) {
                int b = bags[i].rm_so, e = bags[i].rm_eo;
                printf("BAG #%d [%d:%d]: \"%.*s\"\n", i, b, e, e - b, argv[3] + b);
            }
#endif

            for (int i = 0; i < input_len; ++i) {
                if (bags[0].rm_so <= i && i < bags[0].rm_eo) {
                    for (int j = 0; j < subst_len; ++j) {
                        if (j < subst_len - 1 && subst[j] == '\\' && '0' <= subst[j+1] && subst[j+1] <= '9') {
                            print_bag(buf, bags, subst[j+1] - '0');
                            ++j; // skip the bag number
                        } else {
                            putchar(subst[j]);
                        }
                    }

                    i = bags[0].rm_eo - 1; // skip to last char in full match
                } else {
                    putchar(buf[i]);
                }
            }
        }
    }

    regfree(&regex);
    return 0;
}
