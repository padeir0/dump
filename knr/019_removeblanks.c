#include <stdio.h>

#define true 1
#define false 0

#define MAX_INPUT_SIZE 1000

void get_input_cropped(char buffer[], int lim)
{
    int has_chars = false;
    int c, i = 0;
    int newline = true, reset = false;
    while ((c = getchar()) != EOF && i < lim)
    {
        if (has_chars == true || reset == true)
        {
            ++i;
            reset = false;
        }
        if (c != ' ' &&  c != '\t' && c != '\n')
        {
            has_chars = true;
        }
        else if (c == '\n' && has_chars == true)
        {
            reset = true;
            has_chars = false;
        }
        buffer[i] = c;
    }
}

int main()
{
    char input_buffer[MAX_INPUT_SIZE];
    for (int i = 0; i < MAX_INPUT_SIZE; i++)
        input_buffer[i] = 0;

    get_input_cropped(input_buffer, MAX_INPUT_SIZE);

    printf(". EOF\n%s\n", input_buffer);
}
