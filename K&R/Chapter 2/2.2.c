/*
 * Exercise 2.2
 *
 * Write a loop equivalent to the for loop above without using 
 * && or ||.
 *
 * NB: for-loop referred to:
 *     for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 *         s[i] = c;
 *
 */

#include <stdio.h>

#define MAXLINE 1000

main()
{
    int i = 0;
    int lim = MAXLINE;
    int c;
    char s[MAXLINE-1];

    while(i < lim-1) {
        c = getchar();

        if (c == EOF)
            lim = 0;
        else if (c == '\n')
            lim = 0;
        else {
            s[i] = c;
            ++i;
        }
    }
}
