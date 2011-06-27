/*
 * Exercise 5.8
 *
 * There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 *
 */

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int main()
{
    int day = day_of_year(2011,2,31);
    printf("%i\n",day);
    int pmonth, pday;
    month_day(2011,388,&pmonth,&pday);
    printf("%i %i\n", pmonth, pday);
    return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return -1;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (day > daytab[leap][month])
        return -1;
    
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if (year < 0 || yearday < 0) {
        *pmonth = -1;
        *pday = -1;
        return;
    }

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (yearday > (337 + daytab[leap][2])) {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
