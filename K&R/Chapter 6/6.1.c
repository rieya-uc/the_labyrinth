/*
 * Exercise 6.1
 *
 * Our version of getword does not properly handle underscores, string
 * constants, comments, or preprocessor control lnes. Write a better
 * version.
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 100
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))
// #define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "if", 0,
    "int", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};
    

int getword(char *, int);
int binsearch(char *, struct key *, int);
struct key;

char *keyword[NKEYS];
int keycount[NKEYS];
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

    

/* count C keywords */
main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
        }
    }
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    }
    
    return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;

    /* ignore string constants */
    if (c == '"') {
        while((c = getch()) != '"' && c != EOF)
            ;
    }

    /* ignore comments */
    if (c == '/') {
        c = getch();
        if (c == '/')
            while ((c = getch()) != '\n' && c != EOF)
                ;
        else if (c = '/') {
            while (c != EOF) {
                if ((c = getch())  == '*' && (c = getch()) == '/')
                    break;
            }
        }
        /* and if neither? Shall I return an error or just carry on? */
        /* hmm, I'll just carry on */
    }

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {       /* ignore underscored words */
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}


/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
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

