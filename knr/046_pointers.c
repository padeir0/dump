#include <stdio.h>
#include "util.h"

int main()
{
    int a = 1, b = 2, c = 3;
    int *p = &a; // initializes pointer p to the address of a
    b = *p; // sets b to a
    c += *p; // adds a to c

    int ar[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    a = ar[0];        // a is now equal to a[0]
    b = *(ar + 1);    // b is now equal to a[1]
    p = ar;           // p now points to a[0]
    c = *(++p);       // c is now equal to a[1]
    int d = *(p + 1); // d is initialized with the value of a[2]
    
    int newArray[] = {a, b, c, d};
    print_int_array(newArray, 4);
}
