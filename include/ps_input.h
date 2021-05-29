/*
 * ps_input.h - Miscellaneous functions to receive input from a user.
 *
 * Author: Philip R. Simonson
 * Date  : 05/28/2021
 *
 ****************************************************************************
 */

#ifndef INPUT_H
#define INPUT_H

typedef char* string;

/* Get an entire string from the user displaying a prompt. */
string get_string(const char* message);
/* Get integer value. */
int get_integer(const char *message);
/* Get long value. */
long get_long(const char* message);
/* Get floating point (real) number. */
float get_float(const char *message);
/* Get long floating point (real) number. */
double get_double(const char *message);

#endif
