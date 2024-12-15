import roman
import sys

## @package roman_gen
#  Script that generates roman_table.h.
# 
#  The header file defines a table of roman numerals for all guessable numbers
#  as well as the length of the longest roman numeral present.

## Largest guessable number. Passed as a command line argument.
MAXNUM = int(sys.argv[-1])

## Generate header file and print it to stdout.
def print_header_file():
    print("""
/** @file roman_table.h
 * Header file for roman numeral support in the guessing game.
 */
""")

    table = []
    maxlen = 0
    for i in range(1, MAXNUM + 1):
        r = roman.toRoman(i)
        table.append(r)

        if len(r) > maxlen:
            maxlen = len(r)

    print("""
/// Table of roman numerals for all guessable numbers.""")

    print("static char* roman_table[] = {")
    for i, r in enumerate(table):
        if i != len(table) - 1:
            print("    \"{}\",".format(r))
        else:
            print("    \"{}\"".format(r))
    print("};")

    print(f"""
/// Length of the longest roman numeral present.
#define MAX_ROMAN_LEN {maxlen}""")


if __name__ == '__main__':
    print_header_file()
