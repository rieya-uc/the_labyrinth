/*
 * Exercise 2.1
 *
 * Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing 
 * appropriate values from standard headers and by direct computation.
 * Harder if you compute them: determine the ranges of the various 
 * floating-point types.
 *
 */
 
#include <stdio.h>
#include <limits.h>
#include <float.h>

main()
{
    printf("Char\n   Signed:   %d - %d\n   Unsigned: %4d - %d\n\n", 
            CHAR_MIN,CHAR_MAX,0,UCHAR_MAX, CHAR_BIT);
    printf("Short\n  Signed:   %d - %d\n  Unsigned: %6d - %u\n\n",
            SHRT_MIN,SHRT_MAX,0,USHRT_MAX);
    printf("Int\n  Signed:   %d - %d\n  Unsigned: %11d - %u\n\n",
            INT_MIN,INT_MAX,0,UINT_MAX);
    printf("Long\n  Signed:   %ld - %ld\n  Unsigned: %11d - %ul\n\n",
            LONG_MIN,LONG_MAX,0,ULONG_MAX);
    
    
}
