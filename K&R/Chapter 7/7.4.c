/*
 * Exercise 7.4
 *
 * Write a private version of scanf analogous to minprint from 
 * the previous exercise.
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

void minscanf(char *fmt, ...);

int main()
{
    int i,j;
    float f;
    char s[MAXWORD];


    printf("Enter an int and a float\n");
    printf("> ");
    minscanf("%i %f",&i, &f);
    printf("You entered: %i and %f\n",i,f);
    
    printf("\nEnter a string\n");
    printf(">");
    minscanf("%3s",s);
    printf("The first 3 letters are %s\n",s);


}

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, type;
    char *cval;
    int *ival;
    float *dval;
    unsigned *uval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        char word[MAXWORD];
        int len = MAXWORD;
        int i;
       
        while(*p++ != '%') {
            if (*p == EOF || *p == '\n' || *p == '\0')
                return;
            //else
            //    p++;
        }
//
        /* get max number of chars to read from user */
        if (isdigit(*p)) {
            i = 0;
            while(isdigit(word[i++] = *p++))
                ;
            word[i] = '\0';
            len = atoi(word);
            p--;
        }
        
        /* get the datatype */
        type = *p;

        /* get userinput */
        for (i = 0; i < len; i++) {
            if (isspace(word[i] = getchar()))
                break;
        }
        word[i] = '\0';

        /* assign to the correct type */
        switch(type) {
            case 'i':
            case 'd':
                ival = va_arg(ap, int *);
                *ival = atoi(word);
                break;
            case 'f':
            case 'g':
                dval = va_arg(ap, float *);
                *dval = atof(word);
                break;
            case 's':
                sval = va_arg(ap, char *);
                strcpy(sval, word);
                break;
            case 'u':
                uval = va_arg(ap, unsigned *);
                *uval = atoi(word);
                break;
            case 'c':
                cval = va_arg(ap, char *);
                *cval = word[0];
                break;
        }  
    }
    va_end(ap);
}
