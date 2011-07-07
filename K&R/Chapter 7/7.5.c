/*
 * Exercise 7.5
 *
 * Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf 
 * to do the input and number conversion.
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

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */


int getop(char []);
void push(double);
double pop(void);
int getline(char s[], int lim);

/* reverse Polish calculator */
main()
{
    int type = 0;
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
            case '\0':
                
                break;
            case EOF:
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }

        if (!isdigit(type)) {
            float f = pop();
            printf("\t%.8g\n", f);
            push(f);
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
    s[0] = '\0';;
    char user[1000];
    scanf("%s", s);

    if (isdigit(s[0]))
        return NUMBER;
    else
        return s[0];

}

