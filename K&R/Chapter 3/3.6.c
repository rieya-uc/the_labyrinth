/*
 * Exercise 3.6
 *
 * Write a version of itoa that accepts three arguments instead of two.
 * The third argument is a minimum field width; the converted number
 * must be padded with blanks on the left if necessary to make it wide
 * enough.
 *
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAXLINE 1000

void reverse(char s[]);
void itoaw(int n,char s[],int w);

int main()
{
    char s[MAXLINE];
    itoaw(-239,s,8);
    printf("%s\n",s);
}

/* itoa: convert n to characters in s */
void itoaw(int n, char s[], int w)
{
    int i, sign;

    sign = (n < 0) ? -1 : 1;
    i = 0;
    do {        /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0';  /* get next digit */
    } while (abs(n /= 10) > 0);      /* delete it */
 
    if (sign < 0)
        s[i++] = '-';

    while(i < w)
        s[i++] = ' ';
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


