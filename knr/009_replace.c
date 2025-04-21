#include <stdio.h>

int main()
{
    int ch;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '\t')
            putchar('\t');
        else if (ch == '\b')
            putchar('\b');
        else
            putchar(ch);
    }
}
