#include <stdio.h>
#include "util.h"

void qsort(int v[], int left, int right)
{
    int i, last;
    if (left >= right)
        return;

    swap(v, left, (left+right)/2);
    last = left;

    for (i = left+1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);

    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

int main(int argc, char **argv)
{
    int a[11] = {9, 2, 3, 12, 12, 73, 82, 9, 1982, 738, 3};
    qsort(a, 0, 10);
    print_int_array(a, 11);
    return 0;
}

