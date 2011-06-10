/*
 * Exercise 2.8
 *
 * Write a function rightrot(x,n) that returns the value of the integer 
 * x rotated to the right by n positions.
 *
 */

#include <stdio.h>
#include <limits.h>

void pbin(unsigned int dec, int padding);
unsigned rightrot(unsigned x, int n);


main()
{
    int x = 253;
    pbin(x,0);
    pbin(rightrot(x, 3),0);
}

unsigned rightrot(unsigned x, int n)
{
    int i;
    for (i = n; i > 0; --i) {
        if (x & 1)
            x = (x >> 1) | (1 << (sizeof(x)*CHAR_BIT) - 1) ;
        else
            x = x >> 1;
    }
    return x;
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
      
