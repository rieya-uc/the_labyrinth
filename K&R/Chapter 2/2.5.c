/*
 * Exercise 2.5
 *
 * Write the function any(s1,s2), which returns the first location in the 
 * string s1 where any character from the string s2 occurs, or -1 if s1 
 * contains no characters from s2. (The standard library function strpbrk 
 * does the same job but returns a pointer to the location.)
 *
 */

#include <stdio.h>

#define MAX 1000

int getline(char s[], int lim);
int any(char s1[],char s2[]);

main()
{
    char tofind[] = "abc\0";

    char s[MAX];
    while((getline(s,MAX)) != EOF) {
        printf("%d\n",any(s,tofind));
    }
}

int any(char s1[], char s2[])
{
    int pos = -1;
    int i, j;

    for (i = 0; s1[i] != '\0' && pos == -1; ++i) {
        for (j = 0; s2[j] != '\0'  && pos == -1; ++j) {
            if (s1[i] == s2[j]) {
                pos = i;        // guess I could break, but haven't 
            }                   // reached it in the book yet
        }
    }
    return pos;
}



int getline(char s[], int lim)
{
    int i = 0;
    char c;
    while ((c = getchar()) != EOF && c != '\n' && i < lim-1) {
        s[i++] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

