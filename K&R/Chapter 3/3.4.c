/* 
 * Exercise 3.4
 *
 * In a two's complement number representation, our version of 
 * itoa does not handle the largest negative number, that is, 
 * the value of n equal to -(2^wordsize-1). Explain why not. 
 * Modify it to print that value correctly, regardless of the 
 * machine on which it runs.
 *
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAXLINE 1000

void itoa2(int n, char s[]);
void reverse(char s[]);

int main()
{
    int n = INT_MIN;
    char s[MAXLINE];
    printf("%i\n",n);
    itoa2(n,s);
    printf("%s\n",s);


}

/* itoa: convert n to characters in s */
void itoa2(int n, char s[])
{
    int i, sign;

    
    //if ((sign = n) < 0)     /* record sign */
    //    n = -n;             /* make n positive */

    sign = (n < 0) ? -1 : 1;
    
    /* just needed to use absolute values to get it to work right */
    i = 0;
    do {        /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0';  /* get next digit */
    } while (abs(n /= 10) > 0);      /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


