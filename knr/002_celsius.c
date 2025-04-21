#include <stdio.h>

int main()
{
    float fahr, celsius;
    float lower, upper, step;
    
    lower = -10; /* lower limit of temperature scale*/
    upper = 100; /* upper limit */
    step = 5; /* step size */

    celsius = lower;
    printf("°F \t °C\n");
    while (celsius <= upper)
    {
        fahr = (9.0 / 5.0) * celsius + 32 ;
        /* (9.0 / 5.0) * celsius+32.0 
         * (5.0 / 9.0) * (fahr-32.0) */
        printf("%3.1f %6.1f\n", fahr, celsius);
        celsius += step;
    }
}
