#include <stdio.h>
#include <math.h>


// converts number 'x' in base 10 to base 2 to 16, specified in 'base'. 
// 'null_bits' is used to specify what do put in place of zeros
// (use 1 if you want to ommit it them)
void print_cbase(unsigned x, unsigned base, char null_bits)
{
    char symbols[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char output[33];
    for (int i = 0; i < 33; i++)
        output[i] = null_bits;
    output[32] = '\0';
    output[31] = '0'; // if x == 0 it does not enter the loop
    int i = 31;      

    while (x >= 1) // if the loop is x >= 0 Seg. Fault happens
    {
        output[i] = symbols[x % base];
        x /= base;
        i--; // it starts printing the least valuable digit first
            // so the loop needs to go backwards to print correctly
    }
    printf("%s\n", output);
}

// pretty prints a array of integers, O(n)
void print_int_array(int array[], int size)
{
    printf("{");
    for(int i = 0; i < size; i++)
    {
        printf("%d", array[i]);
        if (i + 1 >= size)
            printf("}\n"); 
        else
            printf(", ");
    }
}

// finds first ocurrence of 'target' in 'str'
// O(n)
int find_char(char str[], char target)
{
    int c, i = 0;
    while ((c = str[i]) != '\0')
    {
        if (c == target)
            return i;
        i++;
    }
    return -1;
}

// returns the length of s, O(n)
int len(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

// converts string s to integer, only natural numbers tho
int str_to_int(char s[])
{
    unsigned len_s = len(s);
    unsigned i = len_s-1, j = 0, output = 0, pwr;
    while (i >= 0 && j < len_s)
    {
        pwr = pow(10, i);
        output +=  pwr * (s[j] - '0');
        i--;
        j++;
    }

    return output;
}

// reverses a string s in place
// O(n)
void reverse(char s[], int length)
{
    int i = length -1, j = 0;
    char buff;
    while (i > j)
    {
        buff = s[i];
        s[i] = s[j];
        s[j] = buff;
        i--;
        j++;
    }
}

// gets one line from input
// O(n)
int get_line(char s[], int max)
{
    int i = 0, c;
    while (--max > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;

    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

// outputs the index of first ocurrence of 'pattern' in 's', -1 if not found
// O(n)
int str_index(char s[], char pattern[])
{
    int i, j, out = -1;
    for (i = 0, j = 0; s[i] != '\0'; i++) 
    {
        if (pattern[j] == s[i] && pattern[j] != '\0')
            j++;
        else if (pattern[j] == '\0')
        {
            out = i - j;
            break;
        }
        else 
            j = 0;
    }
    return out;
}

void p_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

