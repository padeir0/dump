#include <stdio.h>

main()
{
    int c;
    int ascii_chars[96];
    
    for (int i = 0; i < 96; ++i)
        ascii_chars[i] = 0;

    while ((c = getchar()) != EOF)
    {
        if (c >= 32 && c < 128)
            ascii_chars[c-32]++;
    }

    printf("\nRunning...\n");

    for (int i = 0; i < 96; ++i)
    {
        printf("%c : %d\n", i+32, ascii_chars[i]);
    }
}
