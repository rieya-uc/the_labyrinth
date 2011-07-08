/* 
 * Exercise 7.6
 *
 * Write a program to compare two files, printing the first line
 * where they differ.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    FILE *file1, *file2;
    char s1[MAXLINE] = "\0";
    char s2[MAXLINE] = "\0";
    char *r1, *r2;

    file1 = fopen("testfile1.txt", "r");
    file2 = fopen("testfile2.txt", "r");
    
    do {
        r1 = fgets(s1, MAXLINE, file1);
        r2 = fgets(s2, MAXLINE, file2);
        
        if ((strcmp(s1, s2)) != 0) {
            printf("Mismatch found\n");
            printf("File 1: %s\n", s1);
            printf("File 2: %s\n", s2);
            return 0;
        }
    } while (r1 != NULL && r2 != NULL);


    printf("Files match\n");

    fclose(file1);
    fclose(file2);
    exit(0); 
}
