/*
 * Exercise 4.1
 *
 * Write the function strrindex(s,t), which returns the position 
 * of the rightmost occurrence of t in s, or -1 if there is none.
 *
 */

#include <stdio.h>

#define MAXLINE 1000

int getline(char s[], int lim);
int strrindex(char s[], char t[]);

int main()
{
    char s[MAXLINE];
    while(getline(s, MAXLINE) > 0) {
        printf("%i\n",strrindex(s,"abc"));
    }

}

/* Same as strindex in the book, but instead of returning 
 * a value, keeps track of the value until the whole string 
 * has been searched */
int strrindex(char s[], char t[])
{
    int i, j, k, pos=-1;
    for (i = 0; s[i] != '\0'; ++i) {
        for (j=i, k=0; t[k] != '\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            pos=i;
    }
    
    return pos;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
    int c,i;

    i = 0;
    while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
