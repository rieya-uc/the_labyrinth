/*
 * Exercise 3.2
 *
 * Write a function escape(s,t) that converts characters like newline 
 * and tab into visible escape sequences like \n and \t as it copies the 
 * string t to s. Use a switch. Write a function for the other direction 
 * as well, converting escape sequences into the real characters.
 *
 */

#include <stdio.h>
#define MAXLINE 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int getline(char s[], int lim);

int main()
{

    char s[MAXLINE];
    char t[MAXLINE];

    while (s != "\0") {
        getline(s,MAXLINE);
        escape(s,t);
        printf("Escape: %s\n", t);
        unescape(t,s);
        printf("And back again: %s\n", s); 
    }
    return 0;
}

/* Lets assume t is big enough to hold s */
void escape(char s[], char t[])
{
    int i,j;
    for (i = j = 0; s[i] != '\0'; ++i) {
        switch(s[i]) {
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            default:
                t[j++] = s[i];
                break;
        }
    }
    t[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i,j;
    for(i = j = 0; s[i] != '\0'; ++i) {
        if (s[i] == '\\' && (s[i+1] == 'n' || s[i+1] == 't')) {
            switch (s[i+1]) {
                case 'n':
                    t[j++] = '\n';
                    break;
                case 't':
                    t[j++] = '\t';
                    break;
                default:
                    break;
            }
            i++;
        }
        else        
            t[j++] = s[i];
    }
    t[j] = '\0';
}

int getline(char s[], int lim)
{
    int c, len;

    len = 0;
    while ((c = getchar()) != EOF && c != '\n' && len < lim - 1) {
        s[len++] = c;
    }

    if (c == 0)
        s[len] = '\0';
    else {
        s[len++] = c;
        s[len] = '\0';
    }

    return len;
}
