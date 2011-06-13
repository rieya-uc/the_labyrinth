/* 
 * Exercise 3.5
 *
 * Write the function itob(n,s,b) that converts the integer n into 
 * a base b character representation in the string s. In particular, 
 * itob(n,s,16) formats n as a hexadecimal integer in s.
 *
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAXLINE 1000

void reverse(char s[]);
void itob(int n,char s[],int b);

int main()
{
    char s[MAXLINE];
    itob(-239,s,8);
    printf("%s\n",s);
}

void itob(int n, char s[], int b)
{
    /* pretty much like itoa in 3.4 except instead of dividing by 10,
     * divide by the base (b)
     */
    int i = 0, sign, t;
    sign = (n < 0) ? -1 : 1;
    do {
        t = abs(n % b);
        t +=  (t > 9) ? '7' : '0';
        s[i++] = t;
    } while (abs(n /= b) > 0);
    
    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}


/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


