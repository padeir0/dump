#include <stdio.h>
#include <math.h>

int binary_v2(int x, int v[], int n)
{
    int low = 0, mid, high = n - 1;

    while (low < high-1)
    {
        mid = (low+high)/2;
        printf("(%d, %d, %d), ", low, mid, high);
        if (x < v[mid])
            high = mid;
        else
            low = mid;
    }
    printf("\n");

    if (v[high] == x)
        return high;
    else if (v[low] == x)
        return low;
    else
        return -1;
}

int binary_v1(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low < high)
    {
        mid = (low+high)/2;
        printf("(%d, %d, %d), ", low, mid, high);
        if (x < v[mid])
            high = mid;
        else if (x > v[mid])
            low = mid;
        else
        {
            printf("\n");
            return mid;
        }
    }
    printf("\n");
    return -1;
}

int len(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

int str_to_int(char s[])
{
    unsigned len_s = len(s);
    unsigned i = len_s-1, j = 0, output = 0, pwr;
    while (i >= 0 && j < len_s)
    {
        pwr = pow(10, i);
        output +=  pwr * (s[j] - '0');
        i--;
        j++;
    }

    return output;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return -1;

    unsigned n = str_to_int(argv[1]);
    unsigned x = str_to_int(argv[2]);
    printf("n = %d, x = %d\n", n, x);
    int array[n];
    for (int i = 0; i < n; i++)
        array[i] = i;

    printf("%d\n", binary_v1(x, array, n));
    printf("%d\n", binary_v2(x, array, n));

    return 0;
}
