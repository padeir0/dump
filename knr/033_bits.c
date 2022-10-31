#include <stdio.h>

int main()
{
    printf("AND BITWISE OPERATOR\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d & %d == %d\n", 1, i, 1 & i);
    }

    printf("OR BITWISE OPERATOR\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d | %d == %d\n", 1, i, 1 | i);
    }

    printf("XOR BITWISE OPERATOR\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ^ %d == %d\n", 1, i, 1 ^ i);
    }

    printf("LEFT SHIFT BITWISE OPERATOR\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d << %d == %d\n", 1, i, 1 << i);
    }

    printf("RIGHT SHIFT BITWISE OPERATOR\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d >> %d == %d\n", i, 1, i >> 1);
    }

    printf("COMPLEMENT BITWISE OPERATOR\n");
    for (int i = 0; i < 10; i++)
    {
        printf("~%d == %d\n", i, ~i);
    }

    return 0;
}
