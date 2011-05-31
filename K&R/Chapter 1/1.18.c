/*
 * Exercise 1.18
 *
 * Write a program to remove trailing blanks and tabs from each line
 * of input, and to delete entirely blank lines.
 *
 */

#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void removeBlanks(char line[], int length);

main()
{
    int len;    /* current line length */
    int max;    /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        removeBlanks(line,len);
        printf("%s",line);
    }

    return 0;

}

/* removeBlanks: modifies line by removing trailing blanks and tabs */
void removeBlanks(char line[], int length)
{
    char str[length];
    int i, j, copying = 0;
    for (i = 0, j = 0; i < length; ++i) {
        int c = line[i];
        if (copying == 0) {
           if (c != ' ' && c != '\t')
               copying = 1;
        }

        if (copying == 1) {
            str[j] = c;
            ++j;
        }
    }
    
    str[j] = '\0';
    copy(line, str);
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
