#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>

#include "config.h"
#include "roman_table.h"

#define _(STRING) gettext(STRING)
#define N_(STRING) (STRING)

/** @mainpage Number guessing game
 * @copydetails guessing-game-desc
 *
 * Help (EN):
 * ```
 * Usage: guess [OPTION...]
 * A game where the computer guesses the number picked by the player.
 *
 * -r, --roman                Use roman numerals
 * -?, --help                 Give this help list
 *     --usage                Give a short usage message
 * -V, --version              Print program version
 *
 * Report bugs to BUG-REPORT-ADDRESS.
 * ```
 *
 * Help (RU):
 * ```
 * Usage: guess [OPTION...]
 * Игра, где компьютер угадывает число,
 * загаданное игроком.
 *
 *   -r, --roman                Использовать римские
 *                              цифры
 *   -?, --help                 Give this help list
 *       --usage                Give a short usage message
 *   -V, --version              Print program version
 *
 * Report bugs to BUG-REPORT-ADDRESS.
 * ```
 */

/** @page guessing-game-desc
 * 
 * In this game a player picks a number and the computer guesses it.
 * The computer asks several questions like "Is the number more than X?" and
 * narrows the search interval down until only one number fits the player's
 * answers.
 * 
 * Numbers can be displayed as roman numerals if `-r` is passed to the
 * game's executable.
 */

/** @file guess.c
 * 
 * Guessing game's main logic.
 * 
 */

const char *argp_program_version =
  PACKAGE_STRING;
const char *argp_program_bug_address =
  PACKAGE_BUGREPORT;

/// Program documentation.
static char doc[] =
    N_("A game where the computer guesses the number picked by the player.");

/// Command line options.
static struct argp_option options[] = {
    {"roman", 'r', 0, 0, N_("Use roman numerals")},
    { 0 }
};

/// Used by main to communicate with parse_opt.
struct arguments {
    int use_roman;
};

/** Parse single command line option.
 * 
 * @param key Option to process.
 * @param arg Unused.
 * @param state Program state that is configured via command line.
 */
static error_t parse_opt(int key, char* arg, struct argp_state* state) {
    struct arguments* arguments = state->input;

    switch (key) {
    case 'r':
        arguments->use_roman = 1;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

/// Info about the argp parser.
static struct argp argp = { options, parse_opt, NULL, doc };

/** Convert integer number to roman numeral.
 * 
 * @param x Number to convert.
 */
char* to_roman(unsigned x) {
    return roman_table[x-1];
}

/** Convert roman numeral to integer number.
 *
 * @param r Roman numeral to convert.
 */
unsigned from_roman(char *r) {
    for (unsigned i = 1; i < MAXNUM + 1; ++i) {
        if (strncmp(r, roman_table[i-1], MAX_ROMAN_LEN + 1)) {
            return i;
        }
    }
}

/// Main loop of the game.
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    struct arguments arguments;

    /* Default values. */
    arguments.use_roman = 0;

    /* Parse command line args. */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (arguments.use_roman) {
        printf(_("Think of a number no less than I and no more than %.*s.\n"),
            MAX_ROMAN_LEN,
            to_roman(MAXNUM)
        );
    } else {
        printf(_("Think of a number no less than 1 and no more than %u.\n"),
            MAXNUM
        );
    }

    char* user_input = NULL;
    size_t user_input_len = 0;
    unsigned l = 1;
    unsigned r = MAXNUM;
    while (l != r) {
        if (arguments.use_roman) {
            printf(_("Is the number more than %.*s?"),
                MAX_ROMAN_LEN,
                to_roman((r + l) / 2)
            );
        } else {
            printf(_("Is the number more than %u?"), (r + l) / 2);
        }

        getline(&user_input, &user_input_len, stdin);

        if (!strncmp(user_input, _("y\n"), 2)) {
            l = (r + l) / 2 + 1;
        } else {
            r = (r + l) / 2;
        }
    }

    if (arguments.use_roman) {
        printf(_("The number must be %.*s\n"),
            MAX_ROMAN_LEN,
            to_roman((r + l) / 2)
        );
    } else {
        printf(_("The number must be %u\n"), (r + l) / 2);
    }

    return 0;
}