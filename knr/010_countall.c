#include <stdio.h>

#define true 1
#define false 0

main()
{
    int ch;
    int lines, nc, words; // counters
    int in_word = false;
    lines = nc = words = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
        {
            in_word = false;
            lines++;
            nc--;
        }
        else if (ch == ' ' || ch == '\t')
        {
            in_word = false;
        }
        else if (in_word == false)
        {
            in_word = true;
            words++;
        }
        nc++;
    }
    if (nc > 0)
        lines++;
    printf("\nWords: %d, Characters: %d, Lines: %d\n", words, nc, lines);
}
