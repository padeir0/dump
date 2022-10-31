#include <stdio.h>

main()
{
    double i;
    
    for (i = 0; getchar() != EOF; ++i);
    printf("\n%.0f\n", i);
}
