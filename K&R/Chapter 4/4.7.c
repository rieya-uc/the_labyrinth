/*
 * Exercise 4.7
 *
 * Write a routine ungets(s) that will push back an entire string 
 * onto the input. Should ungets know about buf and bufp, or should 
 * it just use ungetch?
 *
 */

#include <stdio.h>
#include <stdlib.h>     /* for atof() */
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP   100     /* max size of operand or operator */
#define MAXVAL  100     /* maximum depth of val stack */
#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getch(void);
void ungetch(int);
void ungets(char[]);
    
/* reverse Polish calculator */
main()
{
    char s[] = "string to push onto input\n";
    
    ungets(s);
    printf("%s", s);
}

int getch(void)     /* push character back on input */
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

/* Exercise 4.7 - push a string back onto input
 * Not quite sure what it's asking for... */
void ungets(char s[]) {
    int i;
    for(i = 0; s[i] != '\0'; ++i)
        ungetch(s[i]);

    /* Is that it? Surely there must be more to it? */
}

