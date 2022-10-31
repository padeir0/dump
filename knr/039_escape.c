#include <stdio.h>

void escape(char s[], char t[])
{
    int i = 0, j = 0, c;
    while ((c = s[i]) != '\0') 
    {
        switch (c)
        {
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            default:
                t[j++] = c;
                break;
        }
        i++;
    }
}

void deescape(char s[], char t[])
{
    int c, i = 0, j = 0, state = 0;

    while ((c = s[i]) != '\0')
    {
        switch(state)
        {
            case 0:
                if (c == '\\')
                    state = 1;
                else
                    t[j++] = c;
                break;
            case 1:
                if (c == 't')
                    t[j++] = '\t';
                else if (c == 'n')
                    t[j++] = '\n';
                state = 0;
                break;
            default:
                state = 0;
                break;
        }
        i++;
    }
}

int main()
{
    char t1[100], t2[100];
    escape("\t\npoop\n\t", t1);
    printf("%s\n", t1);

    deescape(t1, t2);
    printf("%s\n", t2);
}
