/* 
 * Exercise 1.9
 *
 * Write a program to copy its input to its output, replacing each 
 * string of one or more blanks by a single blank.
 *
 */

#include <stdio.h>

main()
{
    int pc = -1;
    int c;

    while((c = getchar()) != EOF) {
        if (pc == ' ' && c == ' ')
            ;   // don't copy to output
        else {
            putchar(c);
            pc = c;
        }
    }
}
