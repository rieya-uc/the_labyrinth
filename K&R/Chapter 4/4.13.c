/*
 * Exercise 4.13
 *
 * Write a recursive version of the function reverse(s), which reverses 
 * the string s in place.
 *
 */

#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void reverse_r(char s[], int swap);
void reverse_n1(char s[]);  /* ignore, not part of the exercise */
void reverse_n2(char s[]);  /* ignore, not part of the exercise */

int main()
{
    char s[] = "reverse me please!\0";
    reverse(s);
    printf("%s\n",s);
    return 0;
}

/* recursive version of reverse */
void reverse(char s[])
{
    reverse_r(s,0);
}

/* this is the actual recursive part for reverse */
void reverse_r(char s[], int swap)
{
    int l = strlen(s)-1;
    char t;
    if (swap < (l/2))           /* run halfway through the string */
        reverse_r(s,swap+1);    /* swapping each letter with it's counterpart */
    t = s[swap];
    s[swap] = s[l-swap];
    s[l-swap] = t;
    
}


/* non-recursive reverse functions */
void reverse_n1(char s[])
{
    int l = strlen(s)-1;
    int i;
    for (i = 0; i < l; ++i, --l) {
        int t = s[i];
        s[i] = s[l];
        s[l] = t;
    }
}

void reverse_n2(char s[])
{
    int l = strlen(s)-1;
    int i;
    for (i = 0; i < (l/2)+1; ++i) {
        int t = s[i];
        s[i] = s[l-i];
        s[l-i] = t;
    }
    
}



