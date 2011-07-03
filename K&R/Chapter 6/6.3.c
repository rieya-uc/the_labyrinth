/*
 * Exercise 6.3
 *
 * Write a cross-referencer that prints a list of all words in a document, 
 * and, for each word, a list of the line numbers on which it occurs. 
 * Remove noise words like "the", "and", and so on.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define MAXLINES 1000
#define NKEYS (sizeof noise / sizeof(char*))

struct tnode {      /* tree node */
    char *word;
    int count;
    int linenum[MAXLINES];
    struct tnode *left;
    struct tnode *right;
};

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
int isnoiseword(char *word);
int binsearch(char*, char*[], int);

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

char *noise[] = {"a", "and", "are", "as", "at", "i", "if", 
    "in", "is", "it", "of", "on", "or", "the", "to", "with", "you"};

int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];
    char c;
    int nlines = 1;

    root = NULL;
    while ((c=getword(word, MAXWORD)) != EOF) {
        /* convert word to lower case */
        int i;
        for(i = 0; word[i] != '\0'; i++)
            word[i] = tolower(word[i]);

        /* add word to the tree */
        if (c == '\n')
            nlines++;
        else if (!noiseword(word))
            root = addtree(root,word,nlines); 
    }
    treeprint(root);
    return 0;
}

/* isnoiseword: wrapper for searchnoise, returns 1 if word is noise, else 0 */
int noiseword(char *word)
{
    return binsearch(word, noise, NKEYS) < 0 ? 0 : 1;
}

/* binsearch: performs binary search on array of strings */
int binsearch(char* word, char *list[], int len)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = len - 1;
    while(low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, list[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int lnum)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();   /* make a new node */
        p->word = strdup(w);
        p->linenum[0] = lnum;
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->linenum[p->count++] = lnum;  /* repeated word */
    else if (cond < 0)  
        p->left = addtree(p->left, w, lnum);
    else                
        p->right = addtree(p->right, w, lnum);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);

        printf("Word: %-15sTotal: %i\n", p->word, p->count);
        printf("  Appears on: ");
        int i;
        for (i = 0; i < p->count; ++i)
            printf("%i ", p->linenum[i]);
        printf("\n");
        
        treeprint(p->right);
    }
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())) {
        if (c == '\n') 
            return c;
    }
    
    if (c == EOF)
        return c;

    *w++ = c;
    while (--lim > 0) {
        c = getch();
        if (c != ' ' && c != EOF && c != '\n')
            *w++ = c;
        else {
            ungetch(c);
            break;
        }
    }
    
    *w = '\0';
    return word[0];
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

