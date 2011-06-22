/*
 * Exercise 4.12
 * 
 * Adapt the ideas of printd to write a recursive version of itoa; 
 * that is, convert an integer into a string by calling a recursive 
 * routine.
 *
 */

#include <stdio.h>
#include <stdlib.h>

int itoa_r(int n, char s[]);
void printd(int n);

int main()
{
    int x = 3012;
    char s[1000];
    itoa_r(3041,s);
    printf("%s\n",s);
    itoa_r(-1284,s);
    printf("%s\n",s);

    return 0;
}

/* recursive version of itoa */
int itoa_r(int n, char s[])
{
    int i = 0;
    if (n < 0)
        s[i++] = '-';
    if (n / 10) {
        i = itoa_r(n/10, s);
    }
    
    s[i++] = (abs(n) % 10 + '0');
    s[i] = '\0';

    return i;
}

/* printd: print n in decimal */
void printd(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10) {
        printd(n / 10);
    }
    putchar(n % 10 + '0');
}



