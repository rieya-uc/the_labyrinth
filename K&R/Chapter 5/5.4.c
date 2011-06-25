/* 
 * Exercise 5.4
 *
 * Write the function strend(s,t), which returns 1 if the string t 
 * occurs at the end of the string s, and zero otherwise.
 *
 */

#include <stdio.h>
#include <string.h>

#define MAX 1000

int strend(char *s, char *t);

int main()
{
    char *s = "hello world! ";
    char *t = "world! ";

    int x = strend(s,t);
    printf("%i\n",x);
}

/* strend: returns 1 if t occurs at the end of s */
int strend(char *s, char *t)
{
    int tSize = strlen(t);
    int sSize = strlen(s);

    if (tSize > sSize)          /* check if s is big enough to hold t */
        return 0;
    s = s + (sSize - tSize);    /* move to the end of s minus length of t */
    while ((*s != '\0') && (*s++ == *t++))     /* are they equal? */
        ;
    return (*s == '\0');        /* are both strings at end char? */
}

