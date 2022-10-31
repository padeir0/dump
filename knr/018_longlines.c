#include <stdio.h>

#define MAXLEN 1000
#define MAXLINES 100


int get_line(char s[], int s_len)
{
    int c, i = 0;
    while ((c = getchar()) != EOF)
    {
        s[i] = c;
        ++i;
        if (c == '\n')
            break;
    }
    s[i] = '\0';
    return i;
}

void print_line(char line[], int line_len)
{
    for(int i = 0; i < line_len; ++i)
        putchar(line[i]);
    printf("\n");
}

int main()
{
    int curr;
    char line[MAXLEN];

    while ((curr = get_line(line, MAXLEN)) > 0)
    {
        if (curr > 80)
        {
            print_line(line, curr);
        }
    }
    return 0;
}
