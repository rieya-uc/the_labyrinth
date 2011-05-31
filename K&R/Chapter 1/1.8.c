/* 
 * Exercise 1.8
 *
 * Write a program to count blanks, tabs, and newlines.
 *
 */

#include <stdio.h>

main()
{
    long bc = 0, tc = 0, nlc = 0;
    int c;

    while((c = getchar()) != EOF) {
        if (c == ' ')
            ++bc;
        if (c == '\t')
            ++tc;
        if (c == '\n')
            ++nlc;
    }
    
    printf("blanks:%d, tabs:%d, newlines:%d",bc,tc,nlc);
}
