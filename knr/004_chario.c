#include <stdio.h>

main()
{
    int c;
    printf("%d", EOF);
    while ((c = getchar()) != EOF)
        putchar(c);
}
