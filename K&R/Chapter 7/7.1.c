/*
 * Exercise 7.1
 *
 * Write a program that converts upper case to lower or lower case to 
 * upper, depending on the name it is invoked with, as found in argv[0].
 *
 * NB:
 * Don't forget to compile it using upper.* or lower.* as the filename!
 *
 */

#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    char c;
    if (strncmp("lower", argv[0], 5) == 0) {
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    }
    else if (strncmp("upper", argv[0], 5) == 0) {
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    }

}
