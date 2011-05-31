/* 
 * Exercise 1.14
 *
 * Write a program to print a histogram of the frequencies of different
 * characters in its input.
 *
 */

#include <stdio.h>


main()
{
    int c;
    int i, j;
    int cCount[52];  // only counting letters. Could count more if needed.

    for (i = 0; i < 52; ++i) {
        cCount[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c >= 'A' && c <= 'Z') {
            ++cCount[c-'A'];
        }
        if  (c >= 'a' && c <= 'z') {
            ++cCount[c-'G'];
        }
        putchar(c);
    }

    //display histogram
    for (i = 0; i < 26; ++i) {
        printf("%c: ", i+'A');
        for (j = 0; j < cCount[i]; ++j) {
            printf("*");
        }
        printf("\n");
    }

    for (i = 26; i < 52; ++i) {
        printf("%c: ", i+'G');
        for (j = 0; j < cCount[i]; ++j) {
            printf("*");
        }
        printf("\n");
    }
    
}


