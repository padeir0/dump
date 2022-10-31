#include <stdio.h>

#define MAXLINESIZE 200

int detab_line(char target[], int max_size)
{
    int c, i = 0, j;
    
    while ((c = getchar()) != EOF && c != '\n' && i < max_size-1)
    {
        if (c != '\t')
        {
            target[i] = c;
            i++;
        }
        else
        {
            j = 0;
            while (j < 8 - (i % 8))
            {
                target[i + j] = '.';
                j++;
            }
            i += j;
        }
    }
    if (c == '\n')
    {
        target[i] = c;
        i++;
    }
    target[i] = '\0';

    return i;
}

int main()
{
    char line_buffer[MAXLINESIZE];
    char input_buffer[MAXLINESIZE * 100]; //rewrite and change to linked list or array of pointers when you learn how to do it
    int size, j;

    while ((size = detab_line(line_buffer, MAXLINESIZE)) > 0)
    {
        for (int i = 0; i < size; i++)
        {
            input_buffer[j] = line_buffer[i];
            j++;
        }
    }
    printf("\n.\n%s", input_buffer);

    return 0;
}
