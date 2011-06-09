/*
 * Exercise 2.7
 *
 * Write a function invert(x,p,n) that returns x with the n bits that 
 * begin at position p inverted (i.e, 1 changed into 0 and vice versa), 
 * leaving the others unchanged.
 *
 */

#include <stdio.h>

void pbin(unsigned int dec, int padding);
unsigned getbits(unsigned x, int p, int n);
unsigned invert(unsigned x, int p, int n);

main()
{
    int x = 123;
    pbin(x,0);
    pbin(invert(x,4,4),0);
}

unsigned invert(unsigned x, int p, int n)
{
    int mask;
    mask = ((1 << n)-1) << p+1-n;

    return x ^ mask;
}

/* prints binary string of a decimal */
/* no error checking for negative numbers */
void pbin(unsigned int dec, int padding)
{
    char s[1000];
    int i = 0;
    
    if (dec == 0) {
        printf("0\n");
        return;
    }

    while(dec != 0) {
        if ((dec % 2) == 0)
            s[i++] = '0';
        else
            s[i++] = '1';
        dec /= 2;
    }
    
    // add extra zeros if length of string is shorter than padding
    for (i; i < padding; ++i) {
        s[i] = '0';
    }

    for (i=i-1; i >= 0; --i) {
        printf("%c",s[i]);
        if (i % 3 == 0)
            printf(",");
    }   
    printf("\n");
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}
            
