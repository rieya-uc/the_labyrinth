/*
 * Exercise 5.14
 *
 * Modify the sort program to handle a -r flag, which indicates 
 * sorting in reverse (decreasing) order. Be sure that -r works 
 * with -n.
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
void qsort2(void *lineptr[], int left, int right, int reverse,
        int(*comp)(void *, void *));
int numcmp(char *, char *);
char *alloc(int);
int getline(char *, int);

char *lineptr[MAXLINES];    /* pointers to text lines */
static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;
    int reverse = 0;

    while(argc-- > 0) {
       if (strcmp(argv[argc], "-n") == 0)
           numeric = 1;
       else if (strcmp(argv[argc], "-r") == 0)
           reverse = 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort2((void **) lineptr, 0, nlines-1, reverse,
                (int (*)(void*,void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort2(void *v[], int left, int right, int reverse,
        int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)  /* do nothing if array contains */
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    if (reverse) {
        for (i = left+1; i <= right; i++)
            if ((*comp)(v[i], v[left]) > 0)
                swap(v, ++last, i);
    }
    else {
        for (i = left+1; i <= right; i++)
            if ((*comp)(v[i], v[left]) < 0)
                swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort2(v, left, last-1, reverse, comp);
    qsort2(v, last+1, right, reverse, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
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
