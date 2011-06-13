/*
 * Exercise 3.1
 *
 * Our binary search makes two tests inside the loop, when one would 
 * suffice (at the price of more tests outside). Write a version with 
 * only one test inside the loop and measure the difference in run-time.
 *
 */

#include <stdio.h>

int old_binsearch(int x, int v[], int n);
int binsearch(int x, int v[], int n);

int main()
{
    int arr[10] = {0,3,6,8,12,12,37,45,89,102};
    printf("%i\n", old_binsearch(12,arr,10));
    printf("%i\n", binsearch(12,arr,10));
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low+high)/2;
    while (low <= high && x != v[mid]) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low+high) / 2;
    }
    return (x == v[mid]) ? mid : -1;
}


/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int old_binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return mid;
    }
    return -1; /* no match */
}
