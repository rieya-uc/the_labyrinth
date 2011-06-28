/* 
 * Exercise 5.11
 *
 * Modify the programs entab and detab (written as exercises in Chapter 1) 
 * to accept a list of tab stops as arguments. Use the default tab 
 * settings if there are no arguments.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int getline(char *s, int lim);
void entab(char*, int[]);
void detab(char*, int[]);

int main(int argc, char *argv[])
{
    char s[MAXLINE];
    int tabs[argc];

    if (argc <= 1) {
        printf("Usage: A list of ints representing tab stops\n");
        return -1;
    }

    /* convert arguments to ints */
    int i;
    for (i = 0; i < argc-1; ++i) 
        tabs[i] = atoi(*++argv);
    tabs[argc-1] = '\0';     /* so en\detab knows when the array is finished */

    while((getline(s,MAXLINE) > 0)) {
        detab(s, tabs);
        printf("Detab: %s\n",s);
        entab(s,tabs);
        printf("Entab: %s\n",s);
    }
}

/* detab: takes a string and a list of ints, and replaces the tabs with 
 * the relevant amount of blank spaces */
void detab(char *s, int tabs[])
{
    char temp[MAXLINE];
    int i=0,tb=0,ti=0;
    int tab;

    for(i=0; s[i] != '\0'; i++) {
        if (s[i] == '\t') {
            if (tabs[tb] != '\0') /* are there tabs left in the list? */
                tab = tabs[tb++];
            else
                tab = 4;    /* default tab value */
            
            int j;
            for(j=ti%tab; j < tab+1; ++j)    /* add the tabs */
                temp[ti++] = ' ';
        }
        else
            temp[ti++] = s[i];    
    }
    temp[ti] = '\0';

    /* copy over to s */
    for(i=0; temp[i] != '\0'; i++) {
        s[i] = temp[i];
    }
    s[ti] = '\0';
}

/* entab: replaces a number of spaces, specified by tabs[], by '\t' */
void entab(char *s, int tabs[])
{
    char temp[MAXLINE];
    int i,j,tb=0;
    int spaces = 0;
    int tab = tabs[tb++];

    for(i=j=0; s[j] != '\0'; j++) {
        while(s[j] == ' ') {
            spaces++;
            if (spaces+1 == tab) {  /* replace spaces with tab */
                s[i++] = '\t';
                spaces = 0;
                
                if (tabs[tb] != '\0')   /* get next tab stop */
                    tab = tabs[tb++];
                else
                    tab = 4;
            }
            j++;
        }

        /* add in the rest of the spaces that haven't been replaced */
        while(spaces > 1) {
            s[i++] = ' ';
            spaces--;
        }

        /* "squeeze" s by overwriting extra spaces with the 
         * rest of the string */
        s[i++] = s[j];
    }
    s[i] = '\0';
}


/* getline: reads line into s, return length */
int getline(char s[], int lim)
{
    int c,i;

    i = 0;
    while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    //if (c == '\n')
    //    s[i++] = c;
    s[i] = '\0';

    return i;
}

