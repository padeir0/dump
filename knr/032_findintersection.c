#include <stdio.h>

int find_char(char s[], char c)
{
    int i = 0, ch;

    while ((ch = s[i]) != '\0')
        if (ch == c)
            return i;
        else
            i++;

    return -1;
}

int any(char s1[], char s2[])
{
    int c, i = 0, find = 0;
    
    while ((c = s1[i++]) != '\0')
    {
        if (find_char(s2, c) != -1)
        {
            return i-1; 
        }
    }

    return -1;
}

int main()
{
    int c, i = 0, j = 0;
    int state = 0;
    char buffer0[100], buffer1[100];

    while ((c = getchar()) != EOF)
    {
        if (state == 0)
        {
            if (c == '\n')
            {
                buffer0[i] = '\0';
                state = 1;
            }
            else
                buffer0[i++] = c;
        }
        else
        {
            if (c == '\n')
            {
                buffer1[j] = '\0';
                printf("%d\n", any(buffer0, buffer1));
                state = 0;
                j = i = 0;
            }
            else
                buffer1[j++] = c;
        }
    }

    return 0;
}
