/*
 * Exercise 7.2
 *
 * Write a program that will print arbitrary input in a sensible way.
 * As a minimum, it should print non-graphic characters in octal or
 * hexadecimal according to local custom, and break long text lines.
 *
 */

#include <stdio.h>

#define MAXLINE 70

int main()
{
    int len = 0;
    char c;
    while ((c = getchar()) != EOF) {
        if (isalnum(c) || ispunct(c)) {
            putchar(c);
            len++;
        }
        else if (c == '\n') {
            printf("%x\n", c);
            len = 0;
        }
        else {
            printf("0X%x", c);
            len += 3;
        }

        if (len >= MAXLINE) {
            printf("\n");
            len = 0;
        }
    }
}

