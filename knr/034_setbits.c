#include <stdio.h>
#include <math.h>

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
    unsigned pwr = pow(2, n), y_size = sizeof(y); 
    return (x | ((pwr - 1) << (p - n + 1))) | ((y >> (y_size*8 -n)) << (p -n +1));
}

int main()
{
    unsigned x = 0, p, n = 4;
    unsigned y = 2147483648;
    for (p = n - 1; p < 32; p++)
        printf("x = %u, y = %u, p = %u, n = %u == %u\n", x, y, p, n, setbits(x, p, n, y));

    return 0;
}
