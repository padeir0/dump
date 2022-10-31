#include <stdio.h>

#define MAXINPUTLENGHT 1000 // 1kb
#define LINELIMIT 50

int main()
{
    int c;
    int line_len = 0, i = 0;
    int last_space = 0;
    char buffer[MAXINPUTLENGHT];

    while ((c = getchar()) != EOF && i < MAXINPUTLENGHT)
    {
        if (c == '\n')
        {
            line_len = 0;
            last_space = 0;
        }
        if (c == ' ' || c == '\t')
            last_space = i;

        if (line_len > LINELIMIT)
        {
            if (last_space != 0)
                buffer[last_space] = '\n';
            else
            {
                buffer[i] = '\n';
                i++;
            }
            line_len = 0;
        }

        buffer[i] = c;
        line_len++;
        i++;
    }

    printf("\n%s\n", buffer);

    return 0;
}
