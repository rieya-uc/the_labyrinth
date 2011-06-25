/*
 * Exercise 5.2
 *
 * Write getfloat, the floating-point analog of getint. What type does 
 * getfloat return as its function value?
 *
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getint(int*);
int getfloat(float*);
int getch(void);
void ungetch(int);

int main()
{
    float *fn;
    int i;
            
    while(*fn != EOF) {
        i = getfloat(fn);
        printf("%g\n",*fn);
    }
}

/* getfloat: get next digit from input into *fn */
/* similar to getint, but with added decimal points */
int getfloat(float *fn)
{
    int c, sign, exp = 1;

    while (isspace(c = getch()))    /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c !='+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for(*fn = 0; isdigit(c); c = getch())
        *fn = 10 * *fn + (c - '0');
    if (c == '.') {         /* convert decimal part - Ex 5.2 */
        c = getch();
        for(*fn; isdigit(c); c = getch()) {
            *fn = 10 * *fn + (c - '0');
            exp *= 10;
        }
    }
    *fn *= sign;
    *fn /= exp;
    
    return c;
}
 
/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))    /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);     /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
     if (c != EOF)
        ungetch(c);
     return c;
}

int getch(void)    
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
    
