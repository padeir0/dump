#include <stdio.h>


int power(int n, int p)
{
    int i = 0, out = 1;
    while (i < p) 
    {
        out *= n;
        i++;
    }
    return out;
}

int main()
{
    for (int test = 0; test < 10; ++test)
        printf("%d ** %d = %d\n", -2, test, power(-2, test));
    return 0;
}

