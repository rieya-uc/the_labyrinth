/*
 * Exercise 4.3
 * Given the basic framework, it's straightforward to extend the calculator.
 * Add the modulus (%) operator and provisions for negative numbers.
 *
 * Exercise 4.4
 * Add commands to print the top element of the stack without popping, 
 * to duplicate it, and to swap the top two elements. Add a command to 
 * clear the stack.
 *
 * Exercise 4.5
 * Add access to library functions like sin, exp, and pow.
 * See <math.h> in Appendix B, Section 4.
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
#define COMMAND 1       

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);
void printtop(void);
void duplicate(void);
void swap(void);
void clear(void);
void parseCommand(char s[]);
    
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
            case COMMAND:       /* For Ex 4.5 - other maths functions */
                parseCommand(s);
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
            case '%':           /* Exercise 4.3 - modulus operator */
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(),op2));
                else
                    printf("error: zero modulus\n");
                break;
            case '!':        /* Exercise 4.4 - view top element on stack */
                printtop();
                break;
            case 'd':        /* Ex 4.4 - duplicate top element on stack */
                duplicate();
                break;
            case 's':       /* Ex 4.4 - swap top two elements on stack */
                swap();
                break;
            case 'c':       /* Ex 4.4 - clear stack */
                clear();
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
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;
    if (isalpha(c))      /* For exercise 4.5 */
        while(isalpha(s[++i] = c = getch()))
            ;
    //i = 0;
    if (!isdigit(c) && c != '.' && c != '-')
        return c;    /* not a number */
                     /* Ex 4.3 */   
    if (c == '-') {  /* op a minus sign or negative number? */    
        c = getch();   
        if (isdigit(c) || c == '.')
            ungetch(c);
        else {
            ungetch(c);
            return '-';
        }
    }
    if (isdigit(c))     /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
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

/* Exercise 4-4 */
void printtop(void)
{
    double t1;

    if (sp == 0) {
        printf("error: no items on stack\n");
    }
    else {
        t1 = val[sp - 1];
        printf("%d\n",t1);
    }
}

void duplicate(void)
{
    if (sp > 0) {
        double temp = pop();
        push(temp);
        push(temp);
        printf("%g duplicated\n",temp);
    }
    else
        printf("error: no items on stack to duplicate\n");
}

void swap(void)
{
    if (sp > 1) {
        double t1 = pop();
        double t2 = pop();

        push(t1);
        push (t2);
        printf("%g and %g swapped\n",t1,t2);
    }
    else
        printf("error: stack empty, cannot perform swap\n");
}

void clear(void)
{
    sp = 0;
}

/* Exercise 4.5 - other mathematical functions
 * I could add more functions, but you get the idea */
void parseCommand(char s[])
{
    double t;
    
    if (0 == strcmp(s,"sin")) {
        push(sin(pop()));
    }
    else if (0 == strcmp(s,"exp")) {
        push(exp(pop()));
    }
    else if (0 == strcmp(s,"pow")) {
        t = pop();
        push(pow(pop(),t));
    }
    else {
        printf("error: not a valid function\n");
    }
}
        


