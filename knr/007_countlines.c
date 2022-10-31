#include <stdio.h>

main()
{
    long lines = 0, tabs = 0, spaces = 0;
    int ch;

    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
            lines++; 
        else if (ch == '\t')
            tabs++;
        else if (ch == ' ')
            spaces++;
    }
    printf("\nnew lines: %ld\n", lines);
    printf("tabs: %ld\n", tabs);
    printf("spaces: %ld\n", spaces);
}
