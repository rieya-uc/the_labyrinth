/*
 * Exercise 4.2
 *
 * Extend atof to handle scientific notation of the form
 *      123.45e-6
 * where a floating-point number may be followed by e or E 
 * and an optionally signed exponent.
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINE 1000

double atof2 (char s[]);
int getline(char line[], int max);
int atoi2(char s[]);

main()
{

    char line[MAXLINE];

    printf("Type in a value of the form 123.45e-6\n");
    /* checking my version of atof matches up with <stdio.h>'s version */
    while (getline(line, MAXLINE) > 0) {
        printf("\t%g\n", atof2(line));  /* my atof */
        printf("\t%g\n", atof(line));   /* c's atof */
    }
    return 0;
}

/* atof: convert string s to double */
double atof2(char s[])
{
    double val, power, total, exp;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)     /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    total = sign * val/power;

    /* work out value of the exponent and move the decimal 
     * point accordingly */

    if (s[i] == 'e' || s[i] == 'E') {
        exp = 0;
        power = 1;
        i++;
        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        while (isdigit(s[i])) {
            exp = 10 * exp + (s[i] - '0');
            i++;
        }
        for(i = 0; i < exp; ++i)
            power *= 10;
        if (sign == -1)
            total /= power;
        else
            total *= power;
    }

    return total;
}

/* atoi: convert string s to integer using atof */
int atoi2(char s[])
{
    //double atof(char s[]);
    return (int)atof2(s);
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
    int c,i;

    i = 0;
    while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

