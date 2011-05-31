/* 
 * Exercise 1.5
 *
 * Modify the temperature conversion program to print the table in reverse
 * order, that is, from 300 degrees to 0.
 *
 */

#include <stdio.h>

#define LOWER 0          /* lower limit of temperature table */
#define UPPER 300        /* upper limit */
#define STEP  20         /* step size */

main()
{
    float fahr, celsius;

    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
        printf("%3.0f %6.1f\n", fahr, (5.0/9.0)*(fahr-32.0));
    
}
