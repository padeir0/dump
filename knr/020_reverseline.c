#include <stdio.h>

#define MAXLINESIZE 100

void reverse(char target[], int size, char origin[])
{
    int j = 0;
    for (int i = size -1; i >= 0; i--)
    {
        target[j] = origin[i];
        j++;
    }
}

int get_line(char target[], int limit)
{
    int c, i = 0;
    while ((c = getchar()) != EOF && c != '\n' && i < limit)
    {
        target[i] = c;
        i++;
    }
    
    return i;
}

int main()
{
    char line[MAXLINESIZE], reverse_line[MAXLINESIZE];
    int linesize = 0;

    while ((linesize = get_line(line, MAXLINESIZE)) > 0)
    {
       reverse(reverse_line, linesize, line); 

       putchar('\n');
       for(int i = 0; i < linesize; i++)
       {
           putchar(reverse_line[i]);
       }
       putchar('\n');
    }

    return 0;
}
