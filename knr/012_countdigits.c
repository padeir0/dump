#include <stdio.h>

main()
{
    int c;

    int digits[10];
    c = 0;
    for (int i = 0; i < 10; ++i)
        digits[i] = 0;

    while ((c = getchar()) != EOF)
    {
        if (c >= '0' || c <= 9)
            ++digits[c-'0'];
    }

    printf("\n");
    for (int i = 0; i < 10; ++i)
    {
        printf("%d: %d\n", i, digits[i]);
    }
}
