/*
 * ps_input.c - Source file containing helper functions; to make things
 *              easier (eg: get a string, integer, float, etc.).
 *
 * Author: Philip R. Simonson
 * Date  : 05/28/2021
 *
 ****************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ps_input.h"

static string _ps_help_string;

/* Get an entire string from the user displaying a prompt.
 */
string get_string(const char* message)
{
    string output;
    int c, i, size;

    // Make the initial allocation
    size = 2;
    errno = 0;
    output = malloc(sizeof(char) * size);
    if(output == NULL) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return NULL;
    }
    _ps_help_string = output;

    // Print message and get string from user
    printf("%s", message);
    for(i = 0; (c = fgetc(stdin)) != EOF && c != '\n'; i++) {
        if(i >= size) {
            string tmp;

            // Reset errno and increment size and reallocate
            errno = 0;
            size += 2;
            tmp = realloc(output, sizeof(char) * size);
            if(tmp == NULL) {
                fprintf(stderr, "Error: %s\n", strerror(errno));
                free(output);
                return NULL;
            }
            output = tmp;
        }

        // Now store character inside buffer
        *(output+i) = c;
    }

    // Null terminate string and return it
    *(output+i) = 0;
    return output;
}
/* Get integer value.
 */
int get_integer(const char *message)
{
    int value;
    string input = get_string(message);
    if(input == NULL) return 0;
    value = atoi(input);
    free(input);
    _ps_help_string = NULL;
    return value;
}
/* Get long value.
 */
long get_long(const char* message)
{
    long value;
    string input = get_string(message);
    if(input == NULL) return 0;
    value = atol(input);
    free(input);
    _ps_help_string = NULL;
    return value;
}
/* Get floating point (real) number.
 */
float get_float(const char *message)
{
    float value;
    string input = get_string(message);
    if(input == NULL) return 0;
    value = atof(input);
    free(input);
    _ps_help_string = NULL;
    return value;
}
/* Get long floating point (real) number.
 */
double get_double(const char *message)
{
    double value;
    string input = get_string(message);
    if(input == NULL) return 0;
    value = atof(input);
    free(input);
    _ps_help_string = NULL;
    return value;
}
