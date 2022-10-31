#include <stdio.h>
#include "util.h"

#define BUFFER_SIZE 1000
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"

int strx(char s[], char pattern[]);

int main()
{
    char s[BUFFER_SIZE];
    char search[] = "hello";
    int index;
    while (get_line(s, BUFFER_SIZE) > 0)
    {
        if ((index = strx(s, search)) >= 0)
        {
            printf("%d: %s", index, s);
        }
    }
    return 0;
}


int strx(char s[], char pattern[])
{
    int i, j, out = -1;
    for (i = 0, j = 0; s[i] != '\0'; i++) 
    {
        if (pattern[j] == s[i] && pattern[j] != '\0')
            j++;
        else if (pattern[j] == '\0')
        {
            out = i-j;
            j = 0;
        }
        else 
            j = 0;
    }
    return out;
}


