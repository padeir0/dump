#include <stdio.h>

#define MAXLINE 1000

char longest[MAXLINE];
char line[MAXLINE];
int max;

int get_line()
{
    int c, i = 0;
    extern char line[];

    while ((c = getchar()) != EOF && c != '\n' && i < MAXLINE - 1)
    {
        line[i] = c;
        i++;
    }
    if (c == '\n')
    {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

void copy()
{
    extern char longest[], line[];
    int i = 0;
    while ((longest[i] = line[i]) != '\0')
        i++;
}

int main()
{
    int curr_len;
    extern char longest[];
    extern int max;

    while ((curr_len = get_line()) > 0)
    {
        if (curr_len > max)
        {
            max = curr_len;
            copy();
        }
    }
    if (max > 0)
        printf("\n%s\n", longest);

    return 0;
}

