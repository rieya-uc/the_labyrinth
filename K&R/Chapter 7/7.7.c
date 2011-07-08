/* 
 * Exercise 7.7
 *
 * Modify the pattern finding program of Chapter 5 to take its 
 * input from a set of named files or, if no files are named as 
 * arguments, from the standard input. Should the file name be 
 * printed when a matching line is found?
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFILES 10
#define MAXWORD 1000
#define MAXLINE 1000

int findpattern(char *, char *, FILE *);

int main(int argc, char *argv[])
{
    FILE *fp;
    char *pattern;
    char line[1000];

    if (argc == 2) {
        printf("Usage: filename <pattern> <set of files>\n");
        exit(0);
    }

    if (argc == 1) {
        printf("Enter patten > ");
        fgets(pattern, MAXLINE, stdin);
        pattern[strlen(pattern)-1] = '\0';    /* remove newline */
        printf("Enter lines to look for pattern\n");

        int found = findpattern(pattern, line, stdin);
        if (found > 0)
            printf("Pattern found in: %s\n", line);
        else
            printf("Pattern not found\n");
    }
    else {
        pattern = argv[1];
        
        int matched = 0;
        int i;
        for (i = 2; i < argc; ++i) {    
            if ((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", argv[0], argv[i]);
                continue;
            }
            
            /* search through each file */
            int found = findpattern(pattern, line, fp);
            if (found > 0) {
                printf("Pattern found in file %s, line %i\n", argv[i], found);
                printf("> %s \n", line);
                matched = 1;
            }

            fclose(fp);
        }

        if (matched == 0)
            printf("Pattern not found\n");
    }

    exit(0);
}
        
/* findpattern: searches through fp or stdin for pattern */
/* returns line number and line if found, else 0 */
int findpattern(char * pattern, char * line, FILE *fp)
{
    int lineno = 1;
    while ((fgets(line, MAXLINE, fp)) != NULL) {
        if (strstr(line, pattern) != NULL) /* found the pattern */
            return lineno;
       lineno++;
    } 
    return 0;
}






            





        
