/** @file roman.h
 *
 * Roman conversion functions for the guessing game.
 *
 */

#ifndef ROMAN_H
#define ROMAN_H

/** Convert integer number to roman numeral.
 *
 * @param x Number to convert.
 */
char* to_roman(unsigned x);

/** Convert roman numeral to integer number.
 *
 * @param r Roman numeral to convert.
 */
unsigned from_roman(char *r);

#endif // ROMAN_H
