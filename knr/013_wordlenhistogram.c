#include <stdio.h>

main()
{
    int c, counter;
    int histogram[10];

    for (int i = 0; i < 10; ++i)
        histogram[i] = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            if (counter <= 9)
                histogram[counter]++;
            counter = 0;
        }
        else 
            counter++;
    }

    for(int i = 0; i < 10; ++i)
    {
        printf("%d: ", i);
        for(int j = 0; j < histogram[i]; ++j)
        {
            printf("#");
        }
        printf("\n");
        // printf("words with %d chars: %d\n", i, histogram[i]);
    }

}
