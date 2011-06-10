/*
 * Exercise 2.9
 *
 * In a two's complement number system, x &= (x-1) deletes the 
 * rightmost 1-bit in x. Explain why. Use this observation to 
 * write a faster version of bitcount.
 *
 */

#include <stdio.h>

int old_bitcount(unsigned x);
int bitcount(unsigned x);

main() 
{
    printf("%d\n", old_bitcount(28));
    printf("%d\n", bitcount(28));
}

int bitcount(unsigned x)
{
    int i;
    for (i = 0; x != 0; ++i)
        x &= (x-1);

    return i;
}

/* bitcount: count 1 bits in x */
int old_bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1) {
        if (x & 01)
            b++;
    }
    return b;
    
}


