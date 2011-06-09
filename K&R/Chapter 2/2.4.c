/*
 * Exercise 2.4
 *
 * Write an alternate version of squeeze(s1,s2) that deletes each character 
 * in s1 that matches any character in the string s2.
 *
 */

#include <stdio.h>
#define MAX 1000

void old_squeeze(char s[], int c);
void squeeze(char s1[], char s2[]);

main()
{
    char s[MAX] = "abxcdxbxcx\0";
    squeeze(s,"k\0");
    printf("%s\n",s );
}

// Old squeeze that I need to modify
void old_squeeze(char s[], int c)
{
    int i,j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

        
void squeeze(char s1[], char s2[])
{
    int i,j,k;
    for (i = 0; s2[i] != '\0'; ++i) {
        for (j = k = 0; s1[j] != '\0'; ++j) {
            if (s1[j] != s2[i])
                s1[k++] = s1[j];
        }
        s1[k] = '\0';
    }
}
