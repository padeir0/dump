#include <stdio.h>

main()
{
    long i;
    i = 0;
    while (getchar() != EOF)
    {
        ++i;
    }
    printf("%ld\n", i);
}
