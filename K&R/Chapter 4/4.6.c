/*
 *
 * Exercise 4.6
 * Add commands for handling variables. (It's easy to provide 
 * twenty-six variables with single-letter names.) Add a variable 
 * for the most recently printed value.
 *
 */

#include <stdio.h>
#include <stdlib.h>     /* for atof() */
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER  '0'     /* signal that a number was found */
#define MAXVAL  100     /* maximum depth of val stack */
#define BUFSIZE 100
#define INIT 1
#define UNINIT 0
#define COMMAND 1       
#define VARIABLE 2

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */
double var[26];         /* variables for ex 4.6 */
int vinit[26];          /* which vars hold a value */
int vdx = -1;           /* index of next variable to be assigned */
double last;            /* Ex 4.6 - the most recent printed variable */

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

    
    int i;
    for (i = 0; i < 27; ++i)
        vinit[i] = UNINIT;

    while ((type = getop(s)) != EOF) {
        switch (type) {
            printf("er%s\n",s);
            case NUMBER:
                push(atof(s));
                break;
            case COMMAND:       /* For Ex 4.5 - other maths functions */
                parseCommand(s);
                break;
            case VARIABLE:      /* Ex 4.6 - handling variables */
                vdx = tolower(s[0]) - 'a';
                if (vinit[vdx] == INIT) {
                    push(var[vdx]);
                }
                break;
            case '=':
                if (vdx == -1)
                    printf("error: no variable to assign to\n");
                else if (sp == 0)
                    printf("error: no value specified for variable\n");
                else {
                    var[vdx] = pop();
                    vinit[vdx] = INIT;
                }
                break;
            case '+':
                push(pop() + pop());
                printf("\t%.8g\n", pop());
                break;
            case '*':
                push(pop() - op2);
                printf("\t%.8g\n", pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                printf("\t%.8g\n", pop());
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                    printf("\t%.8g\n", pop());
                }
                else
                    printf("error: zero divisor\n");
                break;
            case '%':           /* Exercise 4.3 - modulus operator */
                op2 = pop();
                if (op2 != 0.0) {
                    push(fmod(pop(),op2));
                    printf("\t%.8g\n", pop());
                }
                else
                    printf("error: zero modulus\n");

                break;
            case '\n':
               // printtop();
               // printf("\t%.8g\n", pop());
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
    if (sp > 0) {
        last = val[--sp];
        return val[sp];
    }
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
    if (isalpha(c)) {       /* For exercise 4.5 */
        while(isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);

        if (s[1] == '\0')
            return VARIABLE;
        else
            return COMMAND;
    }

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

/* Exercise 4-4 */
void printtop(void)
{
    double t1;

    if (sp == 0) {
        printf("error: no items on stack\n");
    }
    else {
        t1 = val[sp - 1];
        printf("\t%.8g\n",t1);
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

void viewstack(void)
{
    int i;
    if (sp <= 0)
        printf("\tempty stack\n");
    else {
        printf("\t");
        for (i = 0; i < sp; ++i)
            printf("%g ",val[i]);
        printf("\n");
    }
}

void viewvars(void)
{
    int i;
    
    for (i = 0; i < 26; ++i) {
        printf("%g ", var[i]);
    }
    printf("\n");
}
    

/* Exercise 4.5 - other mathematical functions
 * I could add more functions, but you get the idea */
void parseCommand(char s[])
{
    double t;
    
    /* Commands for ex 4.4 - stack commands */
    if (0 == strcmp(s,"view"))
        printtop();     /* view top element on stack */
    else if (0 == strcmp(s, "duplicate"))
        duplicate();    /* duplicate top element on stack */
    else if (0 == strcmp(s, "swap"))
        swap();         /* swap top two elements on stack */
    else if (0 == strcmp(s, "clear"))
        clear();        /* clear stack */

    /* Commands for 4.5 - maths functions */
    else if (0 == strcmp(s,"sin")) 
        push(sin(pop()));
    else if (0 == strcmp(s,"exp")) 
        push(exp(pop()));
    else if (0 == strcmp(s,"pow")) {
        t = pop();
        push(pow(pop(),t));
    }

    /* misc functions */
    else if (0 == strcmp(s, "stack"))
        viewstack();
    else if (0 == strcmp(s, "vars"))
        viewvars();
    else
        printf("error: not a valid command\n");
}
        


