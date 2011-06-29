/* 
 * Exercise 5.13
 *
 * Write the program tail, which prints the last n lines of its input.
 * By default, n is 10, let us say, but it can by changed by an 
 * optional argument, so that
 *          tail -n
 * prints the last n lines. The program should behave rationally no 
 * matter how unreasonable the input or the value of n. Write the program 
 * so it makes the best use of available storage; lines should be stored 
 * as in the sorting program of Section 5.6, not in a two dimensional array 
 * of fixed size.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCSIZE 10000     /* size of available space */
#define MAXLINES 1000
#define MAXLEN  1000        /* max length of any input line */

int getline(char *);
char *alloc(int);
void tail(char*[], int);

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

int main(int argc, char* argv[])
{
    char *lineptr[MAXLINES];
    char s[MAXLEN];
    int len, nlines=0;
    int last = 10;

    /* check arguments are correct */
    if (argc > 1 && (strcmp(argv[1],"-n") || argc < 3)) {
        printf("Usage: filename -n int\n");
        printf("Setting n to 10\n");
    }
    else {
        while(*++argv[2] == '-')  /* negative numbers treated as positive */
            ;
        if (isdigit(*argv[2]))    /* ignore non-digit values */
            last = atoi(argv[2]);
        else
            printf("Invalid value, setting n to 10\n");
    }

    /* read in lines */
    while((len = getline(s)) > 0 && nlines < MAXLINES) {
        lineptr[nlines] = alloc(len+1);
        strcpy(lineptr[nlines],s);
        nlines++;
    }
    lineptr[nlines] = alloc(1);
    *lineptr[nlines] = '\0';    /* end of lines list */

    tail(lineptr, last);
}

/* tail: takes in a list of strings, and prints out the last n lines */
void tail(char *lineptr[], int last)
{
    int nlines, start;
    for(nlines=0; *lineptr[nlines] != '\0'; ++nlines)
        ;  /* count the number of lines in array */
    
    /* check there's enough lines in array */
    start = (nlines > last) ? (nlines-last) : 0;

    /* move to correct position and start printing from there */
    int i;
    for(i=start;*lineptr[i] != '\0'; ++i)
        printf("%s\n",lineptr[i]);

}

/* getline: reads a string into s and returns its length */
int getline(char *s)
{
    int i = 0;
    while ((*s++ = getchar()) != '\n')
        ++i;
    *--s = '\0';    // remove 'enter' char 
    return i;
}

char *alloc(int n)  /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {   /* it fits */
        allocp += n;
        return allocp - n;   /* old p */
    } else      /* not enough room */
        return 0;
}
