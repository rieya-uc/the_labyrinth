/*
 * Exercise 7.3
 *
 * Revise minprintf to handle more of the other facilities of printf.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

struct widthfield;
void minprintf(char *fmt, ...);
char parsefield(char *, struct widthfield *);

enum ALIGN {left, right, none};

struct widthfield {
    char pdg;     /* what we use to pad out extra spaces */
    enum ALIGN al;  /* left, right or none */
    int min;      /* minimum number of chars to display, or -1 for no min */
    int max;      /* max number of chars to display, or -1 for no max */
};

int main()
{
    char s[] = "hello, world";

    printf("******Strings******\n");
    minprintf(":%15s:\n",s);
    minprintf(":%-15s:\n",s);
    minprintf(":%.10s:\n",s);
    minprintf(":%15.10s:\n",s);
    minprintf("m:%-15.10s:\n",s);
    printf("\n\n");
  
    int i = 12345; 
    printf("******Ints******\n");
    minprintf(":%8i:\n",i);
    minprintf(":%-8i:\n",i);
    minprintf(":%.8i:\n",i);
    minprintf(":%8.3i:\n",i);
    printf("\n\n");


    float f = 123.456;
    printf("******Floats******\n");
    minprintf(":%.2f:\n",f);
    minprintf(":%.10f:\n",f);

}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;     /* points to each unnamed arg in turn */
    char *p, *sval;
    char cval;
    int ival;
    double dval;
    unsigned uval;
    char line[1000];
    char field[50];
    char c;
    struct widthfield *wfset = malloc(sizeof(struct widthfield));

    va_start(ap, fmt);      /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        /* collect width field */
        int i = 0;
        while(!isalpha(field[i++] = *++p)) 
            ;
        field[i] = '\0';

        /* get width format settings */
        c = parsefield(field, wfset);

        switch (c) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int);
                sprintf(line, "%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                sprintf(line, "%f", dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                strcpy(line, sval);
                break;
            case 'o':
                ival = va_arg(ap, int);
                sprintf(line, "%o", ival);
                break;
            case 'x':
            case 'X':
                ival = va_arg(ap, int);
                sprintf(line, "%x", ival);
                break;
            case 'u':
                uval = va_arg(ap, unsigned);
                sprintf(line, "%u", uval);
            case 'c':
                ival = va_arg(ap, int);
                sprintf(line, "%c", ival);
                break;
            default:
                putchar(*p);
                break;
        }
     
        int llen = strlen(line);
        
        if (c == 'f') { /* floats act on precision only */
            int i = 0;
            while (line[i++] != '.')
                ;
            
            if ((llen-i) > wfset->max)
                wfset->max = i+wfset->max;
            else
                llen -= i;
        }

        if (wfset->max != -1 && llen > wfset->max) {
            line[wfset->max] = '\0';
            llen = wfset->max;
        }
       
        if (wfset->al == right) {
            int i;
            for (i = llen; i < wfset->min; ++i)
                printf("%c",wfset->pdg);
            printf("%s",line);
        }

        else if (wfset->al == left) {
            int i;
            printf("%s",line);
            for (i = llen; i < wfset->min; ++i)
                printf("%c", wfset->pdg);
        }
    }
    va_end(ap);     /* clean up when done */
    free(wfset);
}

char parsefield(char *field, struct widthfield *wfset)
{
    char *c = field;
    char flags[50] = "";
    char prec[50] = "";
    char type;  /* int, string, etc */

    /* default settings, will return this if there are no flags
     * or there is an error in parsing */
    wfset->min = -1;
    wfset->max = -1;
    wfset->pdg = ' ';
    wfset->al = left;

    /* nothing to parse */
    if (isalpha(*c))
        return *c;
  
    /* get flags and width settings */
    int i;
    for (i = 0; !isalpha(*c) && *c != '.' && *c != EOF; i++, c++) /* goddamn c */
        flags[i] = *c;
    flags[i] = '\0';  

    /* get precision settings */
    if (*c == '.') {
        c++;
        for (i = 0; isdigit(*c) && *c != EOF; i++, c++)
            prec[i] = *c;
        prec[i] = '\0';
    }

    type = *c;

    if (strcmp(flags,"") != 0) {
        if ((flags[0]) == '-') {
           char *s = &flags[1];
           wfset->min = atoi(s);
           wfset->al = left;
       }
       else if (isdigit(flags[0])) {
            wfset->min = atoi(flags);
            wfset->al = right;
       }
    }

    if (strcmp(prec,"") != 0) {
        if (type == 's')
            wfset->max = atoi(prec);
        else if (type == 'f') {
            wfset->min = atoi(prec);
            wfset->al = left;
            wfset->pdg = '0';
        }
        else if (atoi(prec) > wfset->min) {
            wfset->pdg = '0';
            wfset->al = right;
            wfset->min = atoi(prec);
        }
    }

    if (type == 'f') {
        int len = (wfset->max < wfset->min) ? wfset->min : wfset->max;
        wfset->min = wfset->max = len;
    }

    return type;
        
}

