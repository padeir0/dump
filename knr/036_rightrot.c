#include "util.h"
#include <math.h>

unsigned rightrot(unsigned x, unsigned n)
{
    int pwr = pow(2, n);
    int size_x = sizeof(x)*8;
    return ((((pwr - 1) << (size_x - n)) & x) >> (size_x -n)) | (x<<n);
}

int main()
{
    int x = 4095;

    for (int n = 0; n < 10; n++)
        print_cbase(rightrot(x, n), 2, '0');

    return 0;
}
