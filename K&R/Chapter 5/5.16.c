/*
 * Exercise 5.16
 *
 * Add the -d ("directory order") option, which makes comparisons only 
 * on letters, numbers and blanks. Make sure it works in conjunction 
 * with -f.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000   /* max #lines to be sorted */
#define MAXLEN 1000
#define ALLOCSIZE 10000

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort2(void *lineptr[], int left, int right, int reverse, int dir,
        int(*comp)(void *, void *, int));
int numcmp(char *, char *, int);
char *alloc(int);
int getline(char *, int);
int strcmpf(char *, char *, int);
int strcmpx(char *, char *, int);

char *lineptr[MAXLINES];    /* pointers to text lines */
static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;
    int reverse = 0;
    int fold = 0;
    int dirord = 0;

    int (*comp)(void*,void*, int);  /* pointer to compare function */

    /* work out which flags are present */
    while(argc-- > 0) {
       if (strcmp(argv[argc], "-n") == 0)
           numeric = 1;
       else if (strcmp(argv[argc], "-r") == 0)
           reverse = 1;
       else if (strcmp(argv[argc], "-f") == 0)
           fold = 1;
       else if (strcmp(argv[argc], "-d") == 0)
           dirord = 1;
    }

    /* work out which compare function to use */
    if (numeric)
        comp = numcmp;
    else if (fold)
        comp = strcmpf; /* strcmp converting all letters to lower case */
    else
        comp = strcmpx;  /* strcmp, no converting */                                

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort2((void **) lineptr, 0, nlines-1, reverse, dirord, comp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort2(void *v[], int left, int right, int reverse, int dir,
        int (*comp)(void *, void *, int))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)  /* do nothing if array contains */
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;

    if (reverse) {
        for (i = left+1; i <= right; i++)
            if ((*comp)(v[i], v[left], dir) > 0)
                swap(v, ++last, i);
    }
    else {
        for (i = left+1; i <= right; i++)
            if ((*comp)(v[i], v[left], dir) < 0)
                swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort2(v, left, last-1, reverse, dir, comp);
    qsort2(v, last+1, right, reverse, dir, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2, int dir)
{

    double v1, v2;

    if (dir && (!isalnum(*s1) || *s1 != ' ' ||
                !isalnum(*s2) || *s2 != ' '))
        return 0;   /* don't do any comparisions */

    v1 = atof(s1);
    v2 = atof(s2);
    
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* strcmpf: compares s1 and s2 alphabetically, converts upper case to lower */
int strcmpf(char *s1, char *s2, int dir)
{
    int c1, c2;
    
    if (dir && (!isalnum(*s1) || *s1 != ' ' ||
                !isalnum(*s2) || *s2 != ' '))
        return 0;   /* don't do any comparisions */
    
    c1 = tolower(*s1);
    c2 = tolower(*s2);

    if (c1 < c2)
        return -1;
    else if (c1 > c2)
        return 1;
    else return 0;
}

/* strcmpf: compares s1 and s2 alphabetically, minding upper and lower case */
int strcmpx(char *s1, char *s2, int dir)
{
    int c1, c2;
    
    if (dir && (!isalnum(*s1) || *s1 != ' ' ||
                !isalnum(*s2) || *s2 != ' '))
        return 0;   /* don't do any comparisions */
    
    c1 = *s1;
    c2 = *s2;

    if (c1 < c2)
        return -1;
    else if (c1 > c2)
        return 1;
    else return 0;
}


void swap(void *v[], int i,  int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0';    /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n",lineptr[i]);
}

/* getline: reads a string into s and returns its length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* alloc: return pointer to n characters */
char *alloc(int n)
{
    if (allocbuf +ALLOCSIZE - allocp >= n) {    /* it fits */
        allocp += n;
        return allocp - n;  /* old p */
    } else      /* not enough room */
        return 0;
}

