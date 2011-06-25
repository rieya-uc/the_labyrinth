/*
 * Exercise 4.14
 *
 * Define a macro swap(t,x,y) that interchanges two arguments of type t.
 * (Block structure will help).
 *
 */

#include <stdio.h>
#include <string.h>

#define swap(T,A,B) {T x = A; A = B; B = x;}

int main()
{
    int a = 1;
    int b = 2;
    swap(int, a, b);
    printf("%i,%i\n",a,b);
}
