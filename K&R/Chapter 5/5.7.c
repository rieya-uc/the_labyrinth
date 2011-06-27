/* 
 * Exercise 5.7
 *
 * Rewrite readlines to store lines in an array supplied by main, rather
 * than calling alloc to maintain storage. How much faster is the program?
 *
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000        /* max #lines to be sorted */
#define MAXLEN 1000          /* max length of any input lines */
#define ALLOCSIZE 10000      /* size of available space */

char lineptr[MAXLINES][MAXLEN];    /* pointers to text lines */
static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

int readlines(char lineptr[][MAXLEN], int nlines);
int old_readlines(char *lineptr[], int nlines);
void writelines(char lineptr[][MAXLEN], int nlines);
int getline(char *, int);
char *alloc(int);
void qsort(char *lineptr[], int left, int right);
void swap(char *v[], int i, int j);

/* sort input lines */
main()
{
    int nlines;     /* number of input lines read */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
        ;
    writelines(lineptr, nlines);
    return 0;
    
}

int readlines(char lineptr[][MAXLEN], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while((len = getline(lineptr[nlines], MAXLEN)) > 0) {
        if (nlines >= maxlines)
            return -1;
        else {
            lineptr[nlines++][len-1] = '\0';
        }
    }
    return nlines;
}

/* readlines: read input lines */
int old_readlines(char *lineptr[], int maxlines)
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
void writelines(char lineptr[][MAXLEN], int nlines)
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

/* return pointer to n characters */
char *alloc(int n)
{
    if (allocbuf +ALLOCSIZE - allocp >= n) {    /* it fits */
        allocp += n;
        return allocp - n;  /* old p */
    } else      /* not enough room */
        return 0;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    
    if (left >= right)  /* do nothing if array contains */
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
