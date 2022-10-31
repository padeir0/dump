#include <stdio.h>

float to_celsius(float temp)
{
    return (5.0/9.0) * (temp - 32.0);
}
float to_fahrenheit(float temp)
{
    return (9.0/5.0) * temp + 32.0;
}

int main()
{
    printf("Fahr to Celsius:\n");
    for (float i = 0; i < 300; i+=10)
    {
        printf("%.2f \t %.2f\n", i, to_celsius(i));
    }

    printf("Celsius to Fahr:\n");
    for (float i = 0; i < 300; i+=10)
    {
        printf("%.2f \t %.2f\n", i, to_fahrenheit(i));
    }
    return 0;
}
