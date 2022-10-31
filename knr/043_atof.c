#include <stdio.h>
#include <ctype.h>
#include <math.h>

double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-'? -1 : 1);
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0*val + (s[i] - '0');
        power *= 10;
    }
    
    if (s[i] == 'e')
        i++;
    int sciSign = (s[i] == '-'? -1 : 1);
    if (s[i] == '+' || s[i] == '-')
        i++;

    float sciPower;
    for (sciPower = 0.0; isdigit(s[i]); i++)
        sciPower = 10*sciPower + (s[i] - '0');

    return sign * (val / power) * pow(10, sciSign * sciPower);
}

int main()
{
    char s[] = "3.14159e-3";
    
    printf("%f", atof(s));

    return 0;
}
