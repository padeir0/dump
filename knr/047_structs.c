#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
};

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        printf("Not Enough Arguments. Usage: dist x1 y1 x2 y2");
        return -1;
    }

    struct point a = { atoi(argv[1]), atoi(argv[2]) };
    struct point b = { atoi(argv[3]), atoi(argv[4]) };

    double distance = sqrt( (double)(b.x - a.x)*(b.x - a.x) + (double)(b.y - a.y)*(b.y - a.y) );

    printf("The distance from a (%d, %d) to b (%d, %d) is: ", a.x, a.y, b.x, b.y);
    printf("%.4f\n", distance);

    return 0;
}

