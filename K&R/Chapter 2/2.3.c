/*
 * Exercise 2.3
 *
 * Write the function htoi(s), which converts a string of hexadecimal 
 * digits (including an optional 0x or 0X) into its equivalent integer 
 * value. The allowable digits are 0 through 9, a through f, and A 
 * through F.
 *
 */

#include <stdio.h>

#define MAXLINE 1000

int htoi(char s[]);

main()
{
    printf("0x123 to dec = %d\n",htoi("0x123\0"));
    printf("0X13FDE to dec = %d\n",htoi("0X13FDE"));
    printf("638BF to dec = %d\n",htoi("638BF"));

}

int htoi(char s[])
{
    int value = 0;
    int len, i;
    
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        i = 2;
    else
        i = 0;
    
    while(s[i] != '\0' && s[i] != EOF && s[i] != '\n') {
        int x = s[i];
        
        value = value * 16 + x - '0';    
        if (x >= 'A' && x <= 'F')
            value = value - 7;
        else if (x >= 'a' && x <= 'f')
            value = value - 39;
        else if (x <= '0' || x >= '9'){
            //What do we do if s is not a hex?
            printf("Invalid hexadecimal digit\n");
            return 0;
        }
        ++i;
    }

    return value;    
}
