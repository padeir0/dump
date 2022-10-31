#include <stdio.h>

void expand(char s1[], char s2[])
{
    int c, i = 0, j = 0, state = 0;
    int start;
    while ((c = s1[i++]) != '\0')
    {
        switch (state)
        {
            case 0:
                if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
                {
                    start = c;
                    state = 1;
                }
                else if (c >= '0' && c <= '9')
                {
                    start = c;
                    state = 3;
                }
                else
                {
                    state = 0;
                }
                break;
            case 1:
                if(c == '-')
                {
                    state = 2;
                }
                else
                {
                    state = 0;
                }
                break;
            case 2:
                if (c - start <= 'z' - 'a')
                {
                    for (char ch = start; ch <= c; ch++)
                    {
                        s2[j++] = ch;
                    }
                }
                state = 0;
                break;
            case 3:
                if (c == '-')
                {
                    state = 4;
                }
                else
                {
                    state = 0;
                }
                break;
            case 4:
                if (c - start <= '9' - '0')
                {
                    for (char ch = start; ch <= c; ch++)
                    {
                        s2[j++] = ch;
                    }
                }
                state = 0;
                break;
        }
    }
    s2[j] = '\0';
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        char s2[200];
        for (int i = 0; i < 200; i++)
            s2[i] = 0;
        expand(argv[1], s2);
        printf("%s\n", s2);
    }
    return 0;
}
