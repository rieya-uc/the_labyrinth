/* 
 * Exercise 1.13
 *
 * Write a program to print a histogram of the lengths of words in 
 * its input. It is easy to draw the histogram with the bars horizontal; 
 * a vertical orientation is more challenging.
 *
 */

#include <stdio.h>


main()
{
    int c, i, j, nwhite, nother;
    int ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
    }
    
    // horizontal histogram
    for (i = 0; i < 10; ++i) {
        printf(" %d  ", i);
        for (j = 0; j < ndigit[i]; ++j)
            printf("*");
        printf("\n");
    }

    // vertical histogram
    int max = 0;        // largest ndigit count
    for (i = 0; i < 10; ++i) {
        if (ndigit[i] > max)
            max = ndigit[i];
    }

    printf("\n\n");

    for (i = max; i > 0; --i) {         // Can I use --i here if it's not been
        printf(" ");                    // introduced in the book?
        for (j = 0; j < 10; ++j) {     
            if (ndigit[j] >= i)
                printf("*  ");
            else
                printf("   ");
        }
        printf("\n");
    }

    for (i = 0; i < 10; ++i) {
        printf(" %d ", i);
    }
    
}
            
