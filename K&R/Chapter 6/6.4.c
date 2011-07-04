/*
 * Exercise 6.4
 *
 * Write a program that prints the distinct words in its input 
 * sorted into decreasing order of frequency of occurrence. Precede
 * each word by its count.
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
void freqprint(struct tnode*);
struct tnode* sort(struct tnode*, struct tnode*);

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
    struct tnode *sorted = NULL;

    root = NULL;
    while ((c=getword(word, MAXWORD)) != EOF) {
        /* convert word to lower case */
        int i;
        for(i = 0; word[i] != '\0'; i++)
            word[i] = tolower(word[i]);

        /* add word to the tree */
        if (c == '\n')
            nlines++;
        else //if (!noiseword(word))
            root = addtree(root,word,nlines); 
    }
   
    /* prints the tree by order of decreasing frequency */
    sorted = sort(sorted, root);
    freqprint(sorted);
    return 0;
}

/* freqprint: prints word and word count */
void freqprint(struct tnode* p)
{
    if (p != NULL) {
        freqprint(p->left);
        printf("%i %s\n", p->count, p->word);
        freqprint(p->right);
    }

}

/* sort: sorts a tree of tnode by tnode->count */
/* ok, not really sorting; recreats tree using count as key */
struct tnode* sort(struct tnode* to, struct tnode* from)
{
    struct tnode* addbycount(struct tnode*, struct tnode*);
    
    if (from != NULL) {
        to = addbycount(to, from);    /* add current node */
        to = sort(to, from->left);    /* add all nodes in left branch */
        to = sort(to, from->right);   /* add all nodes in right branch */
    }
}

struct tnode* addbycount(struct tnode* root, struct tnode* p)
{
    if (p == NULL)  /* this shouldn't happen */
        return root;
    else if (root == NULL) {
        root = talloc();
        root->word = strdup(p->word);
        root->count = p->count;
        root->left = NULL;
        root->right = NULL;
    }
    else if (root->count < p->count)
        root->left = addbycount(root->left, p);
    else if (root->count >= p->count)
        root->right = addbycount(root->right, p);
    return root;
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

