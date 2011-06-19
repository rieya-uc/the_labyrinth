/*
 * Exercise 4.10
 *
 * An alternate organization uses getline to read an entire input line; 
 * this makes getch and ungetch unnecessary. Revise the calculator to 
 * use this approach.
 *
 */

#include <stdio.h>
#include <stdlib.h>     /* for atof() */
#include <ctype.h>
#include <math.h>

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER  '0'     /* signal that a number was found */
#define MAXVAL  100     /* maximum depth of val stack */
#define BUFSIZE 100

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */
char c[1000] = "\0";    /* user input */
int ci = 0;             /* index position for user input */

int getop(char []);
void push(double);
double pop(void);
int getline(char s[], int lim);

/* reverse Polish calculator */
main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() - op2);
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
    }
    return 0;
}

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    }
    else
        printf("error: stack full, can't push %g\n",f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    //int i = 0;
    int si = 0;
    //char c[1000];

    if (c[ci] == '\0') {
        getline(c,1000);
        ci = 0;
    }

    while ((c[ci] == ' ') || (c[ci] == '\t'))
        ++ci;
    if (!isdigit(c[ci]) && (c[ci] != '.') && (c[ci] != '\0'))
        return c[ci++];        /* not a number */
    if (isdigit(c[ci])) {      /* collect integer part */
        while (isdigit(s[si++] = c[ci++]))
            s[si++] = c[ci++];
    }
    if (c[ci] == '.') {        /* collect fraction part */
        s[si++] = c[ci++];
        while (isdigit(c[ci]))
            s[si++] = c[ci++];
    }
    s[si] = '\0';

    return NUMBER;
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

        



