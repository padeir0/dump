#include <stdio.h>

void lower(char target[])
{
    int i = 0, c;
    while ((c = target[i]) != '\0')
        target[i++] = (c >= 'A' && c <= 'Z')?  c - ('A'-'a') : c;
    target[i] = '\0';
}

int main()
{
    char str[] = "Oh! Creator! Please don't keep me waiting!";
    lower(str);
    printf("%s\n", str);

    return 0;
}
