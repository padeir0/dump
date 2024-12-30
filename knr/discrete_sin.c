#include <math.h>
#include <stdint.h>

#define PI 3.14159265358979323846264338327950288419716

int32_t avg(int32_t a, int32_t b) {
	return (a+b)/2;
}

int32_t discrete_sin(int angle, int32_t min, int32_t max) {
	int32_t half_distance = (max - min)/2;
	return sin(angle * (PI / 180)) * half_distance + avg(min, max);
}
