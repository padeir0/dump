#include <stdio.h>

#define MAXINPUTSIZE 10000 // 10kb

void clean(int target[5][20])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j  < 20; j++)
        {
            target[i][j] = -1;
        }
    }
}

int last(int target[5][20], int y)
{
    int i = 0;
    while (target[y][i] != -1)
        i++;
    return i;
}

void count_quotes(int target[5][20], char c, int i)
{
    int pos;
    if (c == '\''){
        if ((pos = last(target, 3)) - 1 == 0)
            target[3][pos-1] = -1;
        else
            target[3][pos] = i;
    }
    else if (c == '\"'){
        if ((pos = last(target, 4)) - 1 == 0)
            target[4][pos-1] = -1;
        else
            target[4][pos] = i;
    }
}

void count(int target[5][20], char c, int i)
{
    int pos;
    if (c == '('){
        target[0][last(target, 0)] = i;
    }
    else if (c == ')'){
        if ((pos = last(target, 0)) == 0)
            target[0][pos] = i;
        else
            target[0][pos - 1] = -1;
    }
    else if (c == '{'){
        target[1][last(target, 1)] = i;
    }
    else if (c == '}'){
        if ((pos = last(target, 1)) == 0)
            target[1][pos] = i;
        else
            target[1][pos - 1] = -1;
    }
    else if (c == '['){
        target[2][last(target, 2)] = i;
    }
    else if (c == ']'){
        if ((pos = last(target, 2)) == 0)
            target[2][pos] = i;
        else
            target[2][pos - 1] = -1;
    }
}

void avaliate(int target[5][20], char buffer[])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (target[i][j] != -1)
            {
                buffer[target[i][j]] = '@';
            }
        }
    }
}

int main()
{
    int i = 0, c;
    char buffer[MAXINPUTSIZE];
    int state = 0;
    int indexes[5][20];
    clean(indexes);

    for (int j = 0; j < MAXINPUTSIZE; j++)
        buffer[j] = 0;

    while ((c = getchar()) != EOF && i < MAXINPUTSIZE)
    {
        if (state == 0)
        {
            if (c == '/')
                state = 1;
            else if (c == '\'')
            {
                count_quotes(indexes, c, i);
                state = 6;
            }
            else if (c == '\"')
            {
                count_quotes(indexes, c, i);
                state = 7;
            }
            else
                count(indexes, c, i);
        }
        else if (state == 1)
        {
            if (c == '/')
                state = 2;
            else if (c == '*')
                state = 3;
            else
            {
                count(indexes, c, i);
                state = 0;
            }
        }
        else if (state == 2)
        {
            if (c == '\n')
                state = 0;
        }
        else if (state == 3)
        {
            if (c == '*')
                state = 4;
        }
        else if (state == 4)
        {
            if (c == '/')
                state = 0;                
            else
                state = 3;
        }
        else if (state == 5)
        {
            if (c == ' ' || c == '\n' || c == '\\' || c == '\t')
                state = 6;
        }
        else if (state == 6)
        {
            if (c == '\'')
            {
                count_quotes(indexes, c, i);
                state = 0;
            }
            else if (c == '\\')
                state = 5;
        }
        else if (state == 7)
        {
            if (c == '\"')
            {
                count_quotes(indexes, c, i);
                state = 0;
            }
            else if (c == '\\')
                state = 8;
        }
        else if (state == 8)
        {
            if (c == ' ' || c == '\n' || c == '\\' || c == '\t')
                state = 7;
        }
        buffer[i] = c;
        i++;
    }
    avaliate(indexes, buffer);

    printf("\n%s\n", buffer);
}
