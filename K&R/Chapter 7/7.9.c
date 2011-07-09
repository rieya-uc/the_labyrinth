/*
 * Exercise 7.9
 *
 * Functions like isupper can be implemented to save space or to 
 * save time. Explore both possibilities.
 *
 * NB: I didn't understand this question, I got the answer from 
 * stackoverflow.
 * 
 */

#include <stdio.h>

int main()
{
    exit(0);
}

/* saves space but takes more time - comparision is slower 
 * than looking it up in a table */
int isupper(int ch)
{
    /* tests for ascii and locale */
    return ((ch >= 'A' && ch <= 'Z') || 
            (ch >= 0xC0 && ch <= 0xDD));
}

/* table takes up space, but look up is faster */
static const char bits[257] = { ...initialization... };

int isupper(int ch)
{                       /* but look, we're doing comparison here?! */
    assert(ch == EOF || (ch >= 0 && ch <= 255));
    return((bits+1)[ch] & UPPER_MASK);
}


