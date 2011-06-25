/* 
 * Exercise 5.5
 *
 * Write versions of the library functions strncpy, strncat, and strncmp, 
 * which operate on at most the first n characters of their argument 
 * strings. For example, strncpy(s,t,n) copies at most n characters of 
 * t to s. Full descriptions are in Appendix B. 
 *
 */

#include <stdio.h>
//#include <string.h>

#define MAX 1000

int getline(char line[], int max);
void strncpy(char *s, char *t, int n);
void strncat(char *s, char *t, int n);
int strncmp(char *s, char *t, int n);
int strnlen(char *s);

int main()
{
    char s[MAX];
    char m[MAX];
    char t[] = " concat me, copy me, leave me";

    while(getline(s,MAX) > 0) {
        printf("length: %i\n",strnlen(s));
        s[strnlen(s)-1] = '\0';       //remove \n character
        strncat(s,t,12);
        printf("concat: %s\n", s);
        strncpy(s,t,19);
        printf("copy: %s\n\n", s);
    }
    return 0;
}

/* strnlen: returns length of s */
int strnlen(char *s)
{
    int i = 0;
    while(*s++)
        i++;
    return i;
}

/* strncpy: copies n amount of characters from t to s */
void strncpy(char *s, char *t, int n)
{
    int i;
    for (i = 0; *t != '\0' && i < n; ++i)
        *s++ = *t++;
    *s = '\0';
}

/* strncat: concatenates n amount of characters from t onto s */
void strncat(char *s, char *t, int n)
{
    int i;
    while (*s)
        s++;
    for(i = 0; *t != '\0' && i < n; ++i)
        *s++ = *t++;
    *s = '\0';
}

/* strncmp: compares the first n characters of s and n */
int strncmp(char *s, char *t, int n)
{
    int i = 1;
    while(*s++ != *t++ && i++ < n)
        i = 0;
    return i;
}

/* getline: reads line into s, return length */
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

