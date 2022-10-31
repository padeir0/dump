#include <stdio.h>

#define true 1
#define false 0

main()
{
    int ch;
    int in_word = false;

    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            in_word = false;
            putchar('\n');
        }
        else
        {
            in_word = true;
            putchar(ch);
        }
    }
}
