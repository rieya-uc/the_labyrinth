/* 
 * Exercise 6.6
 *
 * Implement a simple version of the #define processor (i.e., no 
 * arguments) suitable for use with C programs, based on the routines 
 * of this section. You may also find getch and ungetch helpful.
 * 
 * What I've implemented:
 *      
 *      #define NAME DEFN will now take DEFN to be from the end of NAME
 *      until a new line is reached, e.g. #define expr 1 + 2 + 3
 *      
 *      #view to see what defines have been added to the hashtable
 *      
 *      #undef will remove entry from table (if present)
 *
 *      Typing in a line without any of the above will echo out the line
 *      with any #defines replaced by its defn.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define MAXNAMES 1000
#define HASHSIZE 101

struct nlist {      /* table entry: */
    struct nlist *next;     /* next entry in chain */
    char *name;             /* defined name */
    char *defn;             /* replacement text */
};

int getch(void);
void ungetch(int);
int getword(char *, int);
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int undef(char *w);

/* this is just so I can view all the names in the list */
/* not part of the exercise, for convenience */
char *namelist[MAXNAMES];
int freespace[MAXNAMES];
int nsdex = 0;
void addname(char *s);
void removename(char *s);
int spaces = 0;

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int main()
{  
    int hashnext = 0;
    int undefnext = 0;
    char word[MAXWORD];
    char line[MAXWORD];
    struct nlist *nl = NULL;

    int i;
    for (i = 0; i < MAXNAMES; ++i)
        freespace[i] = 0;   /* indicates empty spots in array */

    printf("\nTo add a word to the hashtable use #define NAME DEF\n");
    printf("To remove a word from the hashtable use #undef NAME\n");
    printf("To view the hashtable use #view\n\n");

    char c;
    while ((c = getword(word, MAXWORD)) != EOF) {
        if (strcmp(word, "#define") == 0) {
            hashnext = 1;
        }
        else if (hashnext == 1) {       /* Ex 6.6 */
            /* read input until new line found */
            /* this will be the "defn" part; not restricted */
            /* to a single word */         
            char g;
            while(isspace(g=getch())) {
                if (g == '\n') {
                    printf("Error in #define\n");
                    hashnext = 0;
                    break;
                }
            }
            
            /* no error occurred in #define */
            if (hashnext) {
                line[0] = g;
                int i = 1;
                while ((line[i++] = getch()) != '\n')
                    ;
                line[--i] = '\0';
                install(word,line);

                /* keeping track of names defined, for my own amusement */
                addname(word);
                hashnext = 0;
            }
            ungetch('\n');
        }
        else if (strcmp(word, "#view") == 0) {
            nl = NULL;
            int i;
            printf("\n  Word       Defn\n");
            for (i = 0; i < nsdex; ++i) {
                if (freespace[i] != 1) {
                    nl = lookup(namelist[i]);
                    printf("   %-10s %s\n",nl->name, nl->defn);
                }
            }
        }
        else if (!hashnext && strcmp(word, "#undef") == 0)  
            undefnext = 1;                                   
        else if (undefnext != 0) {      /* ex 6.5 */
            removename(word);           /* delete defines */
            undef(word);
            undefnext--;
        }
        else if ((nl = lookup(word)) != NULL)  /* ex 6.6 */
            printf("%s",nl->defn);             /* replace defines */
        else 
            printf("%s",word);
    }
}

/* undef: removes a definition from the hash table */
/* returns -1 if unable to remove word */
int undef(char *word)
{
    struct nlist *nl = lookup(word);
    struct nlist *pl;
    int hh;

    if (nl == NULL)  /* not in table */
        return -1;
    
    hh = hash(word);
    nl = hashtab[hh];
    pl = NULL;

    while (strcmp(nl->name,word) != 0) {
        pl = nl;
        nl = nl->next;
    }

    /* remove from list and free */
    if (pl == NULL)
        hashtab[hh] = nl->next;
    else
        pl->next = nl->next;
    free(nl->name);
    free(nl->defn);
    free(nl);

    return 1;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)];  np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;     /* found */
    return NULL;           /* not found */
}

/* install:  put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */ 
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else       /* already there */
        free((void *) np->defn);   /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* addname: adds word to list of definitions */
void addname(char *s)
{
    /* no more room in array */
    if (nsdex >= MAXNAMES && spaces == 0)
        return;

    /* already in list */
    int i = 0;
    for (i = 0; i < MAXNAMES; ++i) {
        if (namelist[i] != NULL && strcmp(s, namelist[i]) == 0)
            return;
    }

    /* enter in next free spot */
    if (spaces == 0)
        namelist[nsdex++] = strdup(s);
    else {
        i = 0;
        while (freespace[i++] == 0)
            ;
        freespace[--i] = 0;
        spaces--;
        namelist[i] = strdup(s);
    }
}

/* removename: removes word from list of definitions */
void removename(char *s)
{
    int i;
    for (i = 0; i < MAXNAMES; ++i) {
        if (namelist[i] != NULL && strcmp(s, namelist[i]) == 0) {
            freespace[i] = 1;
            spaces++;
            namelist[i] = "\0";
            return;
        }
    }
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
        printf("%c",c);     /* slight modification of getword */
    

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

