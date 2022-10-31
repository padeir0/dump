#include <stdio.h>

#define MAXINPUTSIZE 10000 // 10kb
#define false 0
#define true 1

int main()
{
    int i = 0, c;
    char buffer[MAXINPUTSIZE];
    int state = 0;

    for (int j = 0; j < MAXINPUTSIZE; j++)
        buffer[j] = 0;

    while ((c = getchar()) != EOF && i < MAXINPUTSIZE)
    {
        if (state == 0)
        {
            if (c != '/')
            {
                buffer[i] = c;
                i++;
            }
            else
            {
                buffer[i] = c;
                state = 1;
            }
        }
        else if (state == 1)
        {
            if (c == '/')
            {
                state = 2;
            }
            else if (c == '*')
            {
                state = 3;
            }
            else
            {
                i++;
                buffer[i] = c;
                i++;
                state = 0;
            }
        }
        else if (state == 2)
        {
            if (c == '\n')
            {
                buffer[i] = c;
                i++;
                state = 0;
            }
        }
        else if (state == 3)
        {
            if (c == '*')
            {
                state = 4;
            }
        }
        else if (state == 4)
        {
            if (c == '/')
            {
                state = 0;                
            }
            else
            {
                state = 3;
            }
        }
    }

    printf("\n%s\n", buffer);
}
