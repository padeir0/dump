#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP  20

main()
{
    for (int celsius = UPPER; celsius > LOWER; celsius-=STEP)
    {
        printf("%3d \t %6.2f\n", celsius, (9.0/5.0 * celsius)+32.0);
    }
}
