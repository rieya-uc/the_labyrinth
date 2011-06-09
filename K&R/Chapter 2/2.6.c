/*
 * Exercise 2.6
 *
 * Write a function setbits(x,p,n,y) that returns x with the n 
 * bits that begin at position p set to the rightmost n bits of 
 * y, leaving the other bits unchanged.
 *
 */

#include <stdio.h>

void pbin(unsigned int dec, int padding);
unsigned getbits(unsigned x, int p, int n);
int setbits(unsigned x, int p, int n, int y);

main()
{
    int x = 123;
    pbin(setbits(x,5,3,3),0);
}

int setbits(unsigned x, int p, int n, int y)
{
    int mask, replace;
    /* get the bits we're using to replace p+n
     * shift the bits left so they occupy the same position as p+n
     */
    replace = getbits(x,y,n) << p+1-n;

    /* Shift to left of p, shift right by n and fill those bits with 0,
     * shift again so everything back to original position, with 1 
     * filling in the shifted bits.
     * e.g. if x is 010,ppp,101 we end up with 010,000,111.
     */
    mask = ~(~((x >> p+1) << n) << p+1-n);

    /* I'm sure there's a less convoluted way of doing this */ 
    return (x & mask) | replace;


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
            
