#include "util.h"
#include <math.h>

unsigned invert(unsigned x, unsigned p, unsigned n)
{
    unsigned pwr = pow(2, n);
    return x ^ ((pwr - 1) << (p + 1 - n));
}

int main()
{
    unsigned x = 127, n = 2;
    for (int p = 2; p < 10; p++)
    {
        print_cbase(invert(x, p, n), 2, '0');
    }
    return 0;
}
