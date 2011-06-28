/* 
 * Exercise 5.10
 *
 * Write the program expr, which evaluates a reverse Polish expression 
 * from the command line, where each operator or operand is a separate 
 * argument. For example,
 *              expr 2 3 4 + *
 * evaluates 2 x (3+4).
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXOP 100

int push(float n);
float pop();

float op_stack[MAXOP]; 
int op_pos = 0;

int main(int argc, char *argv[])
{
    int value = 0;

    if (argc < 3) {
        printf("Usage: filename operands operators");
        return -1;
    }
   
    int i = 0;
    
    /* this is similar to the calculator in Ch4 but using 
     * command line arguments instead */
    while(i++ < argc-1) {
        char *c = argv[i];

        if (isdigit(*c))
            push(atof(c));
        else if (c[0] == '+')
            push(pop() + pop());
        else if (c[0] == '-') {
            float op = pop();
            push(pop() - op);
        }
        /* windows cmd line won't accept "*" as an argument */
        else if (c[0] == '*' || c[0] == 'x')  
            push(pop() * pop());
        else if (c[0] == '/') {
            float op = pop();
            if (op == 0.0) {
                printf("Error: division by 0\n");
                push(op);
            }
            else
                push(pop() / op);
        }
        else
           printf("Error: nvalid argument\n");
    }
    
    printf("%g\n",pop());
    return 0;
}

int push(float n)
{
    if (op_pos < MAXOP) {
        op_stack[op_pos++] = n;
        return 0;
    }
    else { 
        printf("Error: Stack full\n");
        return -1;
    }
}
   
float pop()
{
    if (op_pos > 0)
        return (op_stack[--op_pos]);
    else {
        printf("Error: Stack empty\n");
        return -1;
    }
}

