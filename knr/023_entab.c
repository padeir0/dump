#include <stdio.h>

#define MAXLINESIZE 100
#define MAXINPUTSIZE 1000

int entab_line(char target[], int lim)
{
    int c, i = 0, cols = 0;
    int spaces = 0;

    while ((c = getchar()) != EOF && c != '\n' && i < lim - 1)
    {
        if (c != ' ')
        {
            target[i] = c;
            spaces = 0;
            i++;
            if (c == '\t')
                cols += 8 - (cols % 8);
            else
                cols++;
        }
        else
        {
            if (cols % 8 == 7 && spaces > 0)
            {
                i -= spaces;
                target[i] = '\t';
                spaces = 0;
            }
            else
            {
                target[i] = '.';
                spaces++;
            }    
            i++;
            cols++;
        }
    }
    if (c == '\n')
    {
        target[i] = '\n';
        i++;
    }
    target[i] = '\0';

    return i;
}

int main()
{
    char line_buffer[MAXLINESIZE];
    char input_buffer[MAXINPUTSIZE];
    int j = 0, size;

    while ((size = entab_line(line_buffer, MAXLINESIZE)) > 0)
    {
        for (int i = 0; i < size && j < MAXINPUTSIZE; i++)
        {
            input_buffer[j] = line_buffer[i];
            j++;
        }
    }

    printf("\n%s\n", input_buffer);

    return 0;
}
