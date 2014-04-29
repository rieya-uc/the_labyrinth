/* 
 * Exercise 1.13
 *
 * Write a program to print a histogram of the lengths of words in 
 * its input. It is easy to draw the histogram with the bars horizontal; 
 * a vertical orientation is more challenging.
 *
 */

#include <stdio.h>
#define MAXLEN 10

main()
{
    int c, i, j, nother;
    int ndigit[MAXLEN];

    nother = 0;
    for (i = 0; i < MAXLEN; ++i)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF && nother < MAXLEN-1)
    {
        if(c == ' ' || c == '\t' || c == '\n')
        {
            ++nother;
        }
        else
        {
            ++ndigit[nother];
        }
    }
    
    // horizontal histogram
    for (i = 0; i < nother; ++i) {
        printf(" %d  ", i);
        for (j = 0; j < ndigit[i]; ++j)
            printf("*");
        printf("\n");
    }

    // vertical histogram
    int max = 0;        // largest ndigit count
    for (i = 0; i < 10; ++i)
    {
        if (ndigit[i] > max)
            max = ndigit[i];
    }

    printf("\n\n");

    for (i = max; i > 0; --i)
    {
        max=i;

        for (j = 0; j < nother; ++j)
        {
            if (max>ndigit[j])
                printf(" ");
            else
                printf("*");
        }
        printf("\n");
    }

    for (i = 0; i < nother; ++i) {
        printf("%d", i);
    }
    printf("\n");
}
            
