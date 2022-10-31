#include <stdio.h>

void rm_char(char s[], char x)
{
    int c, i = 0, j = 0;
    while ((c = s[i++]) != '\0')
    {
        if (c != x)
            s[j++] = c;
    }
    s[j] = '\0';
}

void rm_intersection(char s1[], char s2[])
{
    int c, i = 0;
    while ((c = s2[i++]) != '\0')
    {
        rm_char(s1, c);
    }
}

int main()
{
    char buffer0[100], buffer1[20];
    int i = 0, j = 0, which = 0, c;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            if (which == 0)
            {
                buffer0[i] = '\0';
                which = 1;
            }
            else
            {
                buffer1[j] = '\0';
                rm_intersection(buffer0, buffer1);
                printf("%s\n", buffer0);
                which = 0;
                 j = i = 0;
            }
        }
        else
        {
            if (which == 0)
                buffer0[i++] = c;
            else
                buffer1[j++] = c;
        }
    }
}
