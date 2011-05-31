/* 
 * Exercise 1.12
 *
 * Write a program that prints its input one word per line.
 *
 */

#include <stdio.h>

#define TRUE      1  
#define FALSE     0  

int main()
{
    int c, printline = TRUE;

    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\t' && c != '\n') {
            putchar(c);
            printline = TRUE;
        }
        else if (printline) {     // don't want to print multiple blank lines
            printf("\n");
            printline = FALSE;
        }
    }
}


