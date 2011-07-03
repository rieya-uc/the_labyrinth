/*
 * Exercise 6.2
 *
 * Write a program that reads a C program and prints in alphabetical 
 * order each group of variable names that are identical in the first 
 * 6 characters but different somewhere thereafter. Don't count words 
 * within strings and comments. Make 6 a parameter that can be set 
 * from the command line.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
 
struct tnode {      /* tree node */
    char *key;
    char *simlist[MAXWORD];
    int count;
    struct tnode *left;
    struct tnode *right;
};

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tnode *addtree(struct tnode *, char *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
void sort(char *v[], int left, int right);
void swap(char *v[], int i, int j);
//int binsearch(char *, struct key *, int);
//char *strdupx(char *s);

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];
    int keepnext = 0;
    int nmatch = 6;
    int len;
    char s[MAXWORD];
    struct tnode* match;

    //get user arguments
    if (argc > 1) {
        if (isdigit(*argv[1]))
            nmatch = atoi(argv[1]);
        else {
            printf("Usage: filename <int>\n");
            return 0;
        }
    }

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (strcmp("struct",word) == 0)
            keepnext = 2;                   
        /* is the next word a variable name? */
        else if (isvariable(word))
            keepnext = 1;
        else if (keepnext == 1) {
            len = (strlen(word) < nmatch) ? strlen(word) : nmatch;
            strcpy(s,word);
            *(s+len) = '\0';    /* the part of the word we're comparing */

            root = addtree(root,s,word);   
            keepnext = 0;
        }
        else if (keepnext > 0)
            keepnext--;
    }

    treeprint(root);
    return 0;
}

/* isvariable: returns 1 if w is one of C's datatypes */
int isvariable(char * word)
{   
    if ((strcmp(word, "bool") == 0)   || (strcmp(word, "char") == 0)  ||
        (strcmp(word, "double") == 0) || (strcmp(word, "float") == 0) ||
        (strcmp(word, "int") == 0)    || (strcmp(word, "long") == 0)  ||
        (strcmp(word, "short") == 0)  || (strcmp(word, "void") == 0)  ||
        (strcmp(word, "struct") == 0))

        return 1;
    else
        return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char* key, char *w)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();   /* make a new node */
        p->key = strdup(key);
        p->count = 1;
        p->simlist[0] = strdup(w);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(key, p->key)) == 0)
        p->simlist[p->count++] = strdup(w);
    else if (cond < 0)  /* less than into left subtree */
        p->left = addtree(p->left, key, w);
    else                /* greater than into right subtree */
        p->right = addtree(p->right, key, w);
    return p;
}

/* quick sorts a list of char* in alphabetical order */
void sort(char *v[], int left, int right)
{
    int i, last;
    
    if (left >= right) 
        return;  

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    sort(v, left, last-1);
    sort(v, last+1, right);
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        sort(p->simlist, 0, p->count-1);
        printf("%s: ", p->key);
        int i;
        for (i = 0; i < p->count; i++)
            printf("%s ", p->simlist[i]);
        printf("\n");

        //printf("%4d %s\n", p->count, p->key);
        treeprint(p->right);
    }
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()) || c == '*')
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

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
