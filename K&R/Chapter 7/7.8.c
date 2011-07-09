/*
 * Exercise 7.8
 *
 * Write a program to print a set of files, starting each new one 
 * on a new page, with a title and a running page count for each
 * file.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define LINESPERPAGE 3      /* I set this small for testing */

int main(int argc, char *argv[])
{
    FILE *fp;
    char line[MAXLINE];
    int pageno;
    int lineno;

    if (argc < 2) {
        printf("Usage: filename <names_of_files>\n");
        exit(0);
    }

    int i = 0;
    while (++i < argc) {

        pageno = 1;
        lineno = LINESPERPAGE;

        if ((fp = fopen(argv[i], "r")) == NULL) {
             fprintf(stderr, "\n%s: can't open %s\n", argv[0], argv[i]);
             continue;      /* skip this file, read in the rest */
        }

        printf("\nTitle: %s\n",argv[i]);  /* use name of file as title */
        
        while (fgets(line, MAXLINE, fp) != NULL) {
            if (lineno >= LINESPERPAGE) {
                printf("\nPage %i\n", pageno);
                lineno = 1;
                pageno++;
            }
            printf("%s",line);
            lineno++;
        }        
        printf("\n\n");
    }
    fclose(fp);   
}
