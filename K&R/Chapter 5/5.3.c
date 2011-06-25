/* 
 * Exercise 5.3
 *
 * Write a pointer version of the function strcat that we showed in 
 * Chapter 2: strcat(s,t) copies the string t to the end of s. 
 *
 */

#include <stdio.h>
//#include <string.h>

#define MAX 1000

void strcat_old(char s[], char t[]);
void strcat(char *s, char *t);

int main()
{
    char s[] = "hello ";
    char t[] = "world!";

    strcat(s,t);
    printf("%s\n",s);
}

/* concats t onto the end of s */
void strcat(char *s, char *t)
{
    while (*s)      /* go to end of s */
        s++;
    while((*s++ = *t++) != '\0') /* add t to s */
        ;
}

void strcat_old(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')
        i++;
    while ((s[i++] = t[j++]) != '\0')
        ;
}


