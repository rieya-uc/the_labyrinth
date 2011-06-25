/* 
 * Exercise 5.6 
 *
 * Rewrite appropriate programs from earlier chapters and exercises 
 * with pointers instead of array indexing. Good possibilities include 
 * getline (Chapters 1 and 4), atoi, itoa, and their variants 
 * (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop 
 * (Chapter 4). 
 *
 */

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

int getline(char *s);
void reverse(char *s);
int strlen(char *s);
void swap(char *s, char *t);
void itoa2(int n, char *s);

int main()
{
    char *s;        
    
    itoa2(12345,s);
    printf("itoa:%s\n\n",s);

    while(getline(s) > 1) {
        reverse(s);
        printf("reversed:%s\n",s);
        reverse(s);
        swap(s,(s+strlen(s)-1));
        printf("swapped:%s\n\n",s);   // first and last letters swapped
    }
    
    return 0;
}

/* strlen: returns length of s */
int strlen(char *s)
{
    int i = 0;
    while(*s++)
        i++;
    return i;
}

/* swap: swaps t and s values */
void swap(char *s, char *t)
{
    char temp;
    temp = *s;
    *s = *t;
    *t = temp;
}
    
/* reverse: reverses a string in place */
void reverse(char *s)
{
    int j;
    int i = strlen(s)-1;
    for (j = 0; j < i-1; ++j) 
        swap((s+j), (s+i-j));
}

/* itoa2: converts int n into a string */
void itoa2(int n, char *s)
{
    int i, sign;

    sign = (n < 0) ? -1 : 1;   
    i = 0;
    do {                            /* generate digits in reverse order */
        *s++ = abs(n % 10) + '0';   /* get next digit */
    } while (abs(n /= 10) > 0);     /* delete it */
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(s);
}

/* getline: reads a string into s and returns its length */
int getline(char *s)
{
    int i = 0;
    while ((*s++ = getchar()) != '\n')
        ++i;
    *--s = '\0';    // remove 'enter' char 
    return i;
}


