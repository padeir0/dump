#include <stdio.h>
#include <math.h>

long int htoi(char s[], int size)
{
    int c, i = size-1;
    long int decimal = 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        s[1] = '0';
    while (i > 0)
    {
       c = s[i];

       if (c >= '0' && c <= '9')
       {
           decimal += (c - '0') * (pow(16, size-1 -i));
       }
       else if (c >= 'a' && c <='f')
       {
           decimal += (c - 'a' + 10) * (pow(16, size-1 -i));
       }
       else if (c >= 'A' && c <= 'F')
       {
           decimal += (c - 'A' + 10) * (pow(16, size-1 -i));
       }
       else
       {
           return -1;
       }
       i--;
    }

    return decimal;
}

int main()
{
    int c, i = 0;
    char buffer[100];

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            printf("%ld\n", htoi(buffer, i));
            i = 0;
        }
        else
        {
            buffer[i] = c;
            i++;
        }

        if (i >= 100) 
        {
            printf("Too long\n");
            i = 0;
        }
    }

    return 0;
}
