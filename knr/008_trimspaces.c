#include <stdio.h>

main()
{
    int ch = 0;
    int was_space = 0;
    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ')
        {
            if (was_space != 1)
            {
                putchar(ch);
            }
            was_space = 1;
        }
        else
        {
            putchar(ch);
            was_space = 0;
        }
    }
}
