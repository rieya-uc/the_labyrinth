/*
 * Exercise 3.3
 *
 * Write a function expand(s1,s2) that expand shorthand notations like 
 * a-z in the string s1 into the equivalent complete list abc...xyz in 
 * s2. Allow for letters of either case and digits, and be prepared to 
 * handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading 
 * or trailing - is taken literally.
 *
 */

#include <stdio.h>
#define MAXLINE 1000

void expand(char s[], char t[]);

int main()
{
    char t[MAXLINE];
    char s[] = ("-sfdsA-Gp-m-z0-9-\0");

    printf("%s\n",s);
    expand(s,t);
    printf("%s\n",t);
    return 0;
}

/* Doesn't check to see if range *can* be expanded properly.
 * E.g. "z-a" and "Z-a" will be expanded incorrectly. */
void expand(char s[], char t[])
{
    int i,j;
    int start, end;
    
    i = j = 0;
    while (s[i] != '\0') {
        t[j++] = s[i];
        
        if (s[i] == '-' && s[i+1] != '\0' && i > 0) {
            start = s[i-1];     /* first letter in the range */
            end = s[i+1];       /* last letter in the range */

            j--;
            /* Runs through range until we get to the last letter. */
            /* Ignore first letter, was added a few lines back. */
            int k;
            for (k = start+1; k < end; ++k) {
                t[j++] = k;
            }
        }
        ++i;
    }

    t[j] = '\0';
                
}
