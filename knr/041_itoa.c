#include <stdio.h>
#include <limits.h>
#include "util.h"

#define ARRAY_SIZE 10

void itoa(int n, char s[])
{
    int i = 0, plus = 0;
    char signal = '+';
    if (n < 0)
    {
        if (n == INT_MIN)
        {
            n = -(n + ++plus);
        }
        else
            n = -n;
        signal = '-';
    }

    do
    {
        if (plus > 0)
            s[i++] = n % 10 + '0' + plus--;
        else
            s[i++] = n % 10 + '0';
    } while((n /= 10) > 0);

    s[i++] = signal;
    reverse(s, i);
    s[i] = '\0';
}

int main()
{
    char s[ARRAY_SIZE + 10];
    int n[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++)
        n[i] = INT_MIN;

    print_int_array(n, ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        itoa(n[i], s);
        printf("%s, ", s);
    }
    printf("\n");

    return 0;
}
