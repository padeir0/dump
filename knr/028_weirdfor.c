#include <stdio.h>

int get_line(char target[], int lim)
{
    int i, c = getchar();
    for(i = 0; (i < lim-1) + (c != '\n') + (c != EOF) == 3; c = getchar())
    {
        target[i] = c;
        i++;
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
    char line_buffer[1000];
    while (get_line(line_buffer, 1000) > 0)
    {
        printf("%s", line_buffer);
    }
    return 0;
}
