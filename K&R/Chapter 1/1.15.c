/* 
 * Exercise 1.15
 *
 * Rewrite the temperature conversion program of Section 1.2 to 
 * use a function for conversion.
 *
 */

#include <stdio.h>

float fah_to_cel(float);

main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;
    printf("Fahrenheit    Celcius\n");
    while (fahr <= upper) {
        celsius = fah_to_cel(fahr);
        printf("%7.1f %12.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

float fah_to_cel(float fahr)
{
    return ((5.0/9.0)*(fahr-32.0));
}

