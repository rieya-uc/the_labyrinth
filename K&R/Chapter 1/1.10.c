/* 
 * Exercise 1.10
 *
 * Write a program to copy its input to its output, replacing each tab 
 * by \t, each backspace by \b, and each backslash by \\. This makes tab 
 * and backspaces visible in an unambiguous way.
 *
 */

#include <stdio.h>

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\\\");
        else
            printf("%c", c);
    }
}


