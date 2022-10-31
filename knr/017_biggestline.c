#include <stdio.h>

#define MAXLINE 1000

int get_line(char s[], int lim)
{
    int c, i;

    for (i = 0; i< lim - 1 && (c = getchar()) != EOF; ++i)
    {
        s[i] = c;
        if (c == '\n')
            break;
    }
    s[i] = '\0';
    return i;
}

void copy(char target[], char origin[])
{
    int i = 0;
    while ((target[i] = origin[i]) != '\0')
        ++i;
}

int main()
{
    int len = 0, max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0)
        printf("\n%s\n%d chars long\n", longest, max);

    return 0;
}
